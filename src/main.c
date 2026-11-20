
#include "planner.h"
#include <stdlib.h>
#include <string.h>

static void clearInput(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int compareID(const void *a, const void *b) {
    const Topic *x = (const Topic *)a;
    const Topic *y = (const Topic *)b;

    return (x->id > y->id) - (x->id < y->id);
}

static void searchTopic(void) {
    if (topicCount == 0) {
        printf("No topics available.\n");
        return;
    }

    Topic sorted[MAX_TOPICS];

    memcpy(sorted, topics, topicCount * sizeof(Topic));

    qsort(sorted, topicCount, sizeof(Topic), compareID);

    int id;

    printf("Enter topic ID to search: ");

    if (scanf("%d", &id) != 1) {
        clearInput();
        printf("Invalid ID.\n");
        return;
    }

    clearInput();

    int pos = binarySearch(sorted, topicCount, id);

    if (pos == -1) {
        printf("Topic not found.\n");
    } else {
        printf("\nTopic Found!\n");
        printf("Name: %s\n", sorted[pos].name);
        printf("Study Hours: %d\n", sorted[pos].hours);
        printf("Mastery: %d%%\n", sorted[pos].mastery);
    }
}

static void runDijkstra(void) {
    int id;

    displayTopics();

    printf("\nEnter starting topic ID: ");

    if (scanf("%d", &id) != 1) {
        clearInput();
        return;
    }

    clearInput();

    int index = -1;

    for (int i = 0; i < topicCount; i++)
        if (topics[i].id == id)
            index = i;

    if (index == -1) {
        printf("Invalid topic ID.\n");
        return;
    }

    dijkstra(index);
}

static void runMaxSubarray(void) {
    int n;

    printf("Enter number of daily productivity values (1-100): ");

    if (scanf("%d", &n) != 1 || n < 1 || n > 100) {
        clearInput();
        printf("Invalid size.\n");
        return;
    }

    int a[100];

    printf("Enter productivity values (positive or negative):\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            clearInput();
            printf("Invalid value.\n");
            return;
        }
    }

    clearInput();

    printf("Maximum continuous productivity sum: %d\n",
           maxSubarray(a, 0, n - 1));
}

static void runLCS(void) {
    char planned[501], actual[501];

    printf("Enter planned topic sequence: ");

    if (scanf("%500s", planned) != 1) {
        clearInput();
        return;
    }

    printf("Enter completed topic sequence: ");

    if (scanf("%500s", actual) != 1) {
        clearInput();
        return;
    }

    clearInput();

    int result = lcs(planned, actual);

    if (result < 0) {
        printf("Sequence too long.\n");
        return;
    }

    printf("Common sequence length: %d\n", result);
    printf("Sequence completion similarity: %.2f%%\n",
           strlen(planned) == 0 ? 0.0 :
           100.0 * result / strlen(planned));
}

