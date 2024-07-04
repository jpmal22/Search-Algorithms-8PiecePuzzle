# 8 Piece Slide Puzzle Solver

This project is a comprehensive C++ application designed to solve the 8-puzzle problem, a classic problem in artificial intelligence. The application leverages advanced search algorithms to find the solution to any given 8-puzzle configuration and provides a graphical interface for visualizing the solution process step-by-step.

## Features

Graphical Visualization: Utilizes a custom graphical user interface to display the puzzle and animate the step-by-step solution, providing a clear and interactive way to understand how the puzzle is solved.

Multiple Search Algorithms: Implements various search algorithms including Uniform Cost Search, A* with Misplaced Tile heuristic, and A* with Manhattan Distance heuristic, allowing users to compare the efficiency and effectiveness of these methods.

Dynamic Input Handling: Users can input any valid starting state of the puzzle, and the application will efficiently find and display the solution.
Performance Metrics: The application provides detailed statistics about the solution process, such as number of nodes expanded, maximum queue size, and total runtime, aiding in performance analysis.

## Technologies

* C++: Core programming language used for developing the application, ensuring efficient algorithm implementation.
* Graphical Library Integration: Integrates with a graphical library suitable for rendering simple 2D graphics, making the puzzle visualization intuitive and responsive.
* Makefile: Utilizes a Makefile for straightforward compilation and execution, simplifying build processes across different development environments.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

A C++ compiler like GCC or Clang.

Graphic library dependencies.

Make utility for building the application.

### Installation

git clone https://github.com/jpmal22/Search-Algorithms-8PiecePuzzle

cd project folder name

Run the makefile - run make in the command line or depending on which C++ compiler you used. I have MinGW - run mingw32-make to make the executable file. 

## Usage

This project has 3 modes to run - single run, animate run, and batch run. 

Details to run each mode in the command line:

Single run: 

This allows you to run a single search algorithm to solve the 8-piece puzzle. 

The command line arguments are the executable file "search.exe", the mode to run "single_run", the algorithm you want to use "uc_explist", the initial state of the puzzle "608435127", and the goal state of the puzzle "123456780".

examples: 

search.exe single_run uc_explist 608435127 123456780
search.exe single_run astar_explist_manhattan 608435127 123456780
search.exe single_run astar_explist_misplacedtiles 608435127 123456780

Animate run:

This triggers the graphics component of the project. Takes similar parameters in the command line as single_run:

search.exe animate_run astar_explist_manhattan 608435127 123456780

Batch run:

This mode tests the search allgorithm against the pre-defined test cases in main.cpp. You can run against one algorithm or all 3 implementations:

search.exe batch_run astar_explist_misplacedtiles 
search.exe batch_run uc_explist 
search.exe batch_run all 

## Authors

Implementation of the search algorithms: 

* **Paolo Alejandro** - https://github.com/jpmal22

Starter code files are by NH Reyes PHD, Massey University


