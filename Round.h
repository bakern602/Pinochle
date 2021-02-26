//
//  Round.hpp
//  Pinochle
//
//  Created by Benjamin Kern on 9/9/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#ifndef Round_hpp
#define Round_hpp

#include <stdio.h>
#include <sstream>
#include <fstream>
#include "Deck.h"
#include "Player.h"

class Round{
private:
    int roundNumber;
    int nextPlayer;
    vector<Card> stockPile;
    Card trumpCard;
    Card leadCard;
    Card chaseCard;
    Player *playerList[2];
    vector<Melds> possibleMelds;
public:
    Round(Player *human, Player *computer, Deck deck, int inNextPlayer, int inRoundNumber, vector<Melds> melds);
    void shuffleDeck();
    void dealCards();
    void setStock(vector<Card> inStock);
    void setRoundNumber(int inRoundNumber);
    void setTrump(Card t_trump);
    void playRound();
    int playCards();
    int menu();
    Card getTrump();
    void setMeldSuit();
    stringstream print(Player *human, Player *computer);
    void saveGame(string gameState);
    
};

#endif /* Round_hpp */
