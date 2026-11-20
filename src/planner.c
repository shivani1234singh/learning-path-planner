#include "planner.h"
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define MAKE_DIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MAKE_DIR(path) mkdir(path, 0755)
#endif

Topic topics[MAX_TOPICS];
Assessment assessments[MAX_ASSESSMENTS];
StudySession sessions[MAX_SESSIONS];

int topicCount = 0;
int assessmentCount = 0;
int sessionCount = 0;

int graph[MAX_TOPICS][MAX_TOPICS];

static void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void readName(char *buffer, int size) {
    if (!fgets(buffer, size, stdin))
        buffer[0] = '\0';

    buffer[strcspn(buffer, "\r\n")] = '\0';
}

static int findTopic(int id) {
    for (int i = 0; i < topicCount; i++)
        if (topics[i].id == id)
            return i;

    return -1;
}

static void ensureDirectories(void) {
    MAKE_DIR("data");
    MAKE_DIR("reports");
}

/* STUDENT PROFILE / TOPIC MANAGEMENT */

void addTopic(void) {
    if (topicCount >= MAX_TOPICS) {
        printf("Topic limit reached.\n");
        return;
    }

    Topic t;

    printf("\nEnter Topic ID: ");
    if (scanf("%d", &t.id) != 1) {
        clearInput();
        printf("Invalid ID.\n");
        return;
    }

    if (findTopic(t.id) != -1) {
        clearInput();
        printf("Topic ID already exists.\n");
        return;
    }

    clearInput();

    printf("Enter Topic Name: ");
    readName(t.name, MAX_NAME);

    if (strlen(t.name) == 0 ||
        strchr(t.name, '|') != NULL) {
        printf("Invalid topic name.\n");
        return;
    }

    printf("Estimated Study Hours: ");
    if (scanf("%d", &t.hours) != 1 ||
        t.hours <= 0 || t.hours > 10000) {
        clearInput();
        printf("Invalid hours.\n");
        return;
    }

    printf("Learning Importance (1-100): ");
    if (scanf("%d", &t.value) != 1 ||
        t.value < 1 || t.value > 100) {
        clearInput();
        printf("Invalid importance.\n");
        return;
    }

    printf("Current Mastery (0-100): ");
    if (scanf("%d", &t.mastery) != 1 ||
        t.mastery < 0 || t.mastery > 100) {
        clearInput();
        printf("Invalid mastery.\n");
        return;
    }

    printf("Deadline Day (1-365): ");
    if (scanf("%d", &t.deadline) != 1 ||
        t.deadline < 1 || t.deadline > 365) {
        clearInput();
        printf("Invalid deadline.\n");
        return;
    }

    clearInput();

    topics[topicCount++] = t;
    saveData();

    printf("\nTopic added and saved successfully!\n");
}

void displayTopics(void) {
    if (topicCount == 0) {
        printf("\nNo topics available.\n");
        return;
    }

    printf("\n%-6s %-25s %-8s %-10s %-10s %-10s\n",
           "ID", "TOPIC", "HOURS", "VALUE",
           "MASTERY", "DEADLINE");

    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < topicCount; i++) {
        printf("%-6d %-25.25s %-8d %-10d %-10d %-10d\n",
               topics[i].id,
               topics[i].name,
               topics[i].hours,
               topics[i].value,
               topics[i].mastery,
               topics[i].deadline);
    }
}

/* PREREQUISITE GRAPH */

void addPrerequisite(void) {
    if (topicCount < 2) {
        printf("Add at least two topics first.\n");
        return;
    }

    int a, b, weight;

    displayTopics();

    printf("\nEnter first topic ID: ");
    if (scanf("%d", &a) != 1) {
        clearInput();
        return;
    }

    printf("Enter dependent topic ID: ");
    if (scanf("%d", &b) != 1) {
        clearInput();
        return;
    }

    printf("Enter connection cost (hours): ");
    if (scanf("%d", &weight) != 1 ||
        weight <= 0 || weight > 10000) {
        clearInput();
        printf("Invalid connection cost.\n");
        return;
    }

    clearInput();

    int u = findTopic(a);
    int v = findTopic(b);

    if (u == -1 || v == -1 || u == v) {
        printf("Invalid topic IDs.\n");
        return;
    }

    /* A symmetric weighted relationship is used
       for shortest-path and MST demonstrations. */

    graph[u][v] = weight;
    graph[v][u] = weight;

    saveGraph();

    printf("Topic relationship added and saved successfully.\n");
}

