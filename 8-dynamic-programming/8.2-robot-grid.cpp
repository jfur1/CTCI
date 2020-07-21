/*
    Imagine a robot sitting on the upper left corner of grid with R rows and C columns. The robot can only move in two directions,
    right and down, but certain cells are "off limits" such that the robot can not step on them. Design an algorithm to find a path
    for the robot from the top left to the bottom right.

    Author: John Furlong

    Solution:
        Dyanmic programming approach using memoization. Our algorithm essentially looks at the adjacent points to a given point, and if one is invalid ignores it. Then, we look at those 
        points' adjacent points, and so on. This inevitably creates overlapping subproblems, which is why we use a hash map to memoize values that we've already computed.

    Time Complexity: O(rc) where r = # rows, and c = # cols
        - We have rc squares in our maze, and each gets visited once.

    Space Complexity: O(N) where N is the number of elements in the path vector.
        - While it would be nearly impossible to store every point on the maze in our path (no obstacles), our upper bound on extra space O(n) still holds.
*/
#include <iostream>
#include <algorithm>
#include <vector>
#define N_ROWS 6
#define N_COLS 5
using namespace std;

// Point Structure
struct Point{
    int row;
    int col;
};

// Utility Function to create a new point
struct Point *newPoint(int row, int col){
    struct Point* tmp = (struct Point *)malloc(sizeof(struct Point));
    tmp->row = row;
    tmp->col = col;
    return tmp;
};

// Utility Function used to print maze
void printMaze(bool maze[][N_COLS]){
    for(int i = 0; i < N_ROWS; i++){
        for(int j = 0; j < N_COLS; j++){
            if(maze[i][j]){
                  cout << " [ X ] ";
                  continue;
            }
            if(!maze[i][j]){
                cout << " [   ] ";
                continue;
            }
        }
        cout << endl;
    }
}

// Utility function to print the path returned by the core function
void printPath(vector<Point> path){
    int c = 0, r = 0;
    if(path.empty()) cout << "Empty Path!\n";
    for(int i = 0; i < path.size()-1; i++){
        Point p = path[i];
        c = p.col; 
        r = p.row;
        cout << "(" << r << ", " << c << ") -> ";
    }
    cout << "(" << path[path.size()-1].row << ", " << path[path.size()-1].col << ")\n";
    return;
}

// Utility Function used for recursion on the current path
bool getPathUtility(bool maze[][N_COLS], int row, int col, vector<Point> &path, vector<Point> &hash){
    // If invaild coordinates, or obstacle at this point, return false (can't move here)
    if(col < 0 || row < 0 || maze[row][col])
        return false;
    
    // Create a temp point to evaluate
    Point *p = newPoint(row, col);

    // If we've already visited this point, return
    for(int i = 0; i < hash.size(); i++){
        if(hash[i].col == p->col && hash[i].row == p->row)
            return false;
    }

    bool atOrigin = (row == 0) && (col == 0);

    // If there is a valid route (stored in path), then continue recursion
    if(atOrigin || getPathUtility(maze, row, col-1, path, hash) 
        || getPathUtility(maze, row-1, col, path, hash)){
            // cout << "Added point! Row: " << p->row << " Col: " << p->col << endl;
            // Add the valid point to our current path
            path.push_back(*p);
            return true;
        }
    // If there is no valid path from the current point to our goal, then add to our hashtable of invalid points
    cout << "Adding point to hash table\n";    
    hash.push_back(*p);
    return false;
}

// Core Function:
//  - path: stores the points (coordinates) that make up our path
//  - failedPoints: Acts as a hashtable (memoization) to avoid repeated calculations
vector<Point> getPath(bool maze[][N_COLS]){

    // Vector of points to create a path
    vector<Point> path;
    // Vector hash map of failed points
    vector<Point> failedPoints;
    
    if(getPathUtility(maze, N_ROWS-1, N_COLS-1, path, failedPoints)){
        // Return the value of path by reference
        return path;
    }
    cout << "Utility Function returned NULL\n";
    return vector<Point>(0);
}

// Driver Code
int main(){
    // Construct our maze with sample obstacles
    bool maze[N_ROWS][N_COLS];
    int obstacleRow[] = {0, 1, 2, 4, 5, 6};
    int obstacleCol[] = {3, 1, 4, 0, 0, 5};
    int k = 0;

    // Construct Maze with obstacles
    for(int i = 0; i < N_ROWS; i++){
        for(int j = 0; j < N_COLS; j++){
            int r = obstacleRow[k];
            int c = obstacleCol[k];
            if(r == i && c == j){
                k++;
                maze[i][j] = true;
                continue;
            }
            maze[i][j] = false;
        }
    }

    printMaze(maze);
    printPath(getPath(maze));

    return 0;
}