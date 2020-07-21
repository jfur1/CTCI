/*
    Imagine a robot sitting on the upper left corner of grid with R rows and C columns. The robot can only move in two directions,
    right and down, but certain cells are "off limits" such that the robot can not step on them. Design an algorithm to find a path
    for the robot from the top left to the bottom right.
*/
#include <iostream>
#include <algorithm>
#include <vector>
#define N_ROWS 6
#define N_COLS 5
using namespace std;

struct Point{
    int row;
    int col;
};

struct Point *newPoint(int row, int col){
    struct Point* tmp = (struct Point *)malloc(sizeof(struct Point));
    tmp->row = row;
    tmp->col = col;
    return tmp;
};

bool getPathUtility(bool maze[][N_COLS], int row, int col, vector<Point> path, vector<Point> hash){
    if(col < 0 || row < 0 || !maze[row][col])
        return false;
    
    Point *p = newPoint(row, col);

    // If we've already visited this cell, return
    for(int i = 0; i < hash.size(); i++){
        if(hash[i].col == p->col && hash[i].row == p->row)
            return false;
    }

    bool atOrigin = (row == 0) && (col == 0);

    if(atOrigin || getPathUtility(maze, row, col-1, path, hash) 
        || getPathUtility(maze, row-1, col, path, hash)){
            path.push_back(*p);
            return true;
        }
        
    hash.push_back(*p);
    return false;
}

vector<Point> getPath(bool maze[][N_COLS]){
    if(maze == NULL) return vector<Point>(0);

    // Vector of points to create a path
    vector<Point> *path = new vector<Point>;
    // Vector hash map of failed points
    vector<Point> *failedPoints = new vector<Point>;
    
    if(getPathUtility(maze, N_ROWS-1, N_COLS-1, *path, *failedPoints)){
        return *path;
    }
    cout << "Utility Function returned NULL\n";
    return vector<Point>(0);
}

void printPath(vector<Point> path){
    if(path.empty()) cout << "Empty Path!\n";
    for(int i = 0; i < path.size(); i++){
        Point p = path[i];
        int c = p.col; 
        int r = p.row;
        cout << "(" << r << ", " << c << ") -> ";
    }
    return;
}

int main(){
    bool maze[N_ROWS][N_COLS];
    int obstacleRow[] = {0, 1, 2, 2, 4, 5};
    int obstacleCol[] = {3, 1, 4, 5, 5, 6};
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

    vector<Point> path = getPath(maze);
    printPath(path);


    return 0;
}