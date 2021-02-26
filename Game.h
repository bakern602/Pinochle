//
//  Game.hpp
//  Pinochle
//
//  Created by Benjamin Kern on 9/9/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include "Round.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include "Melds.h"

class Game{
private:
    Deck deck;
    char play;
    int save;
    int roundNumber;
    int nextPlayer;
    Human humanPlayer;
    Computer compPlayer;
    Player *human;
    Player *computer;
    vector<Melds> possibleMelds;
public:
    Game();
    int coinToss();
    void defineMelds();
    void playGame();
    void resumeGame(string filePath);
    int getPoints(char face);
};

#endif /* Game_hpp */
