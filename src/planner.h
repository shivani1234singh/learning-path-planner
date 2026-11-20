
#ifndef PLANNER_H
#define PLANNER_H

#include <stdio.h>

#define MAX_TOPICS 100
#define MAX_ASSESSMENTS 100
#define MAX_SESSIONS 100
#define MAX_NAME 60
#define INF 1000000000

typedef struct {
    int id;
    char name[MAX_NAME];
    int hours;
    int value;
    int mastery;
    int deadline;
} Topic;

typedef struct {
    int id;
    char name[MAX_NAME];
    int topicId;
    int day;
    int duration;
    int completed;
} Assessment;

typedef struct {
    int start;
    int end;
    int id;
} StudySession;

extern Topic topics[MAX_TOPICS];
extern Assessment assessments[MAX_ASSESSMENTS];
extern StudySession sessions[MAX_SESSIONS];

extern int topicCount;
extern int assessmentCount;
extern int sessionCount;
extern int graph[MAX_TOPICS][MAX_TOPICS];

void addTopic(void);
void displayTopics(void);
void addPrerequisite(void);
void generateLearningPath(void);
void allocateStudyTime(void);
void addAssessment(void);
void displayAssessments(void);
void updateAssessment(void);
void completeAssessment(void);
void deleteAssessment(void);
void assessmentMenu(void);
void updateProgress(void);
void showDashboard(void);
void saveData(void);
void loadData(void);
void saveGraph(void);
void loadGraph(void);
void exportReport(void);

void mergeSort(Topic arr[], int left, int right);
int binarySearch(Topic arr[], int n, int id);

int maxSubarray(int arr[], int left, int right);
void activitySelection(void);
void huffmanDemo(void);

void dijkstra(int source);
void prim(void);
void floydWarshall(void);

void knapsack(int capacity);
int lcs(char *a, char *b);
void fractionalKnapsack(int capacity);

void nQueens(int n);
void branchAndBound(int capacity);

void algorithmMenu(void);

#endif
