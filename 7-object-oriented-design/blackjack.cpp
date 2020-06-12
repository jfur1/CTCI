/*
Author: John Furlong
Date: June 11, 2020
Description:
    Implement the data structures needed for a deck of cards. Similarly, how would you subclass these data structures to
    implement a game of blackjack?
*/
#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
using namespace std;

struct Card{
    int value;
    string suit;
};

struct Player{
    int playerNum;
    string playerName;
    vector<Card> hand;
    int handSum;
};

class Deck{
    private:
        vector<Card> deck;

    public:
        
        Deck(){
            // Create the deck for the game
            string suits[] = {"Diamonds", "Hearts", "Clubs", "Spades"};
            for(int i = 0; i < 4; i++){
                for(int j = 1; j < 14; j++){
                    Card tmp;
                    tmp.value = j;
                    tmp.suit = suits[i];
                    deck.push_back(tmp);
                }
            }
        }

        // Shuffle deck
        void shuffle(){
            // Initialize seed randomly 
            srand(time(0)); 
        
            for (int i=0; i<52 ;i++) 
            { 
                // Random for remaining positions. 
                int r = i + (rand() % (52 -i)); 
        
                swap(deck[i], deck[r]); 
            }
        }

        // Deal Card(s)
        vector<Card> deal(int nCards){
            vector<Card> cards;
            for(int i = 0; i < nCards; i++){
                Card tmp = deck[deck.size()-1];
                deck.pop_back();
                cards.push_back(tmp);
            }
            return cards;
        }

        void printCard(Card card){
            string name;
            if(card.value == 1)
                name = "Ace";
            else if(card.value == 11)
                name = "Jack";
            else if(card.value == 12)
                name = "Queen";
            else if(card.value == 13)
                name = "King";
            else
                name = to_string(card.value);  
            cout << name << " of " << card.suit << endl; 
        }
        
        void printDeck(){
            for(int i = 0; i < 52; i++){
                printCard(deck[i]);
            }
        }

        void printHand(vector<Card> hand){
            for(int i = 0; i < hand.size(); i++){
                printCard(hand[i]);
            }
        }
};

class Blackjack{
    private:
        Deck deck;
        Player player;
        Player dealer;
    public:
        Blackjack(){
            deck = Deck();
            player.handSum = 0;
            dealer.handSum = 0;
        }

        int sumHand(vector<Card> hand){
            int handSum = 0;
            for(int i = 0; i < hand.size(); i++){
                if(hand[i].value == 1)
                    handSum += 1;
                else if(hand[i].value >= 10)
                    handSum += 10;
                else
                    handSum += hand[i].value;
            }
            return handSum;
        }

        void displayHands(){
            cout << "-------------------------------------------------\nDealer's Hand: \n -----------------------------\n";
            for(int i = 0; i < dealer.hand.size(); i++){
                deck.printCard(dealer.hand[i]);
            }
            cout << "\nYour Hand:\n------------------------------\n";
            for(int i = 0; i < player.hand.size(); i++){
                deck.printCard(player.hand[i]);
            }
            cout << "-------------------------------------------------\n" << endl;
        }

        // Hit(): inserts one Card into player's hand.
        void hit(Player *tmpPlayer){
            int bjValue = 0;
            vector<Card> card = deck.deal(1);
            tmpPlayer->hand.push_back(card[0]);
            // Default Ace value 11
            if(card[0].value == 1)
                bjValue = 11;
            // "Face" cards have value 10.
            else if(card[0].value == 11 || card[0].value == 12 || card[0].value == 13)
                bjValue = 10;
            else
                bjValue = card[0].value;
            // Keep track of player handSum for each card dealt.
            tmpPlayer->handSum += bjValue;
            card.pop_back();
            return;
        }
        
        int countAces(vector<Card> hand){
            int nAces = 0;
            for(int i = 0; i < hand.size(); i++){
                if(hand[i].value == 1){
                    nAces++;
                }
            }
            return nAces;
        }

        void playerTurn(Card card){

        }

        void dealerTurn(Card card){

        }

