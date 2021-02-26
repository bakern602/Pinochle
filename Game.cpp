//
//  Game.cpp
//  Pinochle
//
//  Created by Benjamin Kern on 9/9/20.
//  Copyright © 2020 Benjamin Kern. All rights reserved.
//

#include "Game.h"

/* *********************************************************************
Function Name: Game (constructor)
Purpose: to begin a game
Parameters:
          none
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) create melds and players, set round number to 1 and play to yes (meaning they will play a new round)
            2) ask whether to start a new game or resume a current game
Assistance Received: none
********************************************************************* */
Game::Game(){
    //create all the melds
    defineMelds();
    //assign human reference variable to the human object
    human = &humanPlayer;
    //assign computer reference variable to the computer object
    computer = &compPlayer;
    //roundNumber is assigned 1 for the start of the game
    roundNumber = 1;
    //play is assigned yes to play a new round
    play = 'y';
    //prompt user on whether to start a saved game or new game and alidate
    do{
        cout << "Would you like to resume a game (0) or start a new game (1)? ";
        cin >> save;
    }while(save < 0 || save > 1);
    
}
/* *********************************************************************
Function Name: playGame
Purpose: to play the game
Parameters:
            none
Return Value:
            none
Local Variables:
            none
Algorithm:
            1) if user decides to play a saved game, retrieve file and load in the game
            2) if user decides to start a new game do a coin toss to start off
            3) continue creating new rounds until user decides to quit
            4) upon exiting print the player's scores along with the winner
Assistance Received: none
********************************************************************* */
void Game::playGame(){
    //start new game
    if(save == 1){
        //nextPlayer is assigned the value of the return value of coinToss()
        nextPlayer = coinToss();
    }
    //start saved game
    else{
        //resume a game
        string filePath;
        cout << "Enter the file name you wish to resume\n";
        cin >> filePath;
        resumeGame(filePath);
        roundNumber++;
        //prompt user to start a new game
        cout << "Would you like to play another round (y/n)? ";
        cin >> play;
    }
    //continue playing while play is yes
    while(play == 'y'){
        Round round(human, computer, deck, nextPlayer, roundNumber, possibleMelds);
        round.playRound();
        do{
            cout << "Would you like to play another round (y/n)? ";
            cin >> play;
        }while(play != 'n' && play != 'y');
    }
    //output final scores and winner at the end of the game
    cout << "Final Score: Human " << human->getScore() << ", Computer " << computer->getScore() << ".";
    if(human->getScore() > computer->getScore()) cout << " Human wins!" << endl;
    else cout << " Computer wins!" << endl;
    
}
/* *********************************************************************
Function Name:coinToss
Purpose: to decide who plays first in the round randomly
Parameters:
            none
Return Value:
            int side - the side (heads or tails) the player chooses
            int flip - a random number (1 or 2) that the coin lands on
Local Variables:
            1) prompt user to input heads or tails
            2) compare the chosen side to the actual flipped side
            3) output and return winner
Algorithm:
            
Assistance Received: none
********************************************************************* */
int Game::coinToss(){
    int side;
    //flip assigned a random number 1 or 2
    int flip = rand() % 2 + 1;
    //prompt user for heads or tails and validate
    do{
        cout << "Coin toss. Select '1' for heads and '2' for tails";
        cin >> side;
    }while(side != 1 && side != 2);
    //human won toss
    if(side == flip){
        cout << "You won the toss. You will go first. The leading player at the end of the round will go first the following round.\n";
        return 0;
    }
    //human lost toss
    else{
        cout << "You lost the toss. The computer will go first. The leading player at the end of the round will go first the following round.\n";
        return 1;
    }
}

