//
//  Computer.hpp
//  Pinochle
//
//  Created by Benjamin Kern on 10/15/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#ifndef Computer_hpp
#define Computer_hpp

#include <stdio.h>
#include "Player.h"

class Computer:public Player{
private:
    
public:
    Card playCard(int lead, Card LeadCard, Card trumpCard);
    void makeMelds(vector<Melds> possibleMelds);
    void checkMelds(vector<int> possibleScores);
};

#endif /* Computer_hpp */