/* LEARNING PATH GENERATION */

void generateLearningPath(void) {
    if (topicCount == 0) {
        printf("Add topics first.\n");
        return;
    }

    Topic sorted[MAX_TOPICS];

    memcpy(sorted, topics, topicCount * sizeof(Topic));

    mergeSort(sorted, 0, topicCount - 1);

    printf("\nPERSONALIZED LEARNING PATH\n");
    printf("---------------------------------------\n");
    printf("Topics are ranked by importance.\n\n");

    for (int i = 0; i < topicCount; i++) {
        printf("%d. %s\n", i + 1, sorted[i].name);
        printf("   Study Hours : %d\n", sorted[i].hours);
        printf("   Importance  : %d\n", sorted[i].value);
        printf("   Mastery     : %d%%\n", sorted[i].mastery);

        if (sorted[i].mastery >= 80)
            printf("   Status      : Revision recommended\n");
        else if (sorted[i].mastery >= 50)
            printf("   Status      : Practice required\n");
        else
            printf("   Status      : High learning priority\n");

        printf("\n");
    }

    printf("Note: This is a priority-based ordering.\n");
    printf("Use the graph algorithms to inspect topic relationships.\n");
}

/* STUDY TIME ALLOCATION */

void allocateStudyTime(void) {
    if (topicCount == 0) {
        printf("Add topics first.\n");
        return;
    }

    int hours;

    printf("\n========================================\n");
    printf("       STUDY TIME ALLOCATION\n");
    printf("========================================\n");

    printf("\nEnter your available study hours: ");

    if (scanf("%d", &hours) != 1 ||
        hours <= 0 || hours > 100000) {
        clearInput();
        printf("Invalid study budget.\n");
        return;
    }

    clearInput();

    printf("\n========================================\n");
    printf("1. 0/1 KNAPSACK (Dynamic Programming)\n");
    printf("========================================\n");
    knapsack(hours);

    printf("\n========================================\n");
    printf("2. FRACTIONAL KNAPSACK (Greedy)\n");
    printf("========================================\n");
    fractionalKnapsack(hours);

    printf("\n========================================\n");
    printf("3. BRANCH AND BOUND (Exact Optimization)\n");
    printf("========================================\n");
    branchAndBound(hours);

    printf("\n========================================\n");
    printf("       ALLOCATION COMPARISON COMPLETE\n");
    printf("========================================\n");
}

/* ASSESSMENT MANAGEMENT */

void addAssessment(void) {
    if (assessmentCount >= MAX_ASSESSMENTS) {
        printf("Assessment limit reached.\n");
        return;
    }

    if (topicCount == 0) {
        printf("Add topics first.\n");
        return;
    }

    Assessment a;

    printf("\nAssessment ID: ");

    if (scanf("%d", &a.id) != 1 || a.id <= 0) {
        clearInput();
        printf("Invalid assessment ID.\n");
        return;
    }

    for (int i = 0; i < assessmentCount; i++) {
        if (assessments[i].id == a.id) {
            clearInput();
            printf("Assessment ID already exists.\n");
            return;
        }
    }

    clearInput();

    printf("Assessment Name: ");
    readName(a.name, MAX_NAME);

    if (strlen(a.name) == 0 ||
        strchr(a.name, '|') != NULL) {
        printf("Invalid assessment name.\n");
        return;
    }

    displayTopics();

    printf("Associated Topic ID: ");

    if (scanf("%d", &a.topicId) != 1 ||
        findTopic(a.topicId) == -1) {
        clearInput();
        printf("Invalid topic ID.\n");
        return;
    }

    printf("Assessment Day: ");

    if (scanf("%d", &a.day) != 1 ||
        a.day < 1 || a.day > 365) {
        clearInput();
        printf("Invalid day.\n");
        return;
    }

    printf("Duration in minutes: ");

    if (scanf("%d", &a.duration) != 1 ||
        a.duration <= 0 || a.duration > 1440) {
        clearInput();
        printf("Invalid duration.\n");
        return;
    }

    clearInput();

    a.completed = 0;

    assessments[assessmentCount++] = a;

    saveData();

    printf("\nAssessment created and saved successfully!\n");
}

