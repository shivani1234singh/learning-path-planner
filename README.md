Personalized Learning Path and Assessment Planner

1. Project Overview

The Personalized Learning Path and Assessment Planner is a menu-driven application developed using the C programming language.

The application helps students organize their learning activities, prioritize academic topics, allocate study hours, track mastery levels and manage assessments.

It demonstrates the practical application of Design and Analysis of Algorithms (DAA) in an educational planning environment.

2. Objectives
Generate personalized topic priorities.
Manage learning topics and prerequisites.
Optimize study-hour allocation.
Schedule and track assessments.
Monitor academic progress.
Demonstrate 12 DAA algorithms.
Export learning analytics as CSV reports.
3. Technologies
Programming Language: C
Compiler: GCC
Standard: C11
Data Structures: Structures, Arrays, Matrices and Graphs
Algorithms: Sorting, Searching, Divide and Conquer, Greedy, Dynamic Programming, Backtracking and Branch and Bound.
Data Storage: Text Files
Report Format: CSV
4. Implemented Algorithms
Algorithm	Technique
Merge Sort	Divide and Conquer
Binary Search	Searching
Maximum Subarray	Divide and Conquer
Activity Selection	Greedy
Huffman Coding	Greedy
Dijkstra	Greedy / Graph
Prim	Greedy / Graph
Floyd-Warshall	Dynamic Programming
0/1 Knapsack	Dynamic Programming
Fractional knapsack  Greedy
LCS	Dynamic Programming
N-Queens	Backtracking
Least-Cost Branch and Bound	Branch and Bound
5. Folder Structure
text
Personalized\_Learning\_Planner/
|
|-- src/
|   |-- main.c
|   |-- planner.c
|   |-- algorithms.c
|   |-- planner.h
|
|-- data/
|   |-- relationships.txt
|   |-- topics.txt
|   |-- assessments.txt
|
|-- reports/
|
|-- Makefile
|-- README.md
|-- DESIGN.md
6. Installation and Execution
Linux

Install GCC and Make:

bash
sudo apt update
sudo apt install gcc make



Navigate to the project directory:

bash
cd Personalized\_Learning\_Planner



Compile:

bash
make



Execute:

bash
./learning\_planner

Windows

Using MinGW GCC:

bash
gcc -std=c11 -Wall -Wextra -O2 src/main.c src/planner.c src/algorithms.c -o learning\_planner.exe



Execute:

bash
learning\_planner.exe

7. Application Modules
Topic Management
Prerequisite Relationship Management
Personalized Learning Path Generation
Study Time Optimization
Assessment Management
Learning Progress Tracking
Analytics Dashboard
DAA Algorithm Laboratory
Data Persistence
CSV Report Generation
8. Data Storage

Topic and assessment records are saved in text files inside the data directory.

Generated CSV reports are stored inside the reports directory.

The graph relationships are currently maintained in application memory and must be entered again after restarting.

9. Limitations
The application uses fixed-size arrays.
The learning path is priority-based rather than a complete prerequisite-constrained topological schedule.
Knapsack and Branch and Bound optimize topic value under a study-hour budget; prerequisite dependencies are not enforced by these two optimization routines.
Assessment scheduling is currently manual.
The Huffman module demonstrates coding-tree construction rather than full file compression.
10. Future Enhancements
Add topological sorting for prerequisite-aware learning paths.
Add automatic assessment scheduling.
Persist prerequisite graphs.
Add JSON export.
Add benchmark reports for different input sizes.
Add a graphical user interface.
Introduce personalized recommendations using historical performance.
11. Conclusion

This project demonstrates how fundamental DAA techniques can be integrated into an educational planning application.

It combines algorithmic problem-solving with a practical student-oriented system and provides an environment for comparing different algorithmic approaches.

