//
//  Round.cpp
//  Pinochle
//
//  Created by Benjamin Kern on 9/9/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#include "Round.h"
/* *********************************************************************
Function Name: Round (constructor)
Purpose: To set up the beginning of each round
Parameters:
            Player *human - a reference variable to the human player
            Player *computer - a reference variable to the computer player
            Deck deck - an instance of the deck class
            int inNextPlayer - an integer that contains the player who will take the next turn
            int inRoundNumber - an integer that contains the current round number
            vector<Melds> melds - a vector that contains all available melds in the game
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) sets the human, computer, nextPlayer, and round number to correct values
            2) retrieves the deck, shuffles the deck, and deals the cards.
            3) sets the meld suit to the trump card suit for the melds that have the trump card suit as a requirement
            4) sets both player's round scores to 0.
Assistance Received: none
********************************************************************* */

Round::Round(Player *human, Player *computer, Deck deck, int inNextPlayer, int inRoundNumber, vector<Melds> melds){
    //assign possibleMelds to the container of melds
    possibleMelds = melds;
    //assign nextPlayer to the value of inNextPlayer
    nextPlayer = inNextPlayer;
    //assign roundNumber to the value of inRoundNumber
    roundNumber = inRoundNumber;
    //assign the first player in playerList to human player
    playerList[0] = human;
    //assign the second player in playerList to computer player
    playerList[1] = computer;
    //reset the capture, meld, and hand
    playerList[0]->clearPiles();
    playerList[1]->clearPiles();
    //assign the games deck to stockPile, shuffle, and deal from shuffled stock pile
    stockPile = deck.getDeck();
    shuffleDeck();
    dealCards();
    //update the suits for melds that require it
    setMeldSuit();
    //set player's initial scores to 0
    playerList[0]->setRoundScore(0);
    playerList[1]->setRoundScore(0);
    
}

/* *********************************************************************
Function Name: shuffleDeck
Purpose: to shuffle the deck in a random order
Parameters:
            none
Return Value:
            none
Local Variables:
            unsigned seed - a random number to use for the shuffle function
Algorithm:
            uses the shuffle function in the algorithm file to shuffle the deck
Assistance Received: none
********************************************************************* */
void Round::shuffleDeck(){
    //assign seed to a random number
    unsigned seed = rand() % 100000000;
    //use seed to shuffle the stock pile
    shuffle(stockPile.begin(), stockPile.end(), default_random_engine(seed));
}
/* *********************************************************************
Function Name: dealCards
Purpose: tdeals cards to start the game
Parameters:
            none
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) deal 4 cards from top of stock pile to human
            2) deal 4 cards from top of stock pile to computer
            3) repeat 1 and 2 two more times
            4) trumpCard is equaled to the next card in the stock
Assistance Received: none
********************************************************************* */
void Round::dealCards(){
    //loop three times through...
    for(int m = 0; m < 3; m++){
        //deal human cards
        for(int i = 0; i < 4; i++){
            playerList[0]->addCard(stockPile.back());
            stockPile.pop_back();
        }
        //deal computer cards
        for(int i = 0; i < 4; i++){
            playerList[1]->addCard(stockPile.back());
            stockPile.pop_back();
        }
    }
    //assign trump card to next card in stock
    trumpCard = stockPile.back();
    stockPile.pop_back();
    
}

/* *********************************************************************
Function Name:setStock
Purpose: to set the stock pile
Parameters:
            vector<Card> inStock - a vector of cards that contains the incomcing stockpile to be set
Return Value:
            none
Local Variables:
            none
Algorithm:
            sets the stockpile equal to the incoming stock pile
Assistance Received: none
********************************************************************* */
void Round::setStock(vector<Card> inStock){
    //stockPile is assigned the value of inStock
    stockPile = inStock;
}
/* *********************************************************************
Function Name: setRoundNumber
Purpose: to set the round number to the incoming value
Parameters:
            int inRoundNumber - the value the roundNumber will be assigned to; the current round number
Return Value:
            none
Local Variables:
            none
Algorithm:
            sets roundNumber to current round number
Assistance Received: none
********************************************************************* */

void Round::setRoundNumber(int inRoundNumber){
    //roundNumber is assigned the value of inRoundNumber
    roundNumber = inRoundNumber;
}
/* *********************************************************************
Function Name: setTrump
Purpose: to set the value of the trump card
Parameters:
            Card t_trump - the card that the trump card will be assigned; the trump card for the current round
            
Return Value:
            none
Local Variables:
            none
Algorithm:
            sets trumpCard to current round's trump card
Assistance Received: none
********************************************************************* */
void Round::setTrump(Card t_trump){
    //trumpCard is assigned the value of t_trump
    trumpCard = t_trump;
}

