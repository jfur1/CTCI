/*
Author: John Furlong
Date: June 12, 2020
Description: Othello
    Othello is played as follows: Each Othello piece is white on one side, and black on the other. When a peice is surrounded by 
    its opponents on both the left and right sides, or both the top and bottom, it is said to be captured and its color is flipped.
    On your turn, you must capture at least one of your opponent's peices. The game ends when either user has no more valid moves.
    The win is assigned to the person with the most pieces. Implement the object oriented design for Othello.
*/
#include <iostream>
#include <string> 

using namespace std;

class Othello{
    private:
        int board[8][8];
        // Dark is 0 , Light is 1
        int turn;

    public:
        Othello(){
            turn = 0;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(i == 3 && j == 3)
                        board[i][j] = 1;
                    else if(i == 3 && j == 4)
                        board[i][j] = 0;
                    else if(i == 4 && j == 3)
                        board[i][j] = 0;
                    else if(i == 4 && j == 4)
                        board[i][j] = 1;
                    else
                        board[i][j] = -1;
                }
            }
        }

        void printBoard(){
            char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
            cout << '\t';
            for(int i = 0; i < 8; i++){
                cout << letters[i] << '\t';
            }
            cout << endl;
            for(int i = 0; i < 8; i++){
                cout << (i+1) << " |\t";
                for(int j = 0; j < 8; j++){
                    cout <<  "|" <<  board[i][j] << "| \t";
                }
                cout << endl;
            }
        }

        void validateMove(int player, string location){

        }

        string prompt(){
            // Prompt the player to select a row and column
            int row; char col;
            cout << "Enter a row number: " << endl;
            cin >> row;
            cout << "Enter a column letter (lowercase)" << endl;
            cin >> col;
            int col_dec = col - 96;
            if(row < 1 || row > 8)
                return "";
            else if(col_dec < 1 || col_dec > 8)
                return "";
            else{
                string row = to_string(row);
                return row+col;                
            }
        }

        void play(){
            while(1){
                // Dark goes first, alternate each turn.
                turn = (turn != 0) ? 0 : 1;
                // Print the board
                printBoard();
                // Prompt the player to select a row and column
                int row; char col;
                cout << "Enter a row number: " << endl;
                cin >> row;
                cout << "Enter a column letter (lowercase)" << endl;
                cin >> col;

                // Check if move is valid before execution
                // if( validateMove(player, location))
                //      board[loc] = player
                // else ==> Loop prompt

                //cout << "You entered: " << row << col << endl;
                int col_dec = col - 96;
                //cout << col << " in decimal: " << col_dec << endl;

                break;
            }
        }

        

};

int main(){
    Othello game = Othello();
    game.printBoard();

    // Dark player goes first
    game.play();

    return 0;
}