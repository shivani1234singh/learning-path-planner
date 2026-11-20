
#include "planner.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>

extern Topic topics[MAX_TOPICS];
extern int topicCount;
extern int graph[MAX_TOPICS][MAX_TOPICS];

/* 1. MERGE SORT */

void merge(Topic arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Topic *L = malloc(n1 * sizeof(Topic));
    Topic *R = malloc(n2 * sizeof(Topic));

    if (!L || !R) {
        free(L);
        free(R);
        return;
    }

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].value >= R[j].value)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(Topic arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/* 2. BINARY SEARCH */

int binarySearch(Topic arr[], int n, int id) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid].id == id)
            return mid;

        if (arr[mid].id < id)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/* 3. MAXIMUM SUBARRAY - DIVIDE AND CONQUER */

int maxCrossingSum(int arr[], int left, int mid, int right) {
    int sum = 0;
    int leftSum = INT_MIN;

    for (int i = mid; i >= left; i--) {
        sum += arr[i];
        if (sum > leftSum)
            leftSum = sum;
    }

    sum = 0;
    int rightSum = INT_MIN;

    for (int i = mid + 1; i <= right; i++) {
        sum += arr[i];
        if (sum > rightSum)
            rightSum = sum;
    }

    return leftSum + rightSum;
}

int maxSubarray(int arr[], int left, int right) {
    if (left == right)
        return arr[left];

    int mid = left + (right - left) / 2;

    int a = maxSubarray(arr, left, mid);
    int b = maxSubarray(arr, mid + 1, right);
    int c = maxCrossingSum(arr, left, mid, right);

    int result = a > b ? a : b;
    return result > c ? result : c;
}

/* 4. ACTIVITY SELECTION */

void activitySelection(void) {
    int n;

    printf("\nNumber of study sessions: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SESSIONS) {
        printf("Invalid number.\n");
        return;
    }

    StudySession a[MAX_SESSIONS];

    for (int i = 0; i < n; i++) {
        printf("Session %d start and end time: ", i + 1);

        if (scanf("%d %d", &a[i].start, &a[i].end) != 2 ||
            a[i].start < 0 || a[i].end <= a[i].start) {
            printf("Invalid interval.\n");
            return;
        }

        a[i].id = i + 1;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j].end > a[j + 1].end) {
                StudySession temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("\nSelected study sessions:\n");

    int lastEnd = -1;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (a[i].start >= lastEnd) {
            printf("Session %d: %d - %d\n",
                   a[i].id, a[i].start, a[i].end);

            lastEnd = a[i].end;
            count++;
        }
    }

    printf("Maximum compatible sessions: %d\n", count);
}

/* 5. HUFFMAN CODING */

typedef struct HuffNode {
    char ch;
    int freq;
    struct HuffNode *left, *right;
} HuffNode;

HuffNode *newNode(char ch, int freq) {
    HuffNode *node = malloc(sizeof(HuffNode));

    if (!node)
        return NULL;

    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;

    return node;
}

void printCodes(HuffNode *root, char code[], int depth) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        code[depth] = '\0';
        printf("%c : %s\n", root->ch, code);
        return;
    }

    if (depth >= 254)
        return;

    code[depth] = '0';
    printCodes(root->left, code, depth + 1);

    code[depth] = '1';
    printCodes(root->right, code, depth + 1);
}

void freeHuffman(HuffNode *root) {
    if (!root)
        return;

    freeHuffman(root->left);
    freeHuffman(root->right);
    free(root);
}

