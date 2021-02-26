//
//  Melds.cpp
//  Pinochle
//
//  Created by Benjamin Kern on 10/16/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#include "Melds.h"
/* *********************************************************************
Function Name: Melds (constructor)
Purpose: to define each instance of a meld
Parameters:
            vector<int> t_cards - a container for all the face values in the meld
            vector<char> inSuits - a container of all the suits in the meld corresponding to each face
            int inPoints - the point value of the meld
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) loop through the two vectors and add the newly created card to the container for the cards iin the meld class
            2) assign the value of points for the meld to the incoming integer inPoints
Assistance Received: none
********************************************************************* */
Melds::Melds(vector<int> t_cards, vector<char> inSuits, int inPoints){
    for(int i = 0; i < t_cards.size(); i++){
        cards.push_back(Card(t_cards[i], 0, inSuits[i]));
    }
    points = inPoints;
}

/* *********************************************************************
Function Name: setSuits
Purpose: to update the suits for the melds (those requiring the trump card for information)
Parameters:
          char inSuit - the suit to which to update the suits of the cards in the meld
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) loop through the cards in the meld
            2) assign the cards suit to inSuit
Assistance Received: none
********************************************************************* */
void Melds::setSuits(char inSuit){
    for(int i = 0; i < cards.size(); i++){
        cards[i].setSuit(inSuit);
    }
}
/* *********************************************************************
Function Name: checkMelds
Purpose: to verify a meld
Parameters:
            vector<Card> hand - the cards that are to be checked for melds
            int meld - the current iteration of the meld
Return Value:
           the point total for the meld (returns 0 if the meld could not be verified in the hand)
Local Variables:
            int count - if count is equal to the current meld's size, the hand contians the meld
Algorithm:
            1) if meld is 2 (the second meld is the only instance where there can be multiple possibilities in one turn, so we must account for that)...
            2) test for marriage by finding a king and queen of the same suit
            3) if meld is not 2 iterate through the cards of the meld
            4) find the current meld's card in the hand
            5) if found increase count by 1
            6) if count is equal to the size of the meld return the point value for that meld
            7) if count is less than the size of that meld, return 0 (count cannot be larger than meld size)
Assistance Received: none
********************************************************************* */
int Melds::checkMelds(vector<Card> hand, int meld){
    //initialize count to 0
    int count = 0;
    //this is the marriage where the king and queen can be any suit so there is a different check for that
    if(meld == 2){
        //loop through hand
        for(int i = 0; i < hand.size(); i++){
            //if the hand is a queen then find a queen with matching suit
            if(hand[i].getFace() == 12){
                vector<Card>::iterator it = find(hand.begin(), hand.end(), Card(13, 4, hand[i].getSuit()));
                //if found return the point value for a marriage
                if(it != hand.end()){
                    return points;
                }
            }
        }
    }
    //loop through the cards in this instance of the meld
    for(int i = 0; i < cards.size(); i++){
        //find the current card in the hand
        vector<Card>::iterator it = find(hand.begin(), hand.end(), cards[i]);
        //if found incrememt count
        if(it != hand.end()){
            count++;
        }
        //if not found return 0 points awarded for the meld
        else return 0;
    }
    //if count is equal to the size of this meld, return the point value for the meld
    if(count == cards.size()){
        return points;
    }
    //else return 0 points for the meld
    
    else return 0;
}

vector<Card> Melds::getCards(){
    return cards;
}