void displayAssessments(void) {
    printf("\n");
    printf("============================================================\n");
    printf("                    ASSESSMENT DASHBOARD\n");
    printf("============================================================\n");

    if (assessmentCount == 0) {
        printf("No assessments scheduled.\n");
        return;
    }

    printf("%-6s %-22s %-10s %-8s %-12s\n",
           "ID", "ASSESSMENT", "TOPIC ID", "DAY", "STATUS");

    printf("------------------------------------------------------------\n");

    int completed = 0;
    int pending = 0;

    for (int i = 0; i < assessmentCount; i++) {
        printf("%-6d %-22.22s %-10d %-8d %-12s\n",
               assessments[i].id,
               assessments[i].name,
               assessments[i].topicId,
               assessments[i].day,
               assessments[i].completed
               ? "COMPLETED" : "PENDING");

        if (assessments[i].completed)
            completed++;
        else
            pending++;
    }

    printf("------------------------------------------------------------\n");

    printf("Total Assessments : %d\n", assessmentCount);
    printf("Completed         : %d\n", completed);
    printf("Pending           : %d\n", pending);

    printf("============================================================\n");
}

/* PROGRESS TRACKING */

void updateProgress(void) {
    int id, mastery;

    displayTopics();

    printf("\nEnter Topic ID: ");

    if (scanf("%d", &id) != 1) {
        clearInput();
        return;
    }

    int index = findTopic(id);

    if (index == -1) {
        clearInput();
        printf("Topic not found.\n");
        return;
    }

    printf("Enter updated mastery (0-100): ");

    if (scanf("%d", &mastery) != 1 ||
        mastery < 0 || mastery > 100) {
        clearInput();
        printf("Invalid mastery.\n");
        return;
    }

    clearInput();

    topics[index].mastery = mastery;
    saveData();

    printf("Mastery updated and saved successfully.\n");

    if (mastery >= 80)
        printf("Recommendation: Schedule a revision assessment.\n");
    else if (mastery >= 50)
        printf("Recommendation: Continue practice exercises.\n");
    else
        printf("Recommendation: Revisit foundational concepts.\n");
}

/* ANALYTICS DASHBOARD */

void showDashboard(void) {
    if (topicCount == 0) {
        printf("No learning data available.\n");
        return;
    }

    int totalHours = 0;
    int masterySum = 0;
    int completed = 0;

    for (int i = 0; i < topicCount; i++) {
        totalHours += topics[i].hours;
        masterySum += topics[i].mastery;
    }

    for (int i = 0; i < assessmentCount; i++)
        if (assessments[i].completed)
            completed++;

    printf("\n====================================\n");
    printf("       LEARNING ANALYTICS\n");
    printf("====================================\n");

    printf("Total Topics             : %d\n", topicCount);
    printf("Total Planned Study Hours: %d\n", totalHours);
    printf("Average Mastery          : %.2f%%\n",
           (double)masterySum / topicCount);

    printf("Total Assessments        : %d\n",
           assessmentCount);

    printf("Completed Assessments    : %d\n",
           completed);

    printf("Pending Assessments      : %d\n",
           assessmentCount - completed);

    printf("====================================\n");
}

/* FILE PERSISTENCE */

void saveData(void) {
    ensureDirectories();

    FILE *fp = fopen("data/topics.txt", "w");

    if (fp == NULL) {
        perror("Cannot open data/topics.txt");
        return;
    }

    printf("\nSaving %d topics...\n", topicCount);

    for (int i = 0; i < topicCount; i++) {
        int result = fprintf(fp, "%d|%s|%d|%d|%d|%d\n",
                             topics[i].id,
                             topics[i].name,
                             topics[i].hours,
                             topics[i].value,
                             topics[i].mastery,
                             topics[i].deadline);

        if (result < 0) {
            printf("Error writing topic ID %d.\n",
                   topics[i].id);
            fclose(fp);
            return;
        }
    }

    if (fclose(fp) != 0) {
        perror("Error closing data/topics.txt");
        return;
    }

    printf("Topics saved successfully: %d\n", topicCount);

    fp = fopen("data/assessments.txt", "w");

    if (fp == NULL) {
        perror("Cannot open data/assessments.txt");
        return;
    }

    for (int i = 0; i < assessmentCount; i++) {
        fprintf(fp, "%d|%s|%d|%d|%d|%d\n",
                assessments[i].id,
                assessments[i].name,
                assessments[i].topicId,
                assessments[i].day,
                assessments[i].duration,
                assessments[i].completed);
    }

    if (fclose(fp) != 0) {
        perror("Error closing data/assessments.txt");
        return;
    }

    printf("Assessments saved successfully: %d\n",
           assessmentCount);
}

