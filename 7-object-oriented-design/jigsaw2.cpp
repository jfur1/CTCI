/*
Author: John Furlong
Date: July 15, 2020
Description: Jigsaw
    Implement an NxN jigsaw puzzle. Design the data structures and explain an algorithm to solve the puzzle.
    You can assume that you have a fitsWith() method which, when passed two puzzle edges, returns true if the two edges
    belong together.
*/

/*
    Puzzle:
//               -1     -1    ...                           
//             ________________________
//          -1 |  1  |  1  |  2  |  2  |
//             |-----------------------|
//          -1 |  4  |  3  |  3  |  2  |
//             -------------------------
//         ... |  5  |  5  |  6  |  7  |
//             |-----------------------|
//             |  5  |  8  |  8  |  9  |
//             -------------------------
    Pieces:
        Each 'piece' object will have cardinal direction attributes (N,E,S,W). The algorithm to solve the puzzle will check whether 
        two pieces are adjacent in their respective directions. Note that 'piece' refers to a single tile.

    The question was a bit vague -- I've implemented the basic class structure required for a jigsaw puzzle, and the prompt only asked
    for an explanation for a solve() method. While there are many ways to solve the puzzle, the question says we're given a fitsWith()
    method, which indicates whether or not two pieces belong together. 
    Therefore, one brute force approach to solve the puzzle could be:
        For each piece/tile, call the fitsWith() method to find its cooresponding piece. 
    Alternatively, you could convert the grid into a graph, and use an adjacency list to determine which pieces fit together. 
    To reduce the time complexity to O(b^(d/2)), one could use a bidirectional search, assuming the branching factor is the same in both directions.
*/

#include <iostream>
using namespace std;

const int size = 4;

struct Tile{
    int value;
    int x, y;
    Tile* north;
    Tile* east;
    Tile* south;
    Tile* west;
};

class Jigsaw{
    private:
        Tile* puzzle[size][size];

    public:
        Jigsaw(int values[]){
            int k = 0;
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    Tile *newTile = new Tile;
                    newTile->value = values[k];
                    newTile->x = j;
                    newTile->y = i;
                    newTile->north = newTile->east = newTile->south = newTile->west = NULL;
                    puzzle[i][j] = newTile;
                    k++;
                }
            }
        }

        void print(){
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    cout << puzzle[i][j]->value << "\t";
                }
                cout << endl;
            }
        }

        void solve(){

        }
};

// Driver Code

int main(){

// Construct Example Puzzle:
///
//               -1     -1    ...
//             ________________________
//          -1 |  1  |  1  |  2  |  2  |
//             |-----------------------|
//          -1 |  4  |  3  |  3  |  2  |
//             -------------------------
//         ... |  5  |  5  |  6  |  7  |
//             |-----------------------|
//             |  5  |  8  |  8  |  9  |
//             -------------------------
//
//   Note: Perimeter pieces with no adjacent tiles have a cardinal value of -1.

    int vals[] = {1, 1, 2, 2, 4, 3, 3, 2, 5, 5, 6, 7, 5, 8, 8, 9};

    Jigsaw jigsaw(vals);
    jigsaw.print();

    return 0;
}