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
            turn = 1;
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

        // Utility function prints the game board
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

        // Functions checks if the tile at the given location is free, and whether or not the move captures an opponent piece.
        // Returns true if move is valid and capturing, else returns false
        bool validateMove(int player, string move){

            // Convert the player's move into row & column indexes
            int row = int(move[0]) - 48 - 1;
            int col = move[2] - 96 - 1;
            // First check if spot is open
            cout << "Validating Move. Row: " << row << ". Column: " << col << endl;

            if(board[row][col] != -1){
                cout << "Tile " << move << " has already been played. Please select a different tile\n";
                return 0;
            }
            
            // Coordinate deltas for checking adjacent tiles -- Clockwise starting from the north
            int delta_x[] = {-1, -1, 0, 1, 1, 1, 0, -1};
            int delta_y[] = {0, 1, 1, 1, 0, -1, -1, -1};
            int opponent = (player == 0) ? 1 : 0;

            // For each adjacent tile, see if the opposite side is also the current color
            for(int i = 0; i < 9; i++){
                // Check if there is an adjacent opponent tile
                int tmpRow = row + delta_x[i];
                int tmpCol = col + delta_y[i];
                if(board[tmpRow][tmpCol] == opponent){
                    cout << "Found adjacent enemy piece at row: " << tmpRow << " and col: " << tmpCol << endl;
                    int oppositeRow = tmpRow + delta_x[i];
                    int oppositeCol = tmpCol + delta_y[i];
                    cout << "Checking for enclosing piece at row: " << oppositeRow << " and col: " << oppositeCol << endl;
                    // Is the opposite side of the adjacent-opponent piece also the current player's?
                    if(board[oppositeRow][oppositeCol] == player){
                        cout << "Valid Move! Captured enemy piece.\n";
                        board[row][col] = player;
                        board[tmpRow][tmpCol] = player;
                        return 1;
                    }   
                }
            }
            cout << "Invalid Move!\n";
            return 0;
        }

        // Function checks if the current state of the board results in a winner/loser
        bool checkWin(){

            return 0;
        }

        // Utility function used to prompt user for their selected move
        string prompt(){
            // Prompt the player to select a row and column
            int row; char col;
            cout << "Enter a row number: " << endl;
            cin >> row;
            cout << "Enter a column letter (lowercase)" << endl;
            cin >> col;
            int col_dec = col - 96;

            // Only accept valid board positions
            if(row < 1 || row > 8){
                if(col_dec < 1 || col_dec > 6){
                    cout << "Enter a row number between 1 and 8. Also, enter a column between 'a' and 'h'\n";
                    return "";
                }
                cout << "Enter a row number between 1 and 8.\n";
                return "";
            }
            // Concatenate the valid move
            string move = to_string(row) + ' ' + col;

            cout << "You entered: " << move << endl;

            return move;
            }

        // Driver function used to play the game
        void play(){
            while(1){
                // Dark goes first, alternate each turn.
                turn = (turn != 0) ? 0 : 1;
                // Print the board
                printBoard();
                // Prompt the player to select a row and column; Continue until valid move is chosen
                string move = prompt();
                while(move == ""){
                    move = prompt();
                }
                bool valid = validateMove(turn, move);
                while(!valid){
                    valid = validateMove(turn, move);
                }
                // Once a move has been made, check for winner


                break;
            }
        }

        

};

int main(){
    Othello game = Othello();
    //game.printBoard();

    // Dark player goes first
    game.play();

    return 0;
}