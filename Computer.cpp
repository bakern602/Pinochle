//
//  Computer.cpp
//  Pinochle
//
//  Created by Benjamin Kern on 10/15/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#include "Computer.h"
/* *********************************************************************
Function Name:playCard
Purpose: to use the computer AI for the computer to make the best decision
Parameters:
            int lead - an integer determining if the human is the lead player
            Card leadCard - the current leadCard (if necessary)
            Card trumpCard - the round's current trump card
Return Value:
            none
Local Variables:
            int cardIndex - the index at which the best card is located
            int maxCard - the point value of the best card
            int maxSuit - the suit value of the best card
            int pile - an integer that will decide either meld pile or hand
Algorithm:
            1) determine if the player is lead player or not
            2) if player is lead
                a) find card that will give best odds to win the round (trump cards, high cards of other suits)
            3) if player is chase
                a) find card that will win (higher trump card, higher card of other suit)
            4) store the values of that card (cardIndex, face, suit, pile)
            5) output the recommendation
Assistance Received: none
********************************************************************* */
Card Computer::playCard(int lead, Card leadCard, Card trumpCard){
    //Initialize cardIndexes and maxCard and minCard to 0 and 100 respectively
    int maxCardIndex = 0;
    int minCardIndex = 0;
    
    int maxCard = 0;
    int minCard = 100;
    //Initialize maxSuit to a default character
    char maxSuit = 'Z';
    //initialize pile to 0
    int highPile = 0;
    int lowPile = 0;
    
    bool doesMatch = false;
    bool low = false;
    //if the player is chase player
    if(lead == 0){
        //loop through hand
        for(int i = 0; i < hand.size(); i++){
            //keep track of min card
            if(hand[i].getPoints() < minCard){
                lowPile = 0;
                minCardIndex = i;
                maxCard = hand[i].getPoints();
            }
            if(hand[i].getSuit() == trumpCard.getSuit() && maxSuit == trumpCard.getSuit() && hand[i].getPoints() >= maxCard){
                highPile = 0;
                maxCardIndex = i;
                maxCard = hand[i].getPoints();
                maxSuit = hand[i].getSuit();
            }
            //if current card suit is equal to trump card suit and the maxSuit != trump suit
            else if(hand[i].getSuit() == trumpCard.getSuit() && maxSuit != trumpCard.getSuit()){
                //update the card's index and info
                highPile = 0;
                maxCardIndex = i;
                maxCard = hand[i].getPoints();
                maxSuit = hand[i].getSuit();
            }
            //if current card suit is equal to trump card suit and current card is greater than maxCards
            else if(hand[i].getSuit() == trumpCard.getSuit() && hand[i].getPoints() > maxCard){
                //update card's index and info
                highPile = 0;
                maxCardIndex = i;
                maxCard = hand[i].getPoints();
                maxSuit = hand[i].getSuit();
            }
            //if current card is equal to lead && maxSuit is not equal to leadCard suit
            else if(hand[i].getSuit() == leadCard.getSuit() && maxSuit != leadCard.getSuit()){
                //update card's index and info
                highPile = 0;
                maxCardIndex = i;
                maxCard = hand[i].getPoints();
                maxSuit = hand[i].getSuit();
            }
            //loop through meld pile
            for(int i = 0; i < melds.size(); i++){
                if(hand[i].getSuit() == trumpCard.getSuit() && maxSuit == trumpCard.getSuit() && hand[i].getPoints() >= maxCard){
                    highPile = 0;
                    maxCardIndex = i;
                    maxCard = hand[i].getPoints();
                    maxSuit = hand[i].getSuit();
                }
                //current card suit equals trump suit and maxSuit is not equal to trump suit
                else if(melds[i].getSuit() == trumpCard.getSuit() && maxSuit != trumpCard.getSuit()){
                    //update card's index and info
                    highPile = 1;
                    maxCardIndex = i;
                    maxCard = melds[i].getPoints();
                    maxSuit = melds[i].getSuit();
                }
                //current card suit equals trump suit and current card points is greater than maxCard
                else if(melds[i].getSuit() == trumpCard.getSuit() && melds[i].getPoints() > maxCard){
                    //update card's index and info
                    highPile = 1;
                    maxCardIndex = i;
                    maxCard = melds[i].getPoints();
                    maxSuit = melds[i].getSuit();
                }
                //current card suit equald lead card suit and maxSuit is not equal to lead card suit
                else if(melds[i].getSuit() == leadCard.getSuit() && maxSuit != leadCard.getSuit()){
                    //update card's index and info
                    highPile = 1;
                    maxCardIndex = i;
                    maxCard = melds[i].getPoints();
                    maxSuit = melds[i].getSuit();
                }
            }
        }
        if(hand[maxCardIndex].getSuit() != trumpCard.getSuit() && hand[maxCardIndex].getSuit() != leadCard.getSuit()){
            maxCardIndex = minCardIndex;
            low = true;
        }
    }
    
    //player is lead
    else{
        //loop through player's hand
        for(int i = 0; i < hand.size(); i++){
            //current card suit is equal to trump suit and current card points is greater than maxCard
            if(hand[i].getSuit() == trumpCard.getSuit() && doesMatch == false){
                //update card's index and info
                highPile = 0;
                maxCardIndex = i;
                maxCard = hand[i].getPoints();
                maxSuit = hand[i].getSuit();
                doesMatch = true;
            }
            if(hand[i].getSuit() == trumpCard.getSuit() && hand[i].getPoints() >= trumpCard.getPoints()){
                highPile = 0;
                maxCardIndex = i;
                maxCard = hand[i].getPoints();
                maxSuit = hand[i].getSuit();
                doesMatch = true;
            }
            //curernt card points is greater than maxCard
            else if(hand[i].getPoints() > maxCard){
                //update card's index and info
                highPile = 0;
                maxCardIndex = i;
                maxCard = hand[i].getPoints();
                maxSuit = hand[i].getSuit();
            }
        }
        //loop through meld pile
        for(int i = 0; i < melds.size(); i++){
            //current card suit is equal to trump suit and current card points is greater than maxCard
            if(hand[i].getSuit() == trumpCard.getSuit() && doesMatch == false){
                //update card's index and info
                highPile = 1;
                maxCardIndex = i;
                maxCard = melds[i].getPoints();
                maxSuit = melds[i].getSuit();
            }
            if(hand[i].getSuit() == trumpCard.getSuit() && hand[i].getPoints() >= trumpCard.getPoints()){
                highPile = 0;
                maxCardIndex = i;
                maxCard = hand[i].getPoints();
                maxSuit = hand[i].getSuit();
                doesMatch = true;
            }
            //current card points is greater than maxCard
            else if(hand[i].getPoints() > maxCard){
                //update card's index and info
                highPile = 1;
                maxCardIndex = i;
                maxCard = melds[i].getPoints();
                maxSuit = melds[i].getSuit();
            }
        }
    }
    //pile is hand
    if(highPile == 0){
        //output recommendation
        cout << "Computer plays " << hand[maxCardIndex];
        if(low == true){
            cout << "because it can't beat the lead or trump card." << endl;
        }
        else if(hand[maxCardIndex].getSuit() == trumpCard.getSuit() && hand[maxCardIndex].getPoints() > leadCard.getPoints()){
            cout << "because it is a higher trump card." << endl;
        }
        else if(hand[maxCardIndex].getSuit() == leadCard.getSuit() && hand[maxCardIndex].getPoints() > leadCard.getPoints()){
            cout << "because it is higher than the lead card" << endl;
        }
        else{
            cout << "." << endl;
        }
        Card t_card = hand[maxCardIndex];
        hand.erase(hand.begin()+(maxCardIndex));
        return t_card;
    }
    //pile is meld
    else{
        //output recommendation
        cout << "Computer plays " << melds[maxCardIndex];
        if(low == true){
            cout << "because it can't beat the lead or trump card." << endl;
        }
        else if(melds[maxCardIndex].getSuit() == trumpCard.getSuit() && melds[maxCardIndex].getPoints() > leadCard.getPoints()){
            cout << "because it is a higher trump card." << endl;
        }
        else if(melds[maxCardIndex].getSuit() == leadCard.getSuit() && melds[maxCardIndex].getPoints() > leadCard.getPoints()){
            cout << "because it is higher than the lead card" << endl;
        }
        else{
            cout << "." << endl;
        }
        Card t_card = melds[maxCardIndex];
        melds.erase(melds.begin()+(maxCardIndex));
        return t_card;
    }
    
}

/* *********************************************************************
Function Name: makeMelds
Purpose: to allow the computer to make its best med using computer AI
Parameters:
            vector<Melds> possibleMelds - a container for all available melds
Return Value:
            none
Local Variables:
            vector<int> possibleScores - a container for the point values for potential melds
            int max - the integer value for the highest meld value created
            int maxIndex - the integer containg the index for the highest possible meld created
Algorithm:
            1) check current hand against all possible melds
            2) add the score of that meld to possibleScores (adds 0 if meld cannot be created)
            3) loop through possibleScore
            4) if the current value at possibleScores is greater than max...
            5) set max to be the current value of possibleScores and set the maxIndex to the current index
            6) update the roundScore
            7) update the meldpoints
Assistance Received: none
********************************************************************* */
void Computer::makeMelds(vector<Melds> possibleMelds){
    vector<int> possibleScores;
    int max = 0;
    int maxIndex = 0;
    //loop through possibleMelds
    for(int i = 0; i < possibleMelds.size(); i++){
        //add the score from the meld to possibleScores
        possibleScores.push_back(possibleMelds[i].checkMelds(hand, i));
    }
    //loop through possibleScores and find the best score
    for(int i = 0; i < possibleScores.size(); i++){
        if(possibleScores[i] > max){
            max = possibleScores[i];
            maxIndex = i;
        }
    }
    //if a new meld has been created
    if(max != 0){
        //newMeld is assigned to the meld that has been created
        vector<Card> newMeld = possibleMelds[maxIndex].getCards();
        //loop through newMeld
        for(int i = 0; i < newMeld.size(); i++){
            //add cards from newMeld to computer's meld pile
            melds.push_back(newMeld[i]);
            //find the pile in computer's hand
            vector<Card>::iterator it = find(hand.begin(), hand.end(), newMeld[i]);
            //erase the card
            hand.erase(it);
        }
        //update round score
        roundScore = roundScore + (max - meldPoints);
        //update meldpoints
        meldPoints = max;
    }
}

void Computer::checkMelds(vector<int> possibleScores){
    
}
