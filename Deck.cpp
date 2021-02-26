//
//  Deck.cpp
//  Pinochle
//
//  Created by Benjamin Kern on 9/9/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#include "Deck.h"

/* *********************************************************************
Function Name: Deck (constructor)
Purpose: To create a deck
Parameters:
            none
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) iterate through i loop to create all face values of cards in deck
            2) iterate through j loop within i loop to create all suit values of cards with each face
            3) based on value of j, create Card with given suit, face, and point value and add it to deck twice
Assistance Received: none
********************************************************************* */
Deck::Deck(){
    //iterate through faces
    for(int i = 0; i < 6; i++){
        //iterate through suits
        for(int j = 0; j < 4; j++){
            //push_back into deck the card with each face/suit/point value
            if(j == 0){
                deck.push_back(Card(i+9, POINTS[i], 'C'));
                deck.push_back(Card(i+9, POINTS[i], 'C'));
            }
            else if(j == 1){
                deck.push_back(Card(i+9, POINTS[i], 'H'));
                deck.push_back(Card(i+9, POINTS[i], 'H'));
            }
            else if(j == 2){
                deck.push_back(Card(i+9, POINTS[i], 'S'));
                deck.push_back(Card(i+9, POINTS[i], 'S'));
            }
            else if(j == 3){
                deck.push_back(Card(i+9, POINTS[i], 'D'));
                deck.push_back(Card(i+9, POINTS[i], 'D'));
            }
        }
    }
}
/* *********************************************************************
Function Name: getDeck
Purpose: To return the deck
Parameters:
            none
Return Value:
            vector of cards that contains all cards in the deck
Local Variables:
            none
Algorithm:
            returns the deck
Assistance Received: none
********************************************************************* */
vector<Card> Deck::getDeck(){
    return deck;
}

/* *********************************************************************
Function Name: printdeck
Purpose:prints the deck
Parameters:
            none
Return Value:
            none
Local Variables:
            none
Algorithm:
            iterates through deck and outputs each card
Assistance Received: none
********************************************************************* */
void Deck::printDeck(){
    //loop through deck and print each card
    for(int i = 0; i < deck.size(); i++){
        cout << deck[i];
        cout << " ";
    }
}