/* *********************************************************************
Function Name: defineMelds
Purpose: to definie the melds that are available in a game
Parameters:
            none
Return Value:
            none
Local Variables:
            vector<int> faces - the faces that are unique to each meld (updated for each)
            vector<char suits - the suits that are unique to each meld (updated for each)
Algorithm:
            1) for each meld...
            2) update faces so they are correct for the meld
            3) update suits so the match up for each card
            4) for the melds that require a trump card, I loaded in hearts for the suit, but it will be updated throughout the game
Assistance Received: none
********************************************************************* */
void Game::defineMelds(){
    //this entire function just redefines the faces and suits required for each meld
    //if a meld needs a trump card suit as part of the definition, I just used Hearts as a place holder
    //for example the first meld, flush, requires A, K, Q, J, X, but I don't know the suit yet so I did hearts
    vector<int> faces = {14, 10, 13, 12, 11};
    vector<char> suits = {'H', 'H', 'H', 'H', 'H'};
    possibleMelds.push_back(Melds(faces, suits, 150));
    faces = {13, 12};
    suits = {'H', 'H'};
    possibleMelds.push_back(Melds(faces, suits, 40));
    faces = {13, 12};
    suits = {'H', 'H'};
    possibleMelds.push_back(Melds(faces, suits, 20));
    faces = {9};
    suits = {'H'};
    possibleMelds.push_back(Melds(faces, suits, 10));
    faces = {14, 14, 14, 14};
    suits = {'C', 'H', 'S', 'D'};
    possibleMelds.push_back(Melds(faces, suits, 100));
    faces = {13, 13, 13, 13};
    possibleMelds.push_back(Melds(faces, suits, 80));
    faces = {12, 12, 12, 12};
    possibleMelds.push_back(Melds(faces, suits, 60));
    faces = {11, 11, 11, 11};
    possibleMelds.push_back(Melds(faces, suits, 40));
    faces = {12, 11};
    suits = {'S', 'D'};
    possibleMelds.push_back(Melds(faces, suits, 40));
    
}