        int checkWinner(){
            // Only called if all players choose to stay, with handSums < 21
            if(player.handSum == dealer.handSum){
                cout << "Dealer wins the draw. You lose!\n";
                return -1;
            }
            else if(player.handSum > dealer.handSum){
                cout << "Your hand is closest to 21. You win!\n";
                return 1;
            }
            else{
                cout << "Dealer is closest to 21. You lose!\n";
                return -1;
            }
        }

        // Returns -1 for dealer victory. Otherwise, return the winning player's number.
        int play(){
            cout << "Welcome to Blackjack!\nShuffling...\n" << endl;
            deck.shuffle();
            hit(&player);
            hit(&dealer);
            hit(&player);
            hit(&dealer);
            displayHands();
            // Players cannot bust with only 2 cards. Only need to check for double Aces, then set handSum = 12.
            if(countAces(player.hand) == 2)
                player.handSum = 12;
            if(countAces(dealer.hand) == 2)
                dealer.handSum = 12;
            // Check for blackjack -- If none, then check if the cards drawn were both aces
            if(dealer.handSum == 21){
                cout << "** Dealer got blackjack! House wins! **\n";
                return -1;
            }
            // 
            if(player.handSum == 21){
                cout << "** You got blackjack! You win! **\n";
                return 1;
            } 

            // If no blackjack, then loop until players either bust, or choose to stay.
            while(1){
                while(1){
                    // Player Turn
                    char input;
                    cout << "** Your hand sums to: " << player.handSum << ". Would you like to hit? (y/n) **\n";
                    cin >> input;

                    if(input == 'y' || input == 'Y'){
                        hit(&player);
                        displayHands();
                        if(player.handSum == 21){
                            cout << "** Blackjack! You win! **\n";
                            return 1;
                        }
                        // If the player bust by drawing an Ace, subtract 10 from handSum, since Aces are default valued as 11
                        if(player.handSum > 21 && player.hand[player.hand.size()-1].value == 1){
                            cout << "** Revalued your Ace as 1 so that you don't bust! **\n";
                            player.handSum -= 10;
                            // Recheck for blackjack after resizing
                            if(player.handSum == 21){
                                cout << "** Blackjack! You win! **\n";
                                return 1;
                            }
                        }

                        if(player.handSum > 21){
                            cout << "\n** Your hand sums to: " << player.handSum << " You lose! **\n";
                            return -1;
                        }
                        // If player.handSum < 21 then continue their turn.
                        if(player.handSum < 21){
                            continue;
                        }
                    } // Break if player doesn't want to hit (stay)
                    else
                        break;
                }
                while(1){
                    // Dealer's turn -> Hit if handSum < 17
                    if(dealer.handSum < 17){
                        cout << "** Dealer chooses to hit **\n";
                        hit(&dealer);
                        displayHands();
                        // Check for immediate blackjack (without resizing any Ace(s)):
                        if(dealer.handSum == 21){
                            cout << "** Blackjack! Dealer wins! **\n";
                            return -1;
                        }
                        if(dealer.handSum > 21 && dealer.hand[dealer.hand.size()-1].value == 1){
                            cout << "** Resized the dealer's Ace to prevent a bust! **\n";
                            dealer.handSum -= 10;
                            // Recheck for blackjack after potential resizing
                            if(dealer.handSum == 21){
                                cout << "** Dealer hit blackjack! You lose! **\n";
                                return -1;
                            }
                        }
                        if(dealer.handSum > 21){
                            cout << "** Dealer busted! You win! **\n";
                            return 1;
                        }
                        // If dealer.handSum < 21 still, then continue loop and see if dealer will hit again
                        if(dealer.handSum < 21){
                            continue;
                        }
                    }
                    // If dealer.handSum > 17, then stay.
                    else{
                        cout << "** Dealer chooses to stay **\n";
                        //check winer
                        return checkWinner();
                    }
                }
            }
            return 0;
        }
};

int main(){            

    char input;
    while(1){    
        
        Blackjack game = Blackjack();
        game.play();

        cout << "\nGood game! Press 'E' to exit, or press any other key to play again.\n";
        cin >> input;
        if(input == 'E' || input == 'e'){
            cout << "Goodbye!\n";
            break;
        }
        else{
            continue;
        }
    }

    return 0;
}