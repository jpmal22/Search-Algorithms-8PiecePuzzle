#include "algorithm.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

//struct to represent a state of the puzzle
struct State {
    string puzzle;  //current arrangement of puzzle tiles
    int zeroPosition; //Position of the 0/empty tile
    string moves; //sequence of moves eg ddllrudull
    int cost; //cost to reach this state
    int heuristictype; //heuristic value of the state

    //function that compares two states based on the total cost
    bool operator<(const State &s) const {
        return cost + heuristictype > s.cost + s.heuristictype;
    }
};

//function to check if the current state is the goal state
bool isGoal(const string &state, const string &goalState) {
    return state == goalState;
}

// function to calculate the number of misplaced tiles
int misplacedtiles(const string &state, const string &goalState) {

    int count = 0; //counter to keep track of the number of misplaced tiles

    //for loop that iterates over the state and goal state
    //count is incremented if the state and goal state are different at position [i]
    //meaning state at position [i] is a misplaced tile
    for (int i = 0; i < 9; i++) {
        if (state[i] != goalState[i] && state[i] != '0') count++;
    }
    return count;
}

// function to calculate the Manhattan distance for the tiles
int manhattan(const string &state, const string &goalState) {

    int distance = 0; //accumulates the total manhattan distance

    //for loop to iterate over each position in the state
    for (int i = 0; i < 9; i++) {

        //checks if state at position [i] is not 0 to avoid calculating the manhattan distance for 0
        if (state[i] != '0') {

            int goalIndex = goalState.find(state[i]); //find the position of the current tile in the goal state
            distance += abs(i / 3 - goalIndex / 3) + abs(i % 3 - goalIndex % 3);
            //above line computes the manhattan distance for the current tile in the state
            //it adds the vertical distance and the horizontal distance the tile needs to move
        }
    }
    return distance;
}

