//
//  Card.cpp
//  Pinochle
//
//  Created by Benjamin Kern on 9/9/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#include "Card.h"

/* *********************************************************************
Function Name: Card (constructor)
Purpose: To set all vaues for the card
Parameters:
            int inFace - an integer that conains the face value of the card
            int inPoints - an integer that contains the point value of a card
            char inSuit - a character that contains the suit of a card
Return Value:
            none
Local Variables:
            none
Algorithm:
            Sets all values for the card
Assistance Received: none
********************************************************************* */
Card::Card(int inFace, int inPoints, char inSuit){
    //assign face to the value of inFace
    face = inFace;
    //assign suit to the value of inSuit
    suit = inSuit;
    //ssign points to the value of inPoints
    points = inPoints;
}

/* *********************************************************************
Function Name: setFace
Purpose: sets the face value of the card
Parameters:
            int inFace - an integer that conains the face value of the card
Return Value:
            none
Local Variables:
            none
Algorithm:
            Sets the card's face to the paramter passed, inFace
Assistance Received: none
********************************************************************* */
void Card::setFace(int inFace){
    //assign face to the value of inFace
    face = inFace;
}

/* *********************************************************************
Function Name: setSuit
Purpose: sets the suit value of the card
Parameters:
            int inSuit - a character that conains the suit value of the card
Return Value:
            none
Local Variables:
            none
Algorithm:
            Sets the card's suit to the paramter passed, inSuit
Assistance Received: none
********************************************************************* */
void Card::setSuit(char inSuit){
    //assign suit to the value of inSuit
    suit = inSuit;
}

/* *********************************************************************
Function Name: getSuit
Purpose: gets the suit value
Parameters:
            none
Return Value:
            The card's suit
Local Variables:
            none
Algorithm:
            Returns the card's suit
Assistance Received: none
********************************************************************* */
char Card::getSuit(){
    return suit;
}

/* *********************************************************************
Function Name: getPoints
Purpose: gets the point value
Parameters:
            none
Return Value:
            The card's point value
Local Variables:
            none
Algorithm:
            Returns the card's point value
Assistance Received: none
********************************************************************* */
int Card::getPoints(){
    return points;
}
/* *********************************************************************
Function Name: getFace
Purpose: gets the face value
Parameters:
            
Return Value:
            The card's face
Local Variables:
            none
Algorithm:
            Returns the card's face value
Assistance Received: none
********************************************************************* */
int Card::getFace(){
    return face;
}

/* *********************************************************************
Function Name: operator<< (overloaded operator)
Purpose: Give a definition to output the value of a carrd using an output stream
Parameters:
            osteram &strm - a dereference to the output stream variable that will be added to
            const Card &card - a const variable that dereferences the card instance that will be referenced
Return Value:
            The ouput stream variable
Local Variables:
            none
Algorithm:
            1) Determine the card's face value.
            2) Output the correct face along with the correct suit
Assistance Received: none
********************************************************************* */
ostream& operator<<(std::ostream &strm, const Card &card){
    //check the face of the card
    //update strm with corresponding output values
    switch(card.face){
        //0 outputs just a suit
        case 0:
            strm << card.suit;
            break;
        //9 outputs 9
        case 9:
            strm << card.face << card.suit;
            break;
        //10 outputs X
        case 10:
            strm << 'X' << card.suit;
            break;
        //11 outputs J
        case 11:
            strm << 'J' << card.suit;
            break;
        // 12 outputs Q
        case 12:
            strm << 'Q' << card.suit;
            break;
        case 13:
        //13 outputs K
            strm << 'K' << card.suit;
            break;
        case 14:
        //14 outputs A
            strm << 'A' << card.suit;
            break;
    }
    return strm << " ";
}
/* *********************************************************************
Function Name: operator== (overloaded operator)
Purpose: To overload the == operator so we can compare two cards.
Parameters:
            const Card &c1 - the first card that will be dereferenced
            const Card &c2 - the seonc card that will be dereferenced
Return Value:
            A boolean value determining if two cards are equal based on the face and the suit
Local Variables:
            none
Algorithm:
            Return a boolean value determining if two cards are equal based on face and suit
Assistance Received: none
********************************************************************* */

bool operator== (const Card &c1, const Card &c2){
    //return true if cards are equal
    return (c1.face == c2.face && c1.suit == c2.suit);
}