void algorithmMenu(void) {
    int choice;

    do {
        printf("\n====================================\n");
        printf("       DAA ALGORITHM LAB\n");
        printf("====================================\n");

        printf("1. Merge Sort\n");
        printf("2. Binary Search\n");
        printf("3. Maximum Subarray\n");
        printf("4. Activity Selection\n");
        printf("5. Huffman Coding\n");
        printf("6. Dijkstra Algorithm\n");
        printf("7. Prim Minimum Spanning Tree\n");
        printf("8. Floyd-Warshall Algorithm\n");
        printf("9. 0/1 Knapsack\n");
        printf("10. Longest Common Subsequence\n");
        printf("11. N-Queens\n");
        printf("12. Least-Cost Branch and Bound\n");
        printf("13. Fractional Knapsack\n");
        printf("0. Back to Main Menu\n");

        printf("\nEnter choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInput();
            printf("Invalid input.\n");
            continue;
        }

        clearInput();

        switch (choice) {
            case 1: {
                if (topicCount == 0) {
                    printf("Add topics first.\n");
                    break;
                }

                Topic sorted[MAX_TOPICS];

                memcpy(sorted, topics,
                topicCount * sizeof(Topic));

                mergeSort(sorted, 0, topicCount - 1);

                printf("Topics sorted by importance:\n");

                for (int i = 0; i < topicCount; i++) {
                printf("%d. %s - Importance: %d\n",
                i + 1, sorted[i].name, sorted[i].value);
                }

                break;
            } 
            case 2:
                searchTopic();
                break;

            case 3:
                runMaxSubarray();
                break;

            case 4:
                activitySelection();
                break;

            case 5:
                huffmanDemo();
                break;

            case 6:
                runDijkstra();
                break;

            case 7:
                prim();
                break;

            case 8:
                floydWarshall();
                break;

            case 9: {
                int capacity;
                printf("Enter available study hours: ");

                if (scanf("%d", &capacity) != 1 ||
                    capacity < 0 || capacity > 100000) {
                    clearInput();
                    printf("Invalid capacity.\n");
                    break;
                }

                clearInput();
                knapsack(capacity);
                break;
            }

            case 10:
                runLCS();
                break;

            case 11: {
                int n;
                printf("Enter N for N-Queens: ");

                if (scanf("%d", &n) != 1) {
                    clearInput();
                    break;
                }

                clearInput();
                nQueens(n);
                break;
            }

            case 12: {
                int capacity;
                printf("Enter available study hours: ");

                if (scanf("%d", &capacity) != 1 ||
                    capacity < 0) {
                    clearInput();
                    printf("Invalid capacity.\n");
                    break;
                }

                clearInput();
                branchAndBound(capacity);
                break;
            }
            case 13: {
                int capacity;

                printf("Enter available study hours: ");

                if (scanf("%d", &capacity) != 1 || capacity < 0) {
                clearInput();
                printf("Invalid capacity.\n");
                break;
                }

                clearInput();

                fractionalKnapsack(capacity);
                break;
            }

            case 0:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);
}

int main(void) {
    loadData();
    loadGraph();
    int choice;

    printf("\n");
    printf("====================================================\n");
    printf("  PERSONALIZED LEARNING PATH & ASSESSMENT PLANNER\n");
    printf("====================================================\n");
    printf("             DAA PROJECT - C LANGUAGE\n");
    printf("====================================================\n");

    do {
        printf("\n");
        printf("----------------------------------------------------\n");
        printf("                    MAIN MENU\n");
        printf("----------------------------------------------------\n");

        printf("1.  Add Student Learning Topic\n");
        printf("2.  Display All Topics\n");
        printf("3.  Add Topic Relationship / Prerequisite\n");
        printf("4.  Generate Personalized Learning Path\n");
        printf("5.  Allocate Study Time\n");
        printf("6.  Assessment Management\n");
        printf("7.  View Assessment Schedule\n");
        printf("8.  Update Learning Progress\n");
        printf("9.  Learning Analytics Dashboard\n");
        printf("10. DAA Algorithm Demonstrations\n");
        printf("11. Save Application Data\n");
        printf("12. Load Application Data\n");
        printf("13. Export Learning Report (CSV)\n");
        printf("0.  Exit\n");

        printf("----------------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInput();
            printf("Please enter a valid number.\n");
            continue;
        }

        clearInput();

        switch (choice) {
            case 1:
                addTopic();
                break;

            case 2:
                displayTopics();
                break;

            case 3:
                addPrerequisite();
                break;

            case 4:
                generateLearningPath();
                break;

            case 5:
                allocateStudyTime();
                break;
            
            case 6:
                assessmentMenu();
                break;

            case 7:
                displayAssessments();
                break;
        
            case 8:
                updateProgress();
                break;

            case 9:
                showDashboard();
                break;

            case 10:
                algorithmMenu();
                break;

            case 11:
                saveData();
                saveGraph();
                break;

            case 12:
                loadData();
                loadGraph();
                break;

            case 13:
                exportReport();
                break;

            case 0:
                printf("\nSaving application data...\n");
                saveData();
                saveGraph();
                printf("Thank you for using the planner!\n");
                break;
            

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}