//function that takes a state of the puzzle and returns all possible successor states/moves
vector<State> successors(State current) {

    vector<State> states; //vector to store all successor states

    int x = current.zeroPosition % 3; //finds the column position of 0
    int y = current.zeroPosition / 3; //finds the row position of 0

    //arrays to show changes in the columns and rows
    const int px[] = {-1, 0, 1, 0};
    const int py[] = {0, 1, 0, -1};

    //array for the move sequences
    const char moveSequence[] = {'u', 'r', 'd', 'l'};

    //for loop to iterate through each possible move for a tile
    for (int i = 0; i < 4; ++i) {
        //calcualtes the new position of 0 if moved by i
        int nX = x + px[i];
        int nY = y + py[i];

        //if condition checks that the new move is still within bounds of the puzzle
        if (nX >= 0 && nX < 3 && nY >= 0 && nY < 3) {

            State newState = current; //create a copy of the current state
            newState.zeroPosition = nY * 3 + nX; //position of 0 is updated in newState
            swap(newState.puzzle[current.zeroPosition], newState.puzzle[newState.zeroPosition]); //swaps the tile 0 with the tile the drection 0 is moving to
            newState.moves += moveSequence[i]; //stores the move made
            newState.cost++; //increment cost to show the number of moves made
            states.push_back(newState); //generated successor state is added to the states vector
        }
    }
    return states;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  UC with Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////


string uc_explist(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                   float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions) {

    priority_queue<State> q; //priority to store states to be explored
    set<string> expandedList; //expanded list to keep track of all states visited

    //start time for the search algorithm
    clock_t startTime = clock();

    //creates an initial state using the puzzle string provided, finds 0
    //intitialises move string in the struct to 0, and sets the cost and heuristic to 0 for both.
    State initial = {initialState, initialState.find('0'), "", 0, 0};

    q.push(initial); //pushes the intitial state just created to priority q
    maxQLength = 1;
    numOfStateExpansions = 0;


    //while loop that executes the search if the priority q is not empty
    while (!q.empty()) {

        //gets and removes the state at the top of priority q
        State current = q.top();
        q.pop();

        if (expandedList.find(current.puzzle) != expandedList.end()) continue; //checks that the state has not been visited before and skips if it has

        //adds current state to the expanded list and increments numOfStateExpansions by 1
        expandedList.insert(current.puzzle);
        numOfStateExpansions++;

        //checks to see if the current state matched the goal state
        if (isGoal(current.puzzle, goalState)) {
            pathLength = current.moves.length(); //calculates the path length
            //calculates the running time of the algorithm by taking the current time it took to find the goal state
            //and subtracting the time the algorithm started at the top of the function
            actualRunningTime = float(clock() - startTime) / CLOCKS_PER_SEC;
            return current.moves; //exits the function and returns the sequence of moves
        }

        //expanding current state
        vector<State> succ = successors(current); //get the successor states of the current state
        //for loop that pushes the successor states ito the priority q
        for (const auto &s : succ) {
            if (expandedList.find(s.puzzle) == expandedList.end()) { //only added to the q if it has not been expanded before
                q.push(s);
            }
        }
        maxQLength = max(maxQLength, static_cast<int>(q.size())); //updates maxQLength
    }

    //returns an empty string and the time it took to execute the search if no solution was found
    actualRunningTime = float(clock() - startTime) / CLOCKS_PER_SEC;
    return "";
}


///////////////////////////////////////////////////////////////////////////////////////////
//
// Search Algorithm:  A* with the Strict Expanded List
//
// Move Generator:  
//
////////////////////////////////////////////////////////////////////////////////////////////

string aStar_ExpandedList(string const initialState, string const goalState, int& pathLength, int &numOfStateExpansions, int& maxQLength,
                               float &actualRunningTime, int &numOfDeletionsFromMiddleOfHeap, int &numOfLocalLoopsAvoided, int &numOfAttemptedNodeReExpansions, heuristicFunction heuristic){

   if (heuristic == misplacedTiles) { //returns the result of A* search using the misplaced tiles heuristic

       return aStar_search(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, misplacedtiles);

   } else if (heuristic == manhattanDistance) { //returns the result of A* using the sum of manhattan distance

       return aStar_search(initialState, goalState, pathLength, numOfStateExpansions, maxQLength, actualRunningTime, manhattan);
   }

}

//Function to run an A* search using the given heuristic
string aStar_search(const string &initialState, const string &goalState, int &pathLength, int &numOfStateExpansions, int& maxQLength, float &actualRunningTime,
             int (*heuristic)(const string&, const string&)) {

    priority_queue<State> q; //initialises priority q
    set<string> expandedList; //initialises expanded list

    clock_t startTime = clock(); //start time for algorithm

    //creates the starting state of the puzzle
    // calculates the heuristic value of the initial state using the heuristic type passed from aStar_ExpandedList
    State initial = {initialState, initialState.find('0'), "", 0, heuristic(initialState, goalState)};

    //pushes initial state into priority q
    q.push(initial);
    maxQLength = 1;
    numOfStateExpansions = 0;


    //while loop to execute the search while the q is not empty
    while (!q.empty()) {

        //gets and remove the state at the top of q
        State current = q.top();
        q.pop();

        if (expandedList.find(current.puzzle) != expandedList.end()) continue; //skip if the state has already been expanded

        //adds the current state to the expanded list and incremements the number of state expansions
        expandedList.insert(current.puzzle);
        numOfStateExpansions++;

        //checks if the current state is the gooal state and returns the path length and time it took to run the algorithm m
        if (isGoal(current.puzzle, goalState)) {
            pathLength = current.moves.length();
            actualRunningTime = float(clock() - startTime) / CLOCKS_PER_SEC;
            return current.moves;
        }


        vector<State> succ = successors(current); //gets a list of the successor states of the current state

        //for loop that calculates the heuristic value for each successor state of the current state
        // and adds pushes it into the q if it has not been expanded yet
        for (auto &s : succ) {
            if (expandedList.find(s.puzzle) == expandedList.end()) {
                s.heuristictype = heuristic(s.puzzle, goalState);
                q.push(s);
            }
        }
        maxQLength = max(maxQLength, static_cast<int>(q.size())); //updates maxQLength
    }

    //returns an empty string and the time it took to execute the search if no solution was found
    actualRunningTime = float(clock() - startTime) / CLOCKS_PER_SEC;
    return "";
}

