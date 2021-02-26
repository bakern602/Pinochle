//
//  Human.hpp
//  Pinochle
//
//  Created by Benjamin Kern on 10/14/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#ifndef Human_hpp
#define Human_hpp

#include <stdio.h>
#include "Player.h"

class Human: public Player{
private:
    
public:
    Card playCard(int lead, Card leadCard, Card trumpCard);
    void makeMelds(vector<Melds> possibleMelds);
    bool checkMelds(vector<Melds> possibleMelds);
};

#endif /* Human_hpp */
