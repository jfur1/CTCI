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
                cout << ' ' << letters[i] << '\t';
            }
            cout << endl;
            for(int i = 0; i < 8; i++){
                cout << (i+1) << " |\t";
                for(int j = 0; j < 8; j++){
                    if(board[i][j] == -1){
                        cout <<  "[   ] \t";
                        continue;
                    }
                    else if(board[i][j] == 0)
                        cout <<  "[ ○ ] \t";
                    else if(board[i][j] == 1)
                        cout <<  "[ ● ] \t";
                }
                cout << endl;
            }
        }
        
        // Functions checks if the tile at the given location is free, and whether or not the move captures an opponent piece.
        // Returns true if move is valid and capturing, else returns false
        bool validateMove(int player, string move){
            int valid_flag = 0;
            // Convert the player's move into row & column indexes
            int row = int(move[0]) - 48 - 1;
            int col = move[2] - 96 - 1;
            // First check if spot is open
            cout << "* Validating Move. Row: " << row+1 << ". Column: " << move[2] << endl;

            // Tile in use
            if(board[row][col] != -1){
                cout << "Tile " << move << " has already been played. Please select a different tile\n";
                return 0;
            }
            
            // Coordinate deltas for checking adjacent tiles -- Clockwise starting from the north
            int delta_x[] = {-1, -1, 0, 1, 1, 1, 0, -1};
            int delta_y[] = {0, 1, 1, 1, 0, -1, -1, -1};
            int opponent = (player == 0) ? 1 : 0;

            // For each adjacent tile, see if the opposite side is also the current color
            for(int i = 0; i < 8; i++){
                // Check if there is an adjacent opponent tile
                int tmpRow = row + delta_x[i];
                int tmpCol = col + delta_y[i];
                if(tmpRow < 0 || tmpRow > 7)
                    continue;
                if(tmpCol < 0 || tmpCol > 7)
                    continue;
                if(board[tmpRow][tmpCol] == opponent){
                    cout << "* Found adjacent enemy piece at row: " << tmpRow+1 << " and col: " << char(tmpCol+97) << endl;
                    int oppositeRow = tmpRow + delta_x[i];
                    int oppositeCol = tmpCol + delta_y[i];
                    cout << "\tChecking for enclosing piece at row: " << oppositeRow+1 << " and col: " << char(oppositeCol+97) << endl;
                    // Is the opposite side of the adjacent-opponent piece also the current player's?
                    if(board[oppositeRow][oppositeCol] == player){
                        cout << "\tValid Move! Captured enemy piece.\n";
                        board[row][col] = player;
                        board[tmpRow][tmpCol] = player;
                        valid_flag = 1;
                    }   
                    else{
                        cout << "\tNo enclosing piece.\n";
                    }
                }
            }

            if(valid_flag == 0)
                return 0;
            else
                return 1;
        }

        // Function checks if the given player wins the game after making a move. 
        // Calculates list of all possible moves left for opponent, if none, then player wins.
        bool checkWin(int player){
            int delta_x[] = {-1, -1, 0, 1, 1, 1, 0, -1};
            int delta_y[] = {0, 1, 1, 1, 0, -1, -1, -1};
            int opponent = (player == 0) ? 1 : 0;
            // For each empty cell, check if there is a valid move remaining
            for(int row = 0; row < 8; row++){
                for(int col = 0; col < 8; col++){
                    // Only check spaces that contain blank spaces (possible moves)
                    if(board[row][col] == -1){
                        for(int i = 0; i < 8; i++){
                            // Check if there is an adjacent tile owned by the player who just took their turn
                            int adjRow = row + delta_x[i];
                            int adjCol = col + delta_y[i];
                            if(adjRow < 0 || adjRow > 7)
                                continue;
                            if(adjCol < 0 || adjCol > 7)
                                continue;
                            int oppositeRow = adjRow + delta_x[i];
                            int oppositeCol = adjCol + delta_y[i];
                            // Opponent's move after this function is called. If there exists an open space adjacent to the current player, 
                            // which is also enclosed by the opponent on the opposite side, then the opponent still has valid moves remaining.
                            if(board[adjRow][adjCol] == player && board[oppositeRow][oppositeCol] == opponent){
                                return false;
                            }
                        }
                    }
                }
            }
            // If the opponent is left without any valid moves after the current player's turn, then the current player wins the game.
            return true;
        }

        // Utility function used to prompt user for their selected move
         string prompt(){
            string move = "";
            while(move == ""){
                bool error = false;
                // Prompt the player to select a row and column
                char row,  col;
                cout << "Enter a row number: " << endl;
                cin >> row;
                cout << "Enter a column letter (lowercase)" << endl;
                cin >> col;
                // (string -> int) to validate position
                int row_dec = row - 48;
                int col_dec = col - 96;

                // Only accept valid row positions
                if(row_dec < 1 || row_dec > 8){
                    cout << "ERROR: Row number must be between 1 and 8.\n";
                    error = true;
                }
                // Only accept valid column positions
                if(col_dec < 1 || col_dec > 8){
                    cout << "ERROR: Column letter must be between 'a' and 'h' (lowercase)\n";
                    error = true;
                }
                // Refresh prompt upon error
                if(error){
                    cin.clear();
                    continue;
                }
                // Concatenate the valid move
                else{
                    move = to_string(row_dec) + ' ' + col;
                    cout << "You entered: " << move << endl;
                }
                cin.clear();
            }
            return move;
        }

        // Driver function used to play the game
        bool play(){
            while(1){
                // Dark goes first, alternate each turn.
                turn = (turn != 0) ? 0 : 1;
                if(turn == 0)
                    cout << "Dark Player's move.\n";
                else
                    cout << "Light Player's Move.\n";
                // Print the board
                printBoard();
                // Prompt the player to select a row and column; Continue until valid move is chosen
                string move = prompt();
        
                // Is it a valid move in terms of enemy capture?
                int valid = validateMove(turn, move);
                while(valid != 1){
                    cout << "Invalid move! No adjacent enemy tiles to be captured. Please enter a different move.\n";
                    move = prompt();
                    valid = validateMove(turn, move);
                }
                
                // Once a move has been made, check for winner. If the resulting move leaves the opponent with no valid moves, then the current player wins.
                if(checkWin(turn)){ 
                    cout << "Player " << turn << " wins!\n";
                    return 1;
                }
            }
            // Function returns player decision to play again
            cout << "Would you like to play again? (y/n)\n";
            char input;
            cin >> input;
            if(input == 'y' || input == 'Y')
                return 1;
            cout << "Thanks for playing!\n";
            return 0;
        }

        

};

int main(){
    Othello game = Othello();

    // Dark player goes first
    bool play_again = game.play();
    while(play_again){
        play_again = game.play();
    }

    return 0;
}