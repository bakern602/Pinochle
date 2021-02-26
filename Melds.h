//
//  Melds.hpp
//  Pinochle
//
//  Created by Benjamin Kern on 10/16/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#ifndef Melds_hpp
#define Melds_hpp

#include <stdio.h>
#include <vector>
#include "Card.h"

class Melds{
private:
    vector<Card> cards;
    int points;
public:
    Melds(vector<int> t_cards, vector<char> inSuits, int inPoints);
    void setSuits(char inSuit);
    int checkMelds(vector<Card> hand, int meld);
    vector<Card> getCards();
};

#endif /* Melds_hpp */