void huffmanDemo(void) {
    int n;
    printf("\nNumber of symbols (2-26): ");

    if (scanf("%d", &n) != 1 || n < 2 || n > 26) {
        printf("Invalid input.\n");
        return;
    }

    HuffNode *nodes[52] = {0};
    int count = n;

    for (int i = 0; i < n; i++) {
        char ch;
        int freq;

        printf("Enter symbol and frequency: ");

        if (scanf(" %c %d", &ch, &freq) != 2 || freq <= 0) {
            printf("Invalid symbol or frequency.\n");
            for (int j = 0; j < i; j++)
                freeHuffman(nodes[j]);
            return;
        }

        nodes[i] = newNode(ch, freq);

        if (!nodes[i]) {
            printf("Memory allocation failed.\n");
            for (int j = 0; j < i; j++)
                freeHuffman(nodes[j]);
            return;
        }
    }

    while (count > 1) {
        int first = -1, second = -1;

        for (int i = 0; i < count; i++) {
            if (!nodes[i]) continue;

            if (first == -1 || nodes[i]->freq < nodes[first]->freq) {
                second = first;
                first = i;
            } else if (second == -1 ||
                       nodes[i]->freq < nodes[second]->freq) {
                second = i;
            }
        }

        if (first == -1 || second == -1)
            break;

        HuffNode *parent = newNode(
            '*', nodes[first]->freq + nodes[second]->freq
        );

        if (!parent) {
            printf("Memory allocation failed.\n");
            for (int i = 0; i < count; i++)
                freeHuffman(nodes[i]);
            return;
        }

        parent->left = nodes[first];
        parent->right = nodes[second];

        if (first > second) {
            int temp = first;
            first = second;
            second = temp;
        }

        nodes[first] = parent;

        for (int i = second; i < count - 1; i++)
            nodes[i] = nodes[i + 1];

        nodes[count - 1] = NULL;
        count--;
    }

    char code[256];
    printf("\nHuffman Codes:\n");
    printCodes(nodes[0], code, 0);
    freeHuffman(nodes[0]);
}

/* 6. DIJKSTRA */