void loadData(void) {
    ensureDirectories();
    topicCount = 0;
    assessmentCount = 0;

    FILE *fp = fopen("data/topics.txt", "r");

    if (!fp) {
        printf("No saved topic file found.\n");
    } else {
        char line[512];

        while (topicCount < MAX_TOPICS &&
               fgets(line, sizeof(line), fp)) {
            Topic t;

            if (sscanf(line, "%d|%59[^|]|%d|%d|%d|%d",
                       &t.id, t.name, &t.hours,
                       &t.value, &t.mastery,
                       &t.deadline) == 6 &&
                t.hours > 0 &&
                t.value >= 1 && t.value <= 100 &&
                t.mastery >= 0 && t.mastery <= 100 &&
                t.deadline >= 1 && t.deadline <= 365 &&
                findTopic(t.id) == -1) {
                topics[topicCount++] = t;
            }
        }

        fclose(fp);
    }

    fp = fopen("data/assessments.txt", "r");

    if (fp) {
        char line[512];

        while (assessmentCount < MAX_ASSESSMENTS &&
               fgets(line, sizeof(line), fp)) {
            Assessment a;

            if (sscanf(line, "%d|%59[^|]|%d|%d|%d|%d",
                       &a.id, a.name, &a.topicId,
                       &a.day, &a.duration,
                       &a.completed) == 6 &&
                findTopic(a.topicId) != -1 &&
                a.day >= 1 && a.day <= 365 &&
                a.duration > 0 &&
                (a.completed == 0 || a.completed == 1)) {
                assessments[assessmentCount++] = a;
            }
        }

        fclose(fp);
    }

    printf("Loaded %d topics and %d assessments.\n",
           topicCount, assessmentCount);
}

/* CSV EXPORT */

void exportReport(void) {
    ensureDirectories();

    FILE *fp = fopen("reports/learning_report.csv", "w");

    if (!fp) {
        printf("Cannot create report. Check reports folder.\n");
        return;
    }

    fprintf(fp,
        "ID,Topic,StudyHours,Importance,Mastery,Deadline\n");

    for (int i = 0; i < topicCount; i++) {
        fprintf(fp, "%d,\"%s\",%d,%d,%d,%d\n",
                topics[i].id,
                topics[i].name,
                topics[i].hours,
                topics[i].value,
                topics[i].mastery,
                topics[i].deadline);
    }

    fclose(fp);

    printf("CSV report exported to reports/learning_report.csv\n");
}

void saveGraph(void) {
    ensureDirectories();

    FILE *fp = fopen("data/relationships.txt", "w");

    if (fp == NULL) {
        printf("ERROR: Cannot open data/relationships.txt\n");
        return;
    }

    int saved = 0;

    /*
       Save only existing relationships.
       Graph uses topic array indices as vertices.
    */

    for (int i = 0; i < topicCount; i++) {
        for (int j = 0; j < topicCount; j++) {
            if (graph[i][j] != 0) {
                fprintf(fp, "%d|%d|%d\n",
                        topics[i].id,
                        topics[j].id,
                        graph[i][j]);

                saved++;
            }
        }
    }

    fclose(fp);

    printf("Graph saved successfully!\n");
    printf("Relationships saved: %d\n", saved);
}

void loadGraph(void) {
    FILE *fp = fopen("data/relationships.txt", "r");

    /*
       Clear the old graph before loading.
    */

    for (int i = 0; i < MAX_TOPICS; i++) {
        for (int j = 0; j < MAX_TOPICS; j++) {
            graph[i][j] = 0;
        }
    }

    if (fp == NULL) {
        printf("No saved prerequisite relationships found.\n");
        return;
    }

    int sourceID, destinationID, weight;
    int loaded = 0;

    while (fscanf(fp, "%d|%d|%d",
                  &sourceID,
                  &destinationID,
                  &weight) == 3) {
        int sourceIndex = findTopic(sourceID);
        int destinationIndex = findTopic(destinationID);

        if (sourceIndex != -1 &&
            destinationIndex != -1 &&
            sourceIndex != destinationIndex &&
            weight > 0) {
            graph[sourceIndex][destinationIndex] = weight;
            loaded++;
        }
    }

    fclose(fp);

    printf("Prerequisite graph loaded successfully!\n");
    printf("Relationships restored: %d\n", loaded);
}

