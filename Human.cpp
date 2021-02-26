//
//  Human.cpp
//  Pinochle
//
//  Created by Benjamin Kern on 10/14/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#include "Human.h"

/* *********************************************************************
Function Name: playCard
Purpose: to allow the player to choose a card to play
Parameters:
            int lead - determines whether player is lead or not
            Card leadCard - the turn's leadCard
            Card trumpCard - the round's trump card
Return Value:
            the value of the card to be played by the player
Local Variables:
            int card - the card at which to play from the given pile
            int pile - the pile at which to play the card from
Algorithm:
            1) prompt user to enter a value for the pile they'd like to play from (check input)
            2) prompt user to enter a value of the card they'd like to play from that pile (check input)
            3) store chosen card in a temporary card
            4) erase the chosen card from the hand/meld pile
            5) return the chosen card
Assistance Received: none
********************************************************************* */
Card Human::playCard(int lead, Card leadCard, Card trumpCard){
    int card;
    int pile;
    char help;
    Card t_card;
    do{
        cout << "Ask for help (y/n):";
        cin >> help;
    }while(help != 'y' && help != 'n');
    if(help == 'y'){
        this->help(lead, leadCard, trumpCard);
    }
    //prompt user for pile and validate
    do{
        cout << "Would you like to play a card from your hand (1) or your melds (2)? ";
        cin >> pile;
    }while(pile != 1 && pile != 2);
    //user picked hand
    if(pile == 1){
        //prompt user for card and validate
        do{
            cout << "Which card from you hand would you like to play? ";
            cin >> card;
        }while(card > hand.size() || card < 1);
        //assign t_card to chosen card
        t_card = hand[card-1];
        //erase card from hand
        hand.erase(hand.begin()+(card-1));
    }
    //user picked meld pile
    else{
        //prompt user for card and validate
        do{
            cout << "Which card from your melds would you like to play? ";
            cin >> card;
        }while(card > melds.size() || card < 1);
        //assign t_card to chosen card
        t_card = melds[card-1];
        //erase card from melds
        melds.erase(melds.begin()+(card-1));
    }
    
    return t_card;
    
}
/* *********************************************************************
Function Name: makeMelds
Purpose: to allow the human to make a meld with current cards
Parameters:
            vector<Melds> possibleMelds - a vector containing game's available melds
Return Value:
            none
Local Variables:
            int num - the number of cards the player wants to add to meld
            int card[num] - the indexes at which the cards are located in the hand
Algorithm:
            1) prompt user to enter the amount of cards to add to meld
            2) prompt user to enter all cards they wish to add (validate input)
            3) add the chosen cards to the player's meld pile
            4) validate the new meld is legal
            5) if legal erase those cards from hand
            6) if not legal, take them out of the meld pile
Assistance Received: none
********************************************************************* */
void Human::makeMelds(vector<Melds> possibleMelds){
    
    int num;
    //prompt user for amount of cards to meld
    cout << "How many cards would you like to add to your melds? ";
    cin >> num;
    //initialize array with num integers
    int card[num];
    //loop num times
    for(int i = 0; i < num; i++){
        //prompt user for card to meld and validate
        do{
            cout << "Enter card: ";
            cin >> card[i];
        }while(card[i] < 1 || card[i] > hand.size());
        //add card to meld pile
        melds.push_back(hand[card[i]-1]);
    }
    //check meld pile for validity
    if(checkMelds(possibleMelds)){
        if(num == hand.size()){
            hand.clear();
        }
        else{
            //erase chosen cards from hand
            for(int i = 0; i < num; i++){
                hand.erase(hand.begin()+(card[i]-1));
            }
        }
    }
    //if not valid
    else{
        //erase chosen cards from meld pile
        for(int i = 0; i < num; i++){
            melds.pop_back();
        }
    }
}
/* *********************************************************************
Function Name: checkMelds
Purpose: to validate the melds a player tries to make
Parameters:
            vector<Melds> possibleMelds - a container for the game's available melds
Return Value:
            boolean value that indicates whteher a meld is legal or not
Local Variables:
            bool isGood - a boolean value storing the legaity of the meld
            int t_meldPoints - an integer containing the current meld's point total
Algorithm:
            1) check current meld against all available melds
            2) add the meld value for each meld to t_meldPoints (adds 0 if the meld does not exist)
            3) if t_meldPoints is greater tha meldPoints (meaning a new meld was created that turn...
            4) set isGood to true
            5) add to the round score of the player
            6) update meldPoints to be t_meldPoints (the new amount of points earned from melds
            7) return isGood
Assistance Received: none
********************************************************************* */
bool Human::checkMelds(vector<Melds> possibleMelds){
    //assign isGood to to false and t_meldPoints to 0
    bool isGood = false;
    int t_meldPoints = 0;
    //loop through possibleMelds
    for(int i = 0; i < possibleMelds.size(); i++){
        //add value of the meld to t_meldPoints
        t_meldPoints += possibleMelds[i].checkMelds(melds, i);
    }
    //if t_meldPints is greater than meldPoints (a new med was created)
    if(t_meldPoints > meldPoints){
        //assign isGood to true
        isGood = true;
        //update roundScore
        roundScore = roundScore + (t_meldPoints - meldPoints);
        //update meldPoints
        meldPoints = t_meldPoints;
    }
    return isGood;
}