/* *********************************************************************
Function Name: resumeGame
Purpose: to load a saved file
Parameters:
            string filePath - the file path in which the game will be loaded from
Return Value:
            none
Local Variables:
            vector<Card> t_stock - a temporary container for the stock pile
            vector<Card> t_stock2 - to store the reversed t_stock
            vector<Card> t_capture1 - computer's incoming capture pile
            vector<Card> t_capture2 - human's incoming capture pile
            vector<Card> t_hand1 - computer's incoming hand
            vector<Card> t_hand2 - human's incoming hand
            vector<Card> t_meld1 - computer's incoming meld
            vector<Card> t_meld2 - human's incoming meld
            Card t_trump a card to hold the trump card to be passed
            int score1 - computer's incoming score
            int score2 - human's incoming score
            int roundScore1 - computer's incoming score of current round
            int roundScore2 - human's incoming score of current round
            string line - the current line of the file being read
            ifstream myfile - the object that allows the computer to read a file
Algorithm:
            1) check if filepath is valid (if not, quit)
            2) loop through each line of the file
            3) find keywords in each line (i.e. Human, Computer, Round, etc)
            4) parse through each line and save the needed information the temporary variables labeled above
            5) start a new round
            6) update all components of the newly created round with all the information that was just parsed through
            7) start round play
Assistance Received: none
********************************************************************* */
void Game::resumeGame(string filePath){
    //initialize all my lpace holder variables
    vector<Card> t_stock;
    vector<Card> t_stock2;
    vector<Card> t_capture1;
    vector<Card> t_capture2;
    vector<Card> t_hand1;
    vector<Card> t_hand2;
    vector<Card> t_meld1;
    vector<Card> t_meld2;
    Card t_trump;
    int score1;
    int score2;
    int roundScore1;
    int roundScore2;
    string line;
    ifstream myfile;
    
    //open file
    myfile.open(filePath);
    //if file not found, exit program
    if (!myfile) {
        cout << "File not found. Unable to open file";
        exit(1);
    }
    
    //loop through each line of file
    while(getline(myfile, line)){
        stringstream mystream(line);
        
        string word;
        mystream >> word;
        
        //the line begins with round
        if(word.find("Round:") != string::npos){
            //find the round number and assign it to roundNumber
            while(mystream >> word){
                roundNumber = stoi(word);
            }
        }
        
        //line begins with Stock
        if(word.find("Stock") != string::npos){
            //loop through each word in the line
            //parse each card and add the card to the t_stock
            while(mystream >> word){
                if(word[0] == 'X'){
                    t_stock.push_back(Card(10, getPoints(word[0]), word[1]));
                }
                else if(word[0] == 'J'){
                    t_stock.push_back(Card(11, getPoints(word[0]), word[1]));
                }
                else if(word[0] == 'Q'){
                    t_stock.push_back(Card(12, getPoints(word[0]), word[1]));
                }
                else if(word[0] == 'K'){
                    t_stock.push_back(Card(13, getPoints(word[0]), word[1]));
                }
                else if(word[0] == 'A'){
                    t_stock.push_back(Card(14, getPoints(word[0]), word[1]));
                }
                else{
                    t_stock.push_back(Card(9, getPoints(word[0]), word[1]));
                }
            }
            //it needs to be reversed to be put back in the correct order
            for(vector<Card>::reverse_iterator it = t_stock.rbegin(); it != t_stock.rend(); it++){
                t_stock2.push_back(*it);
            }
        }
        
        //line begins with computer
        if(word.find("Computer:") != string::npos){
            //there are 4 lines of information regarding the computer
            //the first is score, then hand, then capture, then meld
            //when we finishing parsing each line for the correct information
            //we go to the next line
            
            //finds score
            string attr;
            getline(myfile, attr);
            stringstream temp(attr);
            string score;
            
            temp >> score;
            temp >> score;
            
            score1 = stoi(score);
            
            temp >> score;
            temp >> score;
            
            //sets score to roundScore1
            roundScore1 = stoi(score);
            
            //finds hand
            getline(myfile, attr);
            stringstream temp2(attr);
            string card;
            temp2 >> card;
            //loops through each word in the hand
            //parses each card and adds it to t_hand1
            while(temp2 >> card){
                if(card[0] == 'X'){
                    t_hand1.push_back(Card(10, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'J'){
                    t_hand1.push_back(Card(11, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'Q'){
                    t_hand1.push_back(Card(12, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'K'){
                    t_hand1.push_back(Card(13, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'A'){
                    t_hand1.push_back(Card(14, getPoints(card[0]), card[1]));
                }
                else{
                    t_hand1.push_back(Card(9, getPoints(card[0]), card[1]));
                }
            }
            //find capture
            getline(myfile, attr);
            stringstream temp3(attr);
            temp3 >> card;
            temp3 >> card;
            //parses each card in the capture pile and adds it to t_capture1
            while(temp3 >> card){
                if(card[0] == 'X'){
                    t_capture1.push_back(Card(10, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'J'){
                    t_capture1.push_back(Card(11, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'Q'){
                    t_capture1.push_back(Card(12, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'K'){
                    t_capture1.push_back(Card(13, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'A'){
                    t_capture1.push_back(Card(14, getPoints(card[0]), card[1]));
                }
                else{
                    t_capture1.push_back(Card(9, getPoints(card[0]), card[1]));
                }
            }
            //finds meld
            getline(myfile, attr);
            stringstream temp4(attr);
            temp4 >> card;
            //parses the cards in meld the same way as the previous instance
            while(temp4 >> card){
                if(card[0] == 'X'){
                    t_meld1.push_back(Card(10, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'J'){
                    t_meld1.push_back(Card(11, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'Q'){
                    t_meld1.push_back(Card(12, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'K'){
                    t_meld1.push_back(Card(13, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'A'){
                    t_meld1.push_back(Card(14, getPoints(card[0]), card[1]));
                }
                else{
                    t_meld1.push_back(Card(9, getPoints(card[0]), card[1]));
                }
            }
        }
        
        //finds the word human
        //everything in human is exactly the same as computer
        //except the variables being updated are different, but the process is the same
        //it finds the score, hand, capture, meld and parses each for the correct information
        if(word.find("Human:") != string::npos){
            string attr;
            getline(myfile, attr);
            stringstream temp(attr);
            string score;
            
            temp >> score;
            temp >> score;
            
            score2 = stoi(score);
            
            temp >> score;
            temp >> score;
            
            roundScore2 = stoi(score);
            
            getline(myfile, attr);
            stringstream temp2(attr);
            string card;
            temp2 >> card;
            while(temp2 >> card){
                if(card[0] == 'X'){
                    t_hand2.push_back(Card(10, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'J'){
                    t_hand2.push_back(Card(11, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'Q'){
                    t_hand2.push_back(Card(12, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'K'){
                    t_hand2.push_back(Card(13, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'A'){
                    t_hand2.push_back(Card(14, getPoints(card[0]), card[1]));
                }
                else{
                    t_hand2.push_back(Card(9, getPoints(card[0]), card[1]));
                }
            }
            getline(myfile, attr);
            stringstream temp3(attr);
            temp3 >> card;
            temp3 >> card;
            while(temp3 >> card){
                if(card[0] == 'X'){
                    t_capture2.push_back(Card(10, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'J'){
                    t_capture2.push_back(Card(11, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'Q'){
                    t_capture2.push_back(Card(12, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'K'){
                    t_capture2.push_back(Card(13, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'A'){
                    t_capture2.push_back(Card(14, getPoints(card[0]), card[1]));
                }
                else{
                    t_capture2.push_back(Card(9, getPoints(card[0]), card[1]));
                }
            }
            getline(myfile, attr);
            stringstream temp4(attr);
            temp4 >> card;
            while(temp4 >> card){
                if(card[0] == 'X'){
                    t_meld2.push_back(Card(10, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'J'){
                    t_meld2.push_back(Card(11, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'Q'){
                    t_meld2.push_back(Card(12, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'K'){
                    t_meld2.push_back(Card(13, getPoints(card[0]), card[1]));
                }
                else if(card[0] == 'A'){
                    t_meld2.push_back(Card(14, getPoints(card[0]), card[1]));
                }
                else{
                    t_meld2.push_back(Card(9, getPoints(card[0]), card[1]));
                }
            }
        }
        
        if(word.find("Trump") != string::npos){
            mystream >> word;
            while(mystream >> word){
                if(word[0] == 'X'){
                    t_trump = (Card(10, getPoints(word[0]), word[1]));
                }
                else if(word[0] == 'J'){
                    t_trump = (Card(11, getPoints(word[0]), word[1]));
                }
                else if(word[0] == 'Q'){
                    t_trump = (Card(12, getPoints(word[0]), word[1]));
                }
                else if(word[0] == 'K'){
                    t_trump = (Card(13, getPoints(word[0]), word[1]));
                }
                else if(word[0] == 'A'){
                    t_trump = (Card(14, getPoints(word[0]), word[1]));
                }
                else if(word[0] == '9'){
                    t_trump = (Card(9, getPoints(word[0]), word[1]));
                }
                else{
                    t_trump = Card(0, 0, word[0]);
                }
            }
        }
        
        //finds Next
        if(word.find("Next") != string::npos){
            mystream >> word;
            //finds the player to play next
            while(mystream >> word){
                if(word == "Human"){
                    nextPlayer = 0;
                }
                else if(word == "Computer"){
                    nextPlayer = 1;
                }
            }
        }
    }
    //This process is how we get the points due to melds from each player
    //it does the same thing as the checking for melds in the player class
    //it iterates through each meld and finds all the melds and adds them up
    vector<int> meldPoints1;
    vector<int> meldPoints2;
    int max1 = 0;
    int maxIndex1 = 0;
    int max2 = 0;
    int maxIndex2 = 0;
    for(int i = 0; i < possibleMelds.size(); i++){
        meldPoints1.push_back(possibleMelds[i].checkMelds(t_meld2, i));
    }
    for(int i = 0; i < meldPoints1.size(); i++){
        if(meldPoints1[i] > max1){
            max1 = meldPoints1[i];
            maxIndex1 = i;
        }
    }
    for(int i = 0; i < possibleMelds.size(); i++){
        meldPoints2.push_back(possibleMelds[i].checkMelds(t_meld1, i));
    }
    for(int i = 0; i < meldPoints2.size(); i++){
        if(meldPoints2[i] > max2){
            max2 = meldPoints2[i];
            maxIndex2 = i;
        }
    }
    //begins a new round
    Round round(human, computer, deck, nextPlayer, roundNumber, possibleMelds);
    //updates round number
    round.setRoundNumber(roundNumber);
    //updates stock pile
    round.setStock(t_stock2);
    //updates trump card
    round.setTrump(t_trump);
    //updates computer hand
    computer->setHand(t_hand1);
    //updates human hand
    human->setHand(t_hand2);
    //updates computer capture
    computer->setCapture(t_capture1);
    //updates human capture
    human->setCapture(t_capture2);
    //updates computer melds
    computer->setMeld(t_meld1);
    //updates human melds
    human->setMeld(t_meld2);
    //updates computer game score
    computer->setScore(score1);
    //updates human game score
    human->setScore(score2);
    //updates computer round score
    computer->setRoundScore(roundScore1);
    //updates human round score
    human->setRoundScore(roundScore2);
    //updates meld suit for the round (trump suit)
    round.setMeldSuit();
    //updates human points from melds
    human->setMeldPoints(max1);
    //updates computer points from melds
    computer->setMeldPoints(max2);
    //plays a round
    round.playRound();
}

int Game::getPoints(char face){
    switch(face){
        case '9':
            return 0;
        case 'X':
            return 10;
        case 'J':
            return 2;
        case 'Q':
            return 3;
        case 'K':
            return 4;
        case 'A':
            return 11;
        default:
            return 0;
    }
}