void completeAssessment(void) {
    if (assessmentCount == 0) {
        printf("No assessments available.\n");
        return;
    }

    displayAssessments();

    int id;

    printf("\nEnter Assessment ID to mark completed: ");

    if (scanf("%d", &id) != 1) {
        clearInput();
        printf("Invalid ID.\n");
        return;
    }

    clearInput();

    for (int i = 0; i < assessmentCount; i++) {
        if (assessments[i].id == id) {
            if (assessments[i].completed) {
                printf("Assessment is already completed.\n");
                return;
            }

            assessments[i].completed = 1;

            saveData();

            printf("\nAssessment marked as COMPLETED!\n");
            return;
        }
    }

    printf("Assessment ID not found.\n");
}

void updateAssessment(void) {
    if (assessmentCount == 0) {
        printf("No assessments available.\n");
        return;
    }

    displayAssessments();

    int id;

    printf("\nEnter Assessment ID to update: ");

    if (scanf("%d", &id) != 1) {
        clearInput();
        printf("Invalid ID.\n");
        return;
    }

    clearInput();

    int index = -1;

    for (int i = 0; i < assessmentCount; i++) {
        if (assessments[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Assessment not found.\n");
        return;
    }

    Assessment *a = &assessments[index];

    printf("\nUpdating Assessment: %s\n", a->name);

    printf("New Assessment Name: ");

    char newName[MAX_NAME];
    readName(newName, MAX_NAME);

    if (strlen(newName) == 0 ||
        strchr(newName, '|') != NULL) {
        printf("Invalid name. Update cancelled.\n");
        return;
    }

    displayTopics();

    int topicId, day, duration;

    printf("New Topic ID: ");

    if (scanf("%d", &topicId) != 1 ||
        findTopic(topicId) == -1) {
        clearInput();
        printf("Invalid topic ID. Update cancelled.\n");
        return;
    }

    printf("New Assessment Day: ");

    if (scanf("%d", &day) != 1 ||
        day < 1 || day > 365) {
        clearInput();
        printf("Invalid day. Update cancelled.\n");
        return;
    }

    printf("New Duration (minutes): ");

    if (scanf("%d", &duration) != 1 ||
        duration <= 0 || duration > 1440) {
        clearInput();
        printf("Invalid duration. Update cancelled.\n");
        return;
    }

    clearInput();

    strcpy(a->name, newName);
    a->topicId = topicId;
    a->day = day;
    a->duration = duration;

    saveData();

    printf("\nAssessment updated successfully!\n");
}

void deleteAssessment(void) {
    if (assessmentCount == 0) {
        printf("No assessments available.\n");
        return;
    }

    displayAssessments();

    int id;

    printf("\nEnter Assessment ID to delete: ");

    if (scanf("%d", &id) != 1) {
        clearInput();
        printf("Invalid ID.\n");
        return;
    }

    clearInput();

    int index = -1;

    for (int i = 0; i < assessmentCount; i++) {
        if (assessments[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Assessment not found.\n");
        return;
    }

    for (int i = index; i < assessmentCount - 1; i++) {
        assessments[i] = assessments[i + 1];
    }

    assessmentCount--;

    saveData();

    printf("Assessment deleted successfully!\n");
}

void assessmentMenu(void) {
    int choice;

    do {
        printf("\n");
        printf("========================================\n");
        printf("        ASSESSMENT MANAGEMENT\n");
        printf("========================================\n");

        printf("1. Add New Assessment\n");
        printf("2. View All Assessments\n");
        printf("3. Update Assessment\n");
        printf("4. Mark Assessment as Completed\n");
        printf("5. Delete Assessment\n");
        printf("0. Return to Main Menu\n");

        printf("----------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInput();
            printf("Invalid input.\n");
            continue;
        }

        clearInput();

        switch (choice) {
            case 1:
                addAssessment();
                break;

            case 2:
                displayAssessments();
                break;

            case 3:
                updateAssessment();
                break;

            case 4:
                completeAssessment();
                break;

            case 5:
                deleteAssessment();
                break;

            case 0:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);
}