void dijkstra(int source) {
    if (source < 0 || source >= topicCount) {
        printf("Invalid source.\n");
        return;
    }

    int dist[MAX_TOPICS];
    int visited[MAX_TOPICS] = {0};

    for (int i = 0; i < topicCount; i++)
        dist[i] = INF;

    dist[source] = 0;

    for (int count = 0; count < topicCount; count++) {
        int u = -1;

        for (int i = 0; i < topicCount; i++) {
            if (!visited[i] &&
                (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        if (u == -1 || dist[u] == INF)
            break;

        visited[u] = 1;

        for (int v = 0; v < topicCount; v++) {
            if (!visited[v] && graph[u][v] > 0 &&
                dist[u] <= INF - graph[u][v] &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nShortest learning routes from %s:\n",
           topics[source].name);

    for (int i = 0; i < topicCount; i++) {
        if (dist[i] == INF)
            printf("%s : Unreachable\n", topics[i].name);
        else
            printf("%s : %d\n", topics[i].name, dist[i]);
    }
}

/* 7. PRIM'S MINIMUM SPANNING TREE */

void prim(void) {
    if (topicCount < 2) {
        printf("At least two topics are required.\n");
        return;
    }

    int key[MAX_TOPICS], parent[MAX_TOPICS];
    int used[MAX_TOPICS] = {0};

    for (int i = 0; i < topicCount; i++) {
        key[i] = INF;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < topicCount; count++) {
        int u = -1;

        for (int i = 0; i < topicCount; i++) {
            if (!used[i] &&
                (u == -1 || key[i] < key[u]))
                u = i;
        }

        if (u == -1 || key[u] == INF) {
            printf("Graph is disconnected; MST does not exist.\n");
            return;
        }

        used[u] = 1;

        for (int v = 0; v < topicCount; v++) {
            if (!used[v] && graph[u][v] > 0 &&
                graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int total = 0;

    printf("\nMinimum Spanning Tree:\n");

    for (int i = 1; i < topicCount; i++) {
        printf("%s -- %s : %d\n",
               topics[parent[i]].name,
               topics[i].name, key[i]);
        total += key[i];
    }

    printf("Total network cost: %d\n", total);
}

/* 8. FLOYD-WARSHALL */

void floydWarshall(void) {
    int dist[MAX_TOPICS][MAX_TOPICS];

    for (int i = 0; i < topicCount; i++)
        for (int j = 0; j < topicCount; j++)
            dist[i][j] = (i == j) ? 0 :
                (graph[i][j] > 0 ? graph[i][j] : INF);

    for (int k = 0; k < topicCount; k++)
        for (int i = 0; i < topicCount; i++)
            for (int j = 0; j < topicCount; j++)
                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    printf("\nAll-pairs shortest distance matrix:\n");

    for (int i = 0; i < topicCount; i++) {
        for (int j = 0; j < topicCount; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

/* 9. 0/1 KNAPSACK */


void knapsack(int capacity) {
    if (capacity < 0 || capacity > 5000) {
        printf("Capacity must be between 0 and 5000.\n");
        return;
    }

    size_t cols = (size_t)capacity + 1;
    size_t rows = (size_t)topicCount + 1;

    int *dp = calloc(rows * cols, sizeof(int));

    if (!dp) {
        printf("Memory allocation failed.\n");
        return;
    }

    #define DP(i, w) dp[(size_t)(i) * cols + (w)]

    for (int i = 1; i <= topicCount; i++) {
        for (int w = 0; w <= capacity; w++) {

            DP(i, w) = DP(i - 1, w);

            if (topics[i - 1].hours <= w) {
                int include =
                    topics[i - 1].value +
                    DP(i - 1, w - topics[i - 1].hours);

                if (include > DP(i, w))
                    DP(i, w) = include;
            }
        }
    }

    printf("\nMaximum learning value: %d\n",
           DP(topicCount, capacity));

    printf("Selected topics:\n");

    int w = capacity;

    for (int i = topicCount; i > 0; i--) {
        if (DP(i, w) != DP(i - 1, w)) {
            printf("- %s (%d hours)\n",
                   topics[i - 1].name,
                   topics[i - 1].hours);

            w -= topics[i - 1].hours;
        }
    }

    free(dp);

    #undef DP
}



typedef struct {
    int index;
    double ratio;
} FractionItem;

void fractionalKnapsack(int capacity) {

    if (capacity < 0) {
        printf("Invalid capacity.\n");
        return;
    }

    if (topicCount == 0) {
        printf("No topics available.\n");
        return;
    }

    FractionItem items[MAX_TOPICS];

    for (int i = 0; i < topicCount; i++) {

        items[i].index = i;

        items[i].ratio =
            topics[i].hours > 0
            ? (double)topics[i].value / topics[i].hours
            : 0;
    }

    // Sort topics by value per hour (descending).
    for (int i = 0; i < topicCount - 1; i++) {

        for (int j = 0; j < topicCount - i - 1; j++) {

            if (items[j].ratio < items[j + 1].ratio) {

                FractionItem temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    double totalValue = 0;
    int remaining = capacity;

    printf("\nFRACTIONAL KNAPSACK STUDY ALLOCATION\n");

    for (int i = 0; i < topicCount && remaining > 0; i++) {

        int idx = items[i].index;
        int required = topics[idx].hours;

        if (required <= 0 || topics[idx].value <= 0)
            continue;

        int allocated;

        if (required <= remaining)
            allocated = required;
        else
            allocated = remaining;

        double fraction = (double)allocated / required;

        double earnedValue = fraction * topics[idx].value;

        printf("\nTopic: %s\n", topics[idx].name);
        printf("Allocated Hours: %d / %d\n",
               allocated, required);
        printf("Completion: %.2f%%\n", fraction * 100);
        printf("Learning Value: %.2f\n", earnedValue);

        totalValue += earnedValue;
        remaining -= allocated;
    }

    printf("\nTotal Allocated Hours: %d\n",
           capacity - remaining);

    printf("Maximum Learning Value: %.2f\n",
           totalValue);
}


/* 10. LONGEST COMMON SUBSEQUENCE */

int lcs(char *a, char *b) {
    int m = (int)strlen(a);
    int n = (int)strlen(b);

    if (m > 500 || n > 500)
        return -1;

    int dp[501][501] = {{0}};

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] =
                    dp[i - 1][j] > dp[i][j - 1]
                    ? dp[i - 1][j] : dp[i][j - 1];
        }
    }

    return dp[m][n];
}

/* 11. N-QUEENS BACKTRACKING */

int queenBoard[15][15];
int queenSolutions = 0;

int isSafe(int row, int col, int n) {
    for (int i = 0; i < row; i++)
        if (queenBoard[i][col])
            return 0;

    for (int i = row - 1, j = col - 1;
         i >= 0 && j >= 0; i--, j--)
        if (queenBoard[i][j])
            return 0;

    for (int i = row - 1, j = col + 1;
         i >= 0 && j < n; i--, j++)
        if (queenBoard[i][j])
            return 0;

    return 1;
}

void solveQueens(int row, int n) {
    if (row == n) {
        queenSolutions++;
        printf("\nSolution %d:\n", queenSolutions);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%c ", queenBoard[i][j] ? 'Q' : '.');
            printf("\n");
        }
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col, n)) {
            queenBoard[row][col] = 1;
            solveQueens(row + 1, n);
            queenBoard[row][col] = 0;
        }
    }
}

void nQueens(int n) {
    if (n < 1 || n > 12) {
        printf("Choose N between 1 and 12.\n");
        return;
    }

    memset(queenBoard, 0, sizeof(queenBoard));
    queenSolutions = 0;

    solveQueens(0, n);

    printf("\nTotal solutions: %d\n", queenSolutions);
}

/* 12. LEAST-COST BRANCH AND BOUND */

static int bbBest;
static int bbCapacity;
static int bbOrder[MAX_TOPICS];
static int bbChosen[MAX_TOPICS];
static int bbBestChosen[MAX_TOPICS];

static void sortByRatio(void) {
    for (int i = 0; i < topicCount; i++)
        bbOrder[i] = i;

    for (int i = 0; i < topicCount - 1; i++) {
        for (int j = 0; j < topicCount - i - 1; j++) {
            int a = bbOrder[j], b = bbOrder[j + 1];

            long long left =
                (long long)topics[a].value *
                (topics[b].hours > 0 ? topics[b].hours : 1);

            long long right =
                (long long)topics[b].value *
                (topics[a].hours > 0 ? topics[a].hours : 1);

            if (left < right) {
                int temp = bbOrder[j];
                bbOrder[j] = bbOrder[j + 1];
                bbOrder[j + 1] = temp;
            }
        }
    }
}

static double upperBound(int index, int remaining, int value) {
    double bound = value;

    for (int i = index; i < topicCount; i++) {
        Topic t = topics[bbOrder[i]];

        if (t.hours <= remaining) {
            remaining -= t.hours;
            bound += t.value;
        } else {
            if (t.hours > 0)
                bound += (double)t.value * remaining / t.hours;
            break;
        }
    }

    return bound;
}

static void bbSearch(int index, int remaining, int value) {
    if (index == topicCount) {
        if (value > bbBest) {
            bbBest = value;
            memcpy(bbBestChosen, bbChosen,
                   sizeof(bbBestChosen));
        }
        return;
    }

    if (upperBound(index, remaining, value) <= bbBest)
        return;

    int original = bbOrder[index];
    Topic t = topics[original];

    if (t.hours <= remaining) {
        bbChosen[original] = 1;
        bbSearch(index + 1, remaining - t.hours,
                 value + t.value);
        bbChosen[original] = 0;
    }

    bbSearch(index + 1, remaining, value);
}

void branchAndBound(int capacity) {
    if (capacity < 0) {
        printf("Invalid capacity.\n");
        return;
    }

    if (topicCount == 0) {
        printf("Add topics first.\n");
        return;
    }

    memset(bbChosen, 0, sizeof(bbChosen));
    memset(bbBestChosen, 0, sizeof(bbBestChosen));

    bbBest = 0;
    bbCapacity = capacity;

    sortByRatio();
    bbSearch(0, bbCapacity, 0);

    printf("\nBranch and Bound optimal value: %d\n", bbBest);
    printf("Selected topics:\n");

    for (int i = 0; i < topicCount; i++)
        if (bbBestChosen[i])
            printf("- %s\n", topics[i].name);
}
