
//
//  Player.hpp
//  Pinochle
//
//  Created by Benjamin Kern on 9/9/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Deck.h"
#include "Melds.h"

class Player{
protected:
    vector<Card> hand;
    vector<Card> capture;
    vector<Card> melds;
    int roundScore;
    int score;
    int meldPoints;
public:
    Player();
    void addCard(Card card);
    void clearPiles();
    void setHand(vector<Card> t_hand);
    void setRoundScore(int t_score);
    void setScore(int t_score);
    void setMeldPoints(int t_score);
    virtual Card playCard(int lead, Card leadCard, Card trumpCard);
    void addToCapture(Card card1, Card card2);
    void setCapture(vector<Card> inCapture);
    void setMeld(vector<Card> inMeld);
    virtual void makeMelds(vector<Melds> possibleMelds);
    void addScore(Card card1, Card card2);
    void addTotalScore();
    vector<Card> getHand();
    vector<Card> getCapture();
    vector<Card> getMelds();
    int getScore();
    int getRoundScore();
    void help(int lead, Card leadCard, Card trumpCard);
    
};

#endif /* Player_hpp */
