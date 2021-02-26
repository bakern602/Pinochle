//
//  main.cpp
//  Pinochle
//
//  Created by Benjamin Kern on 2/22/21.
//  Copyright © 2021 Benjamin Kern. All rights reserved.
//

#include <iostream>
#include <time.h>
#include "Game.h"

int main() {
    srand((time(NULL)));
    Game game;
    game.playGame();
}
