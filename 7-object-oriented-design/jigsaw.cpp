/*
Author: John Furlong
Date: June 12, 2020
Description: Jigsaw
    Implement an NxN jigsaw puzzle. Design the data structures and explain an algorithm to solve the puzzle.
    You can assume that you hace a fitsWith() method which, when passed two puzzle edges, returns true if the two edges
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
    
*/
#include <iostream>
using namespace std;

const int size = 4;

struct Piece{
    int value;
    int north;
    int east;
    int south;
    int west;
};
 
Piece* newPiece(int n, int e, int s, int w, int val){
    struct Piece* newPiece = (struct Piece*) malloc(sizeof(struct Piece));
    newPiece->value = val;
    newPiece->north = n;
    newPiece->east = e;
    newPiece->south = s;
    newPiece->west = w;
    return newPiece;
};

Piece* init_pieces(int vals[]){
    Piece* pieces[16];
    int k = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            Piece *tmp;
            // Top Row
            if(i == 0){
                // Top Left
                if(j == 0){
                    tmp = newPiece(-1, 1, 4, -1, 1);
                    pieces[k] = tmp;
                    //k++;
                    //continue;
                }
                // Top Right
                else if(j == 3){
                    tmp = newPiece(-1, -1, 2, 2, 2);
                    pieces[k] = tmp;
                    //k++;
                    //continue;                   
                }
                // Middle Top
                else{
                    tmp = newPiece(-1, vals[k+1], vals[k+4], vals[k-1], vals[k]);
                    pieces[k] = tmp;
                    //k++;
                    //continue;
                }
            }
            // Bottom Row
            else if(i == 3){
                // Bottom Left
                if(j == 0){
                    tmp = newPiece(vals[k-4], vals[k+1], -1, -1, vals[k]);
                    pieces[k] = tmp;
                    //k++;
                    //continue;
                }
                // Bottom Right
                else if(j == 3){
                     tmp = newPiece(vals[k-4], -1, -1, vals[k-1], vals[k]);
                    pieces[k] = tmp;
                    //k++;
                    //continue;
                }
                // Bottom Middle
                else{
                    tmp = newPiece(vals[k-4], vals[k+1], -1, vals[k-1], vals[k]);
                    pieces[k] = tmp;
                    //k++;
                    //continue;
                }
            }
            // Middle 2 Rows
            else{
                // Mid Left Side
                if(j == 0){
                    tmp = newPiece(vals[k-4], vals[k+1], vals[k-4], -1, vals[k]);
                    pieces[k] = tmp;
                    ///k++;
                    //continue;
                }
                // Mid Right Side
                else if(j == 3){
                    tmp = newPiece(vals[k-4], -1, vals[k+4], vals[k-1], vals[k]);
                    pieces[k] = tmp;
                    //k++;
                    //continue;
                }
                // 4 Adjacent tiles
                else{
                    tmp = newPiece(vals[k-4], vals[k+1], vals[k+4], vals[k-1], vals[k]);
                    pieces[k] = tmp;
                    // k++;
                    // continue;
                }   
            }
            k++;
            //continue;
        }
    }
    return *pieces;
}

class Jigsaw{
    private:
        Piece puzzle[size][size];

    public:
        Jigsaw(int vals[]){
            Piece* pieces = init_pieces(vals);
            int k = 0;
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    puzzle[i][j] = pieces[k];
                    k++;
                }
            }
        }
        // Function called after solving the puzzle
        void print(){
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    cout << puzzle[i][j].value << "\t";
                }
                cout << endl;
            }
        }

        bool fitsWith(Piece* piece1, Piece* piece2){
            int piece_1_adj[] = {piece1->north, piece1->east, piece1->south, piece1->west};
            int piece_2_adj[] = {piece2->north, piece2->east, piece2->south, piece2->west};
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    if(piece_1_adj[i] == piece_2_adj[j]){
                        return 1;
                    }
                }
            }
            return 0;
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
    Piece* tiles[16];
    int vals[] = {1, 1, 2, 2, 4, 3, 3, 2, 5, 5, 6, 7, 5, 8, 8, 9};

    Jigsaw jigsaw(vals);
    jigsaw.print();

    return 0;
}