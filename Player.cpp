//
//  Player.cpp
//  Pinochle
//
//  Created by Benjamin Kern on 9/9/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#include "Player.h"

/* *********************************************************************
Function Name: Player (constructor)
Purpose: to set up the beginning state of each player
Parameters:
            none
Return Value:
            none
Local Variables:
            none
Algorithm:
            set each score to 0
Assistance Received: none
********************************************************************* */
Player::Player(){
    //assign player score to 0
    score = 0;
    //assign player round score to 0
    roundScore = 0;
    //asssign player points from melds to 0
    meldPoints = 0;
}

/* *********************************************************************
Function Name: addCard
Purpose: to add a card to a player's hand
Parameters:
            Card card - the card that will be added to the player's hand
Return Value:
            none
Local Variables:
            none
Algorithm:
            add the new card to the player's hand
Assistance Received: none
********************************************************************* */
void Player::addCard(Card card){
    //add card to hand
    hand.push_back(card);
}
//Virtual Function; will be explained in Human and Player Class
Card Player::playCard(int lead, Card leadCard, Card trumpCard){
    Card t_card = hand[hand.size()-1];
    hand.pop_back();
    return t_card;
}

/* *********************************************************************
Function Name: clearPiles
Purpose: to clear all piles and hand of a player
Parameters:
            none
Return Value:
            none
Local Variables:
            none
Algorithm:
            Use the clear function to clear the hand/piles
Assistance Received: none
********************************************************************* */
void Player::clearPiles(){
    hand.clear();
    melds.clear();
    capture.clear();
}

/* *********************************************************************
Function Name: addToCapture
Purpose: adds the lead and chase cards to the player's capture pile
Parameters:
            Card card1 - the lead card that will be added to the capture
            Card card2 - the chase card that will be added to the capture
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) add lead card to capture pile
            2) add chase card to capture pile
Assistance Received: none
********************************************************************* */
void Player::addToCapture(Card card1, Card card2){
    //add lead card to capture
    capture.push_back(card1);
    //add chase card to capture
    capture.push_back(card2);
}

/* *********************************************************************
Function Name: setHand
Purpose: to set the player's hand to the incoming hand
Parameters:
            vector<Card> t_hand - the container of cards that will be set to the player's hand
Return Value:
            none
Local Variables:
            none
Algorithm:
            update the player's hand to the incoming vector of cards
Assistance Received: none
********************************************************************* */
void Player::setHand(vector<Card> t_hand){
    //hand is assigned to the value of t_hand
    hand = t_hand;
}

/* *********************************************************************
Function Name: setCapture
Purpose: to set the player's capture pile to the incoming vecor of cards
Parameters:
            vector<Card> inCapture - the container of cards that will be set to the player's capture pile
Return Value:
            none
Local Variables:
            none
Algorithm:
            update the player's capture pile to the incoming vector of cards
Assistance Received: none
********************************************************************* */
void Player::setCapture(vector<Card> inCapture){
    //capture is assigned the value of inCapture
    capture = inCapture;
}

/* *********************************************************************
Function Name: setMeld
Purpose: to set the player's meld pile to the incoming vector of cards
Parameters:
            vector<Card> inMeld - the container of cards that will be set to the player's meld pile
Return Value:
            none
Local Variables:
            none
Algorithm:
            update the player's meld pile to the incoming vector ot cards
Assistance Received: none
********************************************************************* */
void Player::setMeld(vector<Card> inMeld){
    //melds is assigned the value of inMeld
    melds = inMeld;
}
/* *********************************************************************
Function Name: setMeldPoints
Purpose: to set the points that the player gets from their melds
Parameters:
            int t_score - the value that will be set to their points from melds
Return Value:
            none
Local Variables:
            none
Algorithm:
            set player's points from meld to the incoming number
Assistance Received: none
********************************************************************* */
void Player::setMeldPoints(int t_score){
    //meldPoints is assigned the value of t_score
    meldPoints = t_score;
}
/* *********************************************************************
Function Name: setScore
Purpose: to set the score of the player's current total score
Parameters:
         int t_score - the value to which the total score will be set
Return Value:
            none
Local Variables:
            none
Algorithm:
            sets game score to the incoming value
Assistance Received: none
********************************************************************* */
void Player::setScore(int t_score){
    //score is assigned the value of t_score
    score = t_score;
}
/* *********************************************************************
Function Name: setRoundScore
Purpose: to set the score of the player's current round score
Parameters:
            int t_score - the value to which the round score will be set
Return Value:
            none
Local Variables:
            none
Algorithm:
            sets the player's round score to the incoming value
Assistance Received: none
********************************************************************* */
void Player::setRoundScore(int t_score){
    //roundScore is assigned the value of t_score
    roundScore = t_score;
}

//Virtual class; will explain in Human and Player class
void Player::makeMelds(vector<Melds> possibleMelds){
    
}
/* *********************************************************************
Function Name: addScore
Purpose: to add the score to the player's current round score
Parameters:
            Card card1 - the current lead card
            Card card2 - the current chase card
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) obtain the point value for the lead and chase cards
            2) add those point totals to the current round score
Assistance Received: none
********************************************************************* */
void Player::addScore(Card card1, Card card2){
    //roundScore adds the points from lead card and chase card
    roundScore = card1.getPoints() + card2.getPoints() + roundScore;
}
/* *********************************************************************
Function Name: addTotalScore
Purpose: to add the player's current round score to thier game score
Parameters:
            none
Return Value:
            none
Local Variables:
            none
Algorithm:
            add the player's round score to their game score
Assistance Received: none
********************************************************************* */
void Player::addTotalScore(){
    //player's round score is added to their total score
    score += roundScore;
}
/* *********************************************************************
Function Name:getScore
Purpose: to return the player's game score
Parameters:
           none
Return Value:
            the value of the player's current game score
Local Variables:
            none
Algorithm:
            returns the player's current game score
Assistance Received: none
********************************************************************* */
int Player::getScore(){
    return score;
}
/* *********************************************************************
Function Name: getRoundScore
Purpose: to return the player's current round score
Parameters:
            none
Return Value:
            the value of the player's current score of the round
Local Variables:
            none
Algorithm:
            return the value of the player's current round score
Assistance Received: none
********************************************************************* */
int Player::getRoundScore(){
    return roundScore;
}
/* *********************************************************************
Function Name: getHand
Purpose: to get the player's hand
Parameters:
            none
Return Value:
            the player's current hand
Local Variables:
            none
Algorithm:
            return the player's current hand
Assistance Received: none
********************************************************************* */
vector<Card> Player::getHand(){
    return hand;
}
/* *********************************************************************
Function Name: getCapture
Purpose: to get the player's current capture pile
Parameters:
         none
Return Value:
            the player's current capture pile
Local Variables:
            none
Algorithm:
            return the player's current capture pile
Assistance Received: none
********************************************************************* */
vector<Card> Player::getCapture(){
    return capture;
}
/* *********************************************************************
Function Name: getMelds
Purpose: to get the player's current meld pile
Parameters:
            none
Return Value:
            the player's current meld pile
Local Variables:
            none
Algorithm:
            return the player's current meld pile
Assistance Received: none
********************************************************************* */
vector<Card> Player::getMelds(){
    return melds;
}

/* *********************************************************************
Function Name:help
Purpose: to use the computer AI to give the human help on his turn
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
void Player::help(int lead, Card leadCard, Card trumpCard){
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
    if(lead == 1){
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
                //current card suit equals trump suit and maxSuit is not equal to trump suit
                if(hand[i].getSuit() == trumpCard.getSuit() && maxSuit == trumpCard.getSuit() && hand[i].getPoints() >= maxCard){
                    highPile = 0;
                    maxCardIndex = i;
                    maxCard = hand[i].getPoints();
                    maxSuit = hand[i].getSuit();
                }
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
                //current card suit equals lead card suit and maxSuit is not equal to lead card suit
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
            //current card points is greater than maxCard
            else if(hand[i].getPoints() > maxCard && doesMatch == false){
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
        cout << "Computer recommends playing " << hand[maxCardIndex];
        if(low == true){
            cout << "because you don't have a card that will beat the lead or trump card." << endl;
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
    }
    //pile is meld
    else{
        //output recommendation
        cout << "Computer recommends playing " << melds[maxCardIndex];
        if(low == true){
            cout << "because you don't have a card that will beat the lead or trump card." << endl;
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
    }
    
}