/* *********************************************************************
Function Name: setMeldSuit
Purpose: to set the suit for the melds that require the trump card's suit
Parameters:
            none
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) loops through the available melds (possibleMelds)
            2) given certain cases, the meld's suit will be updated accordingly. (3 seperate melds need the trump card's suit)
Assistance Received: none
********************************************************************* */
void Round::setMeldSuit(){
    //loop through melds
    for(int i = 0; i < possibleMelds.size(); i++){
        //if meld is case 0, 1, 3 then update the suit for those melds
        switch(i){
            case 0:
            case 1:
            case 3:
                possibleMelds[i].setSuits(trumpCard.getSuit());
        }
    }
}
/* *********************************************************************
Function Name: playRound
Purpose: to play a single round of the game
Parameters:
            none
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) loopes through the round until all hand/meld cards are used
            2) prints out all the details of the current state of the round
            3) prints menu and asks user to input a choice
            4) based on the input, the game will either save and quit, start a turn, give help, or quit
            5) once round is complete, each player's game score is updated
Assistance Received: none
********************************************************************* */
void Round::playRound(){
    //loop while meld and hand is not empty
    while(!(playerList[0]->getHand().empty()) || playerList[0]->getMelds().empty()){
        //print state of game
        stringstream ss = this->print(playerList[0], playerList[1]);
        cout << ss.str();
        //print and retreive menu options
        int choice = menu();
        //save game
        if(choice == 1){
            stringstream saveState = print(playerList[0], playerList[1]);
            saveGame(saveState.str());
            exit(0);
        }
        //make a move
        else if(choice == 2){
            //have both players play cards
            int winner = playCards();
            //winner is lead card
            if(winner == 0){
                //winner makes melds
                playerList[nextPlayer]->makeMelds(possibleMelds);
            }
            //winner is chase card
            else{
                //winner makes melds
                playerList[(nextPlayer+1)%2]->makeMelds(possibleMelds);
                //update next player because chase card won
                nextPlayer = (nextPlayer + 1) % 2;
            }
            //if stock pile is not empty
            if(!(stockPile.empty())){
                //winner takes from stock
                playerList[nextPlayer]->addCard(stockPile.back());
                //pop the top card from the stock
                stockPile.pop_back();
                //if stock remains not empty
                if(!(stockPile.empty())){
                    //loser takes from stock
                    playerList[(nextPlayer + 1) % 2]->addCard(stockPile.back());
                    //pop the top card from the stock
                    stockPile.pop_back();
                }
                //stock is empty
                else{
                    //loser draws trump card
                    playerList[(nextPlayer + 1) % 2]->addCard(trumpCard);
                    //trump card is set to 0 of that suit (will only print suit)
                    Card newCard(0, 0, trumpCard.getSuit());
                    trumpCard = newCard;
                }
            }
        }
        //asks for help
        else if(choice == 3){
            playerList[0]->help(nextPlayer, Card(0, 0, 'Z'), trumpCard);
        }
        //quits
        else{
            exit(0);
        }
    }
    //when round is over, both players have their round scores added to total scores
    playerList[0]->addTotalScore();
    playerList[1]->addTotalScore();
    
}
/* *********************************************************************
Function Name: playCards
Purpose: to allow each player to play a card (lead card and chase card)
Parameters:
            none
Return Value:
            an integer desribing the winning the player for the turn
Local Variables:
            Card leadCard - the card that gets played by the lead player
            Card chaseCard - the card that gets played by the chase player
Algorithm:
            1) obtain each player's card to play for the turn
            2) compare each card and determine a winner
            3) return the winning player
Assistance Received: none
********************************************************************* */
int Round::playCards(){
    //get the lead card
    leadCard = playerList[nextPlayer]->playCard(0, Card(0, 0, 'Z'), trumpCard);
    //get the chase card
    chaseCard = playerList[(nextPlayer + 1) % 2]->playCard(1, leadCard, trumpCard);
    //lead card suit is equal to trump card suit
    if(leadCard.getSuit() == trumpCard.getSuit()){
        //chase card suit is equal to trump card suit AND chase card point value is higher than lead card
        if(chaseCard.getSuit() == trumpCard.getSuit() && chaseCard.getPoints() > leadCard.getPoints()){
            //chase card wins, adds to score, and adds to capture pile
            playerList[(nextPlayer + 1) % 2]->addScore(leadCard, chaseCard);
            cout << "Chase won" << endl;
            playerList[(nextPlayer + 1) % 2]->addToCapture(leadCard, chaseCard);
            return 1;
        }
        //in any other case
        else{
             //lead card wins, adds to score, and adds to capture pile
            playerList[nextPlayer]->addScore(leadCard, chaseCard);
            playerList[nextPlayer]->addToCapture(leadCard, chaseCard);
            cout << "Lead won" << endl;
            return 0;
        }
    }
    //lead card suit is not equal to trump card suit
    else{
        //chase card suit is equal to rump card suit
        if(chaseCard.getSuit() == trumpCard.getSuit()){
            //chase card suit is equal to trump card suit AND chase card point value is higher than lead card
            playerList[(nextPlayer + 1) % 2]->addScore(leadCard, chaseCard);
            playerList[(nextPlayer + 1) % 2]->addToCapture(leadCard, chaseCard);
            cout << "Chase won" << endl;
            return 1;
        }
        //chase card suit is the same as lead card and chase card points is higher than lead card
        else if(chaseCard.getSuit() == leadCard.getSuit() && chaseCard.getPoints() > leadCard.getPoints()){
            //chase card suit is equal to trump card suit AND chase card point value is higher than lead card
            playerList[(nextPlayer + 1) % 2]->addScore(leadCard, chaseCard);
            playerList[(nextPlayer + 1) % 2]->addToCapture(leadCard, chaseCard);
            cout << "Chase won" << endl;
            return 1;
        }
        //in all other cases
        else{
            //lead card wins, adds to score, and adds to capture pile
            playerList[nextPlayer]->addScore(leadCard, chaseCard);
            playerList[nextPlayer]->addToCapture(leadCard, chaseCard);
            cout << "Lead won" << endl;
            return 0;
        }
    }
    
}
/* *********************************************************************
Function Name: menu
Purpose: to output the game's menu to the player
Parameters:
            none
Return Value:
            an integer with the player's choice for that turn
Local Variables:
            int choice - the integer that contains the human player's choice for the menu options
Algorithm:
            1) ask human to choose an option
            2) have the human input their choice
            3) return their chocie
Assistance Received: none
********************************************************************* */
int Round::menu(){
    //prompt the user for choice
    int choice;
    cout << "Choose an option:\n\t1) Save the Game\n\t2) Make a Move\n\t3) Ask for Help\n\t4) Quit the Game" << endl;
    //get their choice and return
    cin >>choice;
    return choice;
}
/* *********************************************************************
Function Name: getTrump
Purpose: to return the trumpCard
Parameters:
           none
Return Value:
            the current round's trump card
Local Variables:
            none
Algorithm:
            return the current round's trump card
Assistance Received: none
********************************************************************* */
Card Round::getTrump(){
    return trumpCard;
}
/* *********************************************************************
Function Name:print
Purpose: to store the contents of the current state of the round in a stringstream object
Parameters:
            Player *human - a variable that references the human player
            Player *computer - a vraibale that references the computer player
Return Value:
            a stringstream object that contains the current state of the round
Local Variables:
            stringstream gameboard - the variable that will be used to store the current state of the round
Algorithm:
            obtain all values of the current state of the round and store it in the stringstream object
Assistance Received: none
********************************************************************* */
stringstream Round::print(Player *human, Player *computer){
    //initialize gameboard, which will store the stringstream of the current round
    stringstream gameBoard;
    //stores round number
    gameBoard << "Round: " << roundNumber << endl;
    //stores all computer information
    gameBoard << "Computer:\n\tScore: " << computer->getScore() << " / " << computer->getRoundScore();
    gameBoard << "\n\tHand: ";
    for(int i = 0; i < computer->getHand().size(); i++){
        gameBoard << computer->getHand()[i];
    }
    gameBoard << "\n\tCapture Pile: ";
    for(int i = 0; i < computer->getCapture().size(); i++){
        gameBoard << computer->getCapture()[i];
    }
    gameBoard << "\n\tMelds: ";
    for(int i = 0; i < computer->getMelds().size(); i++){
        gameBoard << computer->getMelds()[i];
    }
    //stores all human infomration
    gameBoard << "\nHuman:\n\tScore: " << human->getScore() << " / " << human->getRoundScore();
    gameBoard << "\n\tHand: ";
    for(int i = 0; i < human->getHand().size(); i++){
        gameBoard << human->getHand()[i];
    }
    gameBoard << "\n\tCapture Pile: ";
    for(int i = 0; i < human->getCapture().size(); i++){
        gameBoard << human->getCapture()[i];
    }
    gameBoard << "\n\tMelds: ";
    for(int i = 0; i < human->getMelds().size(); i++){
        gameBoard << human->getMelds()[i];
    }
    //stores trump card
    gameBoard << "\n\nTrump Card: " << trumpCard;
    //stores stock pile
    gameBoard << "\n\nStock: ";
    for(int i = stockPile.size(); i > 0; i--){
        gameBoard << stockPile[i-1];
    }
    //stores next player to play either human or computer
    if(nextPlayer == 0) gameBoard << "\nNext Player: Human";
    else gameBoard << "\nNextPlayer: Computer";
    
    gameBoard << endl;
    //return the full gameboard stringstream
    return gameBoard;
}
/* *********************************************************************
Function Name: saveGame
Purpose: to save the current state of the game
Parameters:
            string gameState - a string that contains the current state of the game
Return Value:
            none
Local Variables:
            ofstream myfile - an ooutput file stream object that allows for the game state to be saved to a file
Algorithm:
            1) open a file
            2) load the string gameState into the file
            3) close the file
Assistance Received: none
********************************************************************* */
void Round::saveGame(string gameState){
    //initialize an output file stream
    ofstream myfile;
    //open file
    //This is the file for my program.
    //Change the string to the desired directory
    myfile.open("/Users/benjaminkern/Desktop/Pinochle/Serialization1.txt");
    //output gamestate to file
    myfile << gameState;
    //close file
    myfile.close();
}
