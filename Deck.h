//
//  Deck.hpp
//  Pinochle
//
//  Created by Benjamin Kern on 9/9/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include <vector>
#include "Card.h"

class Deck{
private:
    const int POINTS[6] = {0, 10, 2, 3, 4, 11};
    vector<Card> deck;
public:
    Deck();
    vector<Card> getDeck();
    void printDeck();
};

#endif /* Deck_hpp */
