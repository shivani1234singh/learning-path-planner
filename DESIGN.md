SOFTWARE DESIGN DOCUMENT
Personalized Learning Path and Assessment Planner

Project Domain: Educational Technology / Learning Analytics
Programming Language: C
Project Subject: Design and Analysis of Algorithms (DAA)
Implementation: Modular CLI-Based Application
Project Duration: 8 Weeks

1. INTRODUCTION

The Personalized Learning Path and Assessment Planner is a menu-driven application developed using the C programming language.

The purpose of this system is to help students organize their academic learning activities, prioritize subjects, allocate available study hours, manage assessments and monitor their learning progress.

The system applies various Design and Analysis of Algorithms techniques to solve practical problems related to educational planning and resource optimization.

The application integrates sorting, searching, divide and conquer, greedy algorithms, graph algorithms, dynamic programming, backtracking and branch and bound.

2. PROBLEM STATEMENT

Students often face difficulties in managing multiple academic subjects, identifying important topics, allocating limited study time and preparing for assessments.

Traditional study planning methods generally rely on manual decisions and do not provide systematic optimization.

This project addresses these problems by developing an algorithm-based learning planner that:

Organizes academic topics and their learning requirements.
Prioritizes topics according to importance and mastery.
Allocates study hours under limited time constraints.
Represents relationships between topics using graphs.
Tracks assessment schedules and learning progress.
Demonstrates different algorithmic approaches to optimization problems.
3. PROJECT OBJECTIVES

The main objectives are:

Develop a portable C-based learning management application.
Implement 13 major DAA algorithms.
Use appropriate data structures for storing learning information.
Generate priority-based personalized learning paths.
Optimize topic selection under limited study-hour budgets.
Represent topic relationships through weighted graphs.
Manage assessments and student progress.
Compare different algorithmic strategies.
Generate reports for learning analytics.
Demonstrate the practical relevance of DAA concepts.
4. SYSTEM REQUIREMENTS
4.1 Hardware Requirements
Processor: Intel Core i3 or equivalent.
RAM: Minimum 4 GB.
Storage: Minimum 100 MB free space.
Operating System: Windows, Linux or macOS.
4.2 Software Requirements
Programming Language: C.
Compiler: GCC.
C Standard: C11.
IDE: Visual Studio Code.
Build Tool: Make / GCC command line.
Data Storage: Text files.
Report Format: CSV.
5. SYSTEM ARCHITECTURE

The application follows a modular architecture consisting of four major layers.

5.1 Presentation Layer

Responsible for interaction between the user and the application.

Responsibilities:

Displaying the main menu.
Accepting student inputs.
Displaying learning plans.
Showing algorithm outputs.
Displaying analytics.

Implementation File: main.c

5.2 Application Layer

Responsible for managing the main functionalities of the learning planner.

Responsibilities:

Topic management.
Assessment management.
Progress tracking.
Learning path generation.
Study-time allocation.
Data management.

Implementation File: planner.c

5.3 Algorithm Layer

Responsible for implementing the DAA algorithms.

Responsibilities:

Sorting and searching.
Divide-and-conquer operations.
Greedy optimization.
Graph algorithms.
Dynamic programming.
Backtracking.
Branch and bound.

Implementation File: algorithms.c

5.4 Data Layer

Responsible for defining common structures and maintaining application data.

Responsibilities:

Topic records.
Assessment records.
Study session records.
Graph representation.
Function declarations.

Implementation File: `planner

