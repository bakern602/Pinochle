//
//  Card.hpp
//  Pinochle
//
//  Created by Benjamin Kern on 9/9/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <random>
using namespace std;
class Card{
private:
    int face;
    int points;
    char suit;
    
public:
    Card (){}
    Card(int inFace, int inPoints, char inSuit);
    void setFace(int inFace);
    void setSuit(char inSuit);
    int getFace();
    char getSuit();
    int getPoints();
    friend ostream& operator<<(std::ostream &strm, const Card &card);
    friend bool operator== (const Card &c1, const Card &c2);
};

#endif /* Card_hpp */
