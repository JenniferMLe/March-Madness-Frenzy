/* ---------------------------------------------
Program 4: March Madness Frenzy

Course: CS 141, Spring 2022, Tues 9am lab
System: Mac using Visual Studio Code
Author: Jennifer Le
Date: 4/13/22
------------------------------------------------ */
#include <iostream>      // for cout and cin statements
#include <fstream>       // for file input and output
#include <string>        // for string operation and stoi
#include <sstream>       // for stringstream
#include <vector>        // vector operations
#include <cmath>         // for abs()
using namespace std;

class marchMadnessGame {   
    private:                 // each data memeber corresponds to a column
        string region;
        int rank1;
        string team1;
        int score1;
        int rank2;
        string team2;
        int score2;
        string winningTeam;
        int roundNumber;
        int gameNumber;

    public: 
        void setValues(string region, int rank1, string team1, int score1, int rank2,
        string team2, int score2, string winningTeam, int roundNumber, int gameNumber) {
            this->region = region;
            this->rank1 = rank1;
            this->team1 = team1;
            this->score1 = score1;
            this->rank2 = rank2;
            this->team2 = team2;
            this->score2 = score2;
            this->winningTeam = winningTeam;
            this->roundNumber = roundNumber;
            this->gameNumber = gameNumber;
        }
        string getRegion()   { return this->region; }
        int getRank1()       { return this->rank1; }
        string getTeam1()    { return this->team1; }
        int getScore1()      { return this->score1; }
        int getRank2()       { return this->rank2; }     
        string getTeam2()    { return this->team2; }
        int getScore2()      { return this->score2; }
        string getWinningTeam() { return this->winningTeam; }
        int getRoundNumber()    { return this->roundNumber; }
        int getGameNumber()     { return this->gameNumber; }

        void menuOption5message(int scoreDifference);    // utility function
        marchMadnessGame() { winningTeam = "N/A"; }      // default constructor

        // fully-qualified constructor
        marchMadnessGame(string region, int rank1, string team1, int score1, int rank2,  
        string team2,int score2, string winningTeam, int roundNumber, int gameNumber) {
            this->region = region;
            this->rank1 = rank1;
            this->team1 = team1;
            this->score1 = score1;
            this->rank2 = rank2;
            this->team2 = team2;
            this->score2 = score2;
            this->winningTeam = winningTeam;
            this->roundNumber = roundNumber;
            this->gameNumber = gameNumber;
        }    
};

// outputs message for menuOption 5, utility function definition 
void marchMadnessGame::menuOption5message(int scoreDifference){
    cout << "Round " << this->roundNumber << ", Game " << this->gameNumber
        << ": " << this->team1 << " vs " << this->team2 << ". " 
        << "Winner: " << this->winningTeam << "\nThe difference was " 
        << scoreDifference << " points.\n\n";
}

// reads in a csv file, and puts each data point in a vector called allData
void readFile(string csvFile, vector<string>& allData) {
    fstream inStream;
    inStream.open(csvFile);     // opens file
                
    string row;                
    string word;                // element that will be stored in the vector allData e.g "Oregon"

    while (inStream) {
        getline(inStream, row);
        stringstream s(row);
        while(getline(s, word, ',')) {    // input from a single row, stops when it reaches a comma
            allData.push_back(word);          
        }
    }  inStream.close();                  // closes file
}

// displays message that tells users what the program does
void displayProgramInfo(){
    cout << "Program 5: March Madness Frenzy\n"
        << "CS 141, Spring 2022, UIC\n\n"
        << "This program reads in data from NCAA Basketball Tournaments (aka March\n"
        << "Madness). It provides overall information regarding the data, allows you to\n"
        << "see the path taken to the championship, uses rankings of teams to determine\n"
        << "which region is expected to win at a given round and to find the best underdog\n"
        << "team, and calculates point differences within the games. You can also compare\n"
        << "the actual brackets to your own predictions!\n\n";
}

// displays menuOptions 1-7 and explain what each does 
void displayMenuOptions(){
    cout << "Select a menu option:\n"
        << "   1. Display overall information about the data\n"
        << "   2. Display the path of the winning team to the championship\n"
        << "   3. Determine which region is expected to win the championship based on a given round\n"
        << "   4. Identify the best underdog within a given round\n"
        << "   5. Find the shoo-in and nail-biting games within a given round, or overall\n"
        << "   6. Compare the actual brackets to your predicted brackets\n"
        << "   7. Exit\n"
        << "Your choice --> ";
}

// called when user chooses menuOption 1, elements of vector parameters are used to set and get values
void menuOption1(vector<string> region, vector<string> winningTeam, vector<int> roundNumber) {
    vector<marchMadnessGame> finalFour;   
    marchMadnessGame singleGame; 
    int totalGames = 0;            // counts total games played in tournament

    // loops through all games and sets values only if the game is a final four game (round == 4)
    for(int i = 0; i < region.size(); i++){   
        if (roundNumber.at(i) == 4) {  
            singleGame.setValues(region.at(i),0,"",0,0,"",0,winningTeam.at(i),0,0);
            finalFour.push_back(singleGame);
        }
        totalGames++;
    }
    cout << "Total number of games played in tournament: " << totalGames << endl;
    cout << "The Final Four contestants are:\n"; 
    // loops through finalFour and displays info using getters
    for (int i = 0; i < finalFour.size(); i++) {
        singleGame = finalFour.at(i);
        cout << "        " << singleGame.getRegion() << " region:    " << singleGame.getWinningTeam() << endl;
    } 
}

// called when user chooses menuOption 2, elements of vector parameters are used to set and get values
void menuOption2(vector<string> winningTeam, vector<string> team1,
vector<string> team2, vector<int> gameNumber, vector<int> roundNumber) {

    vector<marchMadnessGame> pathToChampionshipGames;  // games where winning team played in
    marchMadnessGame singleGame;
    string championTeam = winningTeam.at(0);   

    // loops through all games and sets values only if the winning team played in the game
    for(int i = 0; i < winningTeam.size(); i++ ) {
        if (winningTeam.at(i) == championTeam) {
            singleGame.setValues("",0,team1.at(i),0,0,team2.at(i),0,"",0,gameNumber.at(i));
            pathToChampionshipGames.push_back(singleGame);    // will eventually look like {round 6, 5, 4, 3, 2, 1} 
        }
    }
    int round = 1;
    cout << "Path to the championship:\n";
    for (int i = 5; i >= 0; i--) {      // i starts at 5 to reverse order and start with round 1 game
        singleGame = pathToChampionshipGames.at(i);
        cout << "Round " << round << ", Game " << singleGame.getGameNumber() << ": " 
            << singleGame.getTeam1() << " vs " << singleGame.getTeam2() << ". "
            << "Winner: " << championTeam << endl;
        round++;
    } 
}

// called when user chooses menuOption 3, elements of vector parameters are used to set and get values
void menuOption3(vector<string> winningTeam, vector<int> roundNumber, vector<string> team1,
vector<string> team2, vector<int> rank1, vector<int> rank2, string csvFile) {  
    cout << "Enter a round to be evaluated:\n"
        << "   Select 2 for round 2\n"
        << "   Select 3 for round 3 'Sweet 16'\n"
        << "   Select 4 for round 4 'Elite 8'\n"
        << "   Select 5 for round 5 'Final 4'\n"
        << "Your choice --> ";

    int roundInput;
    cin >> roundInput ;
    cout << "\nAnalyzing round " << roundInput << "...\n\n";

    if( roundInput == 5) { roundInput--; }     // choices 4 and 5 does the same thing
    vector<marchMadnessGame> roundGames;       // games whose round number matches user input
    marchMadnessGame singleGame;

    // loops through all games and sets values only if the round number matches user input
    for(int i = 0; i < winningTeam.size(); i++) {
        if (roundNumber.at(i) == roundInput) { 
            singleGame.setValues("",rank1.at(i),team1.at(i),0,rank2.at(i),team2.at(i),0,winningTeam.at(i),0,0);
            roundGames.push_back(singleGame);
        }
    }
    int totalRanks1, totalRanks2, totalRanks3, totalRanks4;       // one for each region
    totalRanks1 = totalRanks2 = totalRanks3 = totalRanks4 = 0;
    int divisor = roundGames.size() / 4;                          // used to add ranks to the right region

    // loops through all games with matching round number and adds ranks to correct region 
    for(int i = 0; i < roundGames.size(); i++) {
        singleGame = roundGames.at(i);
        if(singleGame.getTeam1() == singleGame.getWinningTeam()) {       // if team1 won the game                
            if (i/divisor == 0) { totalRanks1 = totalRanks1 + singleGame.getRank1(); }
            if (i/divisor == 1) { totalRanks2 = totalRanks2 + singleGame.getRank1(); }
            if (i/divisor == 2) { totalRanks3 = totalRanks3 + singleGame.getRank1(); }
            if (i/divisor == 3) { totalRanks4 = totalRanks4 + singleGame.getRank1(); }
        }
        if(singleGame.getTeam2() == singleGame.getWinningTeam()) {       // if team2 won the game
            if (i/divisor == 0) { totalRanks1 = totalRanks1 + singleGame.getRank2(); }
            if (i/divisor == 1) { totalRanks2 = totalRanks2 + singleGame.getRank2(); }
            if (i/divisor == 2) { totalRanks3 = totalRanks3 + singleGame.getRank2(); }
            if (i/divisor == 3) { totalRanks4 = totalRanks4 + singleGame.getRank2(); }
        }
    }
    vector<int> allRanks = {totalRanks1, totalRanks2, totalRanks3, totalRanks4};
    int maxRank = allRanks.at(0);  
    
    for(int i = 1; i < allRanks.size(); i++) {  // finds highest rank (lowest number)
        if(allRanks.at(i) <= maxRank) { maxRank = allRanks.at(i); }
    }
    vector<string> mensRegions = {"West", "South", "East", "Midwest"}; 
    vector<string> womensRegions = {"Greensboro", "Wichita", "Spokane", "Bridgeport"};
    string expectedRegion;    // expected region to win

    for(int i = 0; i < allRanks.size(); i++) { 
        if (allRanks.at(i) == maxRank) {          // if total ranks added together equals highest rank
            if (csvFile.substr(0,1) == "m" ) { expectedRegion = mensRegions.at(i); break; }   
            if (csvFile.substr(0,1) == "w" ) { expectedRegion = womensRegions.at(i); break; }
        }
    } cout << "The region expected to win is: " << expectedRegion << endl;   
}

// called when user chooses menuOption 4, elements of vector parameters are used to set and get values
void menuOption4(vector<int> roundNumber, vector<string> team1,
vector<string> team2, vector<int> rank1, vector<int> rank2){
    cout << "Enter a round to be evaluated:\n"
        << "   Select 2 for round 2\n"
        << "   Select 3 for round 3 'Sweet 16'\n"
        << "   Select 4 for round 4 'Elite 8'\n"
        << "   Select 5 for round 5 'Final 4'\n"
        << "   Select 6 for round 6 'Championship'\n"
        << "Your choice --> ";
    int roundInput;
    cin >> roundInput;

    vector<marchMadnessGame> roundGames;  // games whose round match input
    marchMadnessGame singleGame;

    for(int i = 0; i < roundNumber.size(); i++) {
        if(roundNumber.at(i) == roundInput) {       // if round number matches user input
            singleGame.setValues("",rank1.at(i),team1.at(i),0,rank2.at(i),team2.at(i),0,"",0,0);
            roundGames.push_back(singleGame);
        }
    }
    int lowestRank = 1; 
    // loop finds lowest Rank (greatest number) out of all games belonging in a given round
    for(int i = 0; i < roundGames.size(); i++) {
        singleGame = roundGames.at(i);
        if (singleGame.getRank1() >= lowestRank) { lowestRank = singleGame.getRank1(); }
        if (singleGame.getRank2() >= lowestRank) { lowestRank = singleGame.getRank2(); }
    }
    string underdogTeam; 
    // loop gets values if a team's rank equals lowest rank
    for(int i = 0; i < roundGames.size(); i++) {
        singleGame = roundGames.at(i);
        if (singleGame.getRank1() == lowestRank) { underdogTeam = singleGame.getTeam1(); break; }
        if (singleGame.getRank2() == lowestRank) { underdogTeam = singleGame.getTeam2(); break; }
    }
    cout << "The best underdog team is " << underdogTeam << " which has rank " << lowestRank << ".\n\n";
}

// called when user chooses menuOption 5, elements of vector parameters are used to set and get values
void menuOption5(vector<int> roundNumber, vector<string> team1, vector<string> team2, 
vector<int> score1, vector<int> score2, vector<string> winningTeam, vector<int> gameNumber) {
    cout << "Enter a round to be evaluated:\n"
        << "   Select 1 for round 1\n"
        << "   Select 2 for round 2\n"
        << "   Select 3 for round 3 'Sweet 16'\n"
        << "   Select 4 for round 4 'Elite 8'\n"
        << "   Select 5 for round 5 'Final 4'\n"
        << "   Select 6 for round 6 'Championship'\n"
        << "   Select 7 for the overall tournament\n"
        << "Your choice --> ";
    int roundInput;
    cin >> roundInput;
    
    if (roundInput == 7) { cout << "Analyzing the overall tournament...\n"; }
    else { cout << "\nAnalyzing round " << roundInput << "...\n\n"; } 

    vector<marchMadnessGame> roundGames;  // games whose round match input
    marchMadnessGame singleGame;

    // set values if round number matches input
    for(int i = 0; i < roundNumber.size(); i++) {
        if(roundNumber.at(i) == roundInput || roundInput == 7) {
            singleGame.setValues("",0,team1.at(i),score1.at(i),0,team2.at(i),
            score2.at(i),winningTeam.at(i),roundNumber.at(i),gameNumber.at(i));
            roundGames.push_back(singleGame);
        }
    }
    singleGame = roundGames.at(0);
    int scoreDifference, maxScoreDifference, minScoreDifference;
    maxScoreDifference = minScoreDifference = abs(singleGame.getScore1() - singleGame.getScore2());

    // finds the biggest and smallest difference in scores of games in given round
    for (int i = 0; i < roundGames.size(); i++) {
        singleGame = roundGames.at(i);
        scoreDifference = abs(singleGame.getScore1() - singleGame.getScore2()); 
        if (scoreDifference >= maxScoreDifference) { maxScoreDifference = scoreDifference; }
        if (scoreDifference <= minScoreDifference) { minScoreDifference = scoreDifference; }
    }
    // finds game with matching maxScoreDifference
    for (int i = 0; i < roundGames.size(); i++) {
        singleGame = roundGames.at(i);
        scoreDifference = abs(singleGame.getScore1() - singleGame.getScore2());
        if (scoreDifference == maxScoreDifference) {   
            cout << "The shoo-in game was:\n"; 
            singleGame.menuOption5message(scoreDifference);
            break;
        }
    }
    // finds game with matching mixScoreDifference
    for (int i = 0; i < roundGames.size(); i++) {     
        singleGame = roundGames.at(i);
        scoreDifference = abs(singleGame.getScore1() - singleGame.getScore2()); 
        if (scoreDifference == minScoreDifference) {   
            cout << "The nail-biting game was:\n";
            singleGame.menuOption5message(scoreDifference);
            break;
        }
    }
}

// called when user chooses menuOption 6, elements of vector parameters are used to set and get values
void menuOption6(vector<int> roundNumber, vector<string> winningTeam){
    cout << "Enter the name of the file with your predicted brackets:\n";
    string fileName;  cin >> fileName; 
    vector<string> allData;       // each element is a data point 
    readFile(fileName, allData); 

    vector<string> winningTeamPrediction;
    // only adds column 7 or the winning team column to vector using index    
    for(int i = 10; i < allData.size(); i++) {
        if (i % 10 == 7 ) { winningTeamPrediction.push_back(allData.at(i)); }
    }
    vector<marchMadnessGame> allGames;  
    marchMadnessGame singleGame;

    for (int i = 0; i < winningTeam.size(); i++) {
        singleGame.setValues("",0,"",0,0,"",0,winningTeam.at(i),roundNumber.at(i),0);
        allGames.push_back(singleGame);
    }
    int correctPredictedWins = 0;   // number of winning teams guessed correctly
    int score = 0;
    for(int i = 0; i < allGames.size(); i++) {
        singleGame = allGames.at(i);
        if ( singleGame.getWinningTeam() == winningTeamPrediction.at(i)) { 
            score = score + (singleGame.getRoundNumber() * 5);    // round number multiplied by 5 is added to score
            correctPredictedWins++;
        }
    }
    cout << "You correctly predicted the winner for " << correctPredictedWins << " games.\n";
    cout << "This means that you have a score of " << score << ".\n";
    
    if (score >= 250) { cout << " Great job! You could consider entering your predictions to win money!\n\n"; }
    else { cout << "You may want to learn more about basketball to improve your predictions next year.\n\n"; }
}
// __________________________________________________________________________________________________________________
int main() {
    displayProgramInfo();
    cout << "Enter the name of the file with the data for the NCAA tournament:\n";
    string fileName; cin >> fileName;
    vector<string> allData;           // each element is a data point in csv file
    readFile(fileName, allData);

    vector<string> region, team1, team2, winningTeam;
    vector<int> rank1, score1, rank2, score2, roundNumber, gameNumber;

    // populates vectors created above with coresponding data using allData's index
    for(int i = 10; i < allData.size(); i++) {               // start at 10 to omit first row
        if (allData.at(i) == "") { allData.at(i) = "0"; }    // incase element is empty, prevents stoi error
        if (i % 10 == 0) { region.push_back(allData.at(i)); }
        if (i % 10 == 1) { int intRank1 = stoi(allData.at(i)); rank1.push_back(intRank1);  }
        if (i % 10 == 2) { team1.push_back(allData.at(i)); }
        if (i % 10 == 3) { int intScore1 = stoi(allData.at(i)); score1.push_back(intScore1); }
        if (i % 10 == 4) { int intRank2 = stoi(allData.at(i)); rank2.push_back(intRank2); }
        if (i % 10 == 5) { team2.push_back(allData.at(i)); } 
        if (i % 10 == 6) { int intScore2 = stoi(allData.at(i)); score2.push_back(intScore2); }
        if (i % 10 == 7) { winningTeam.push_back(allData.at(i)); }
        if (i % 10 == 8) { int intRoundNumber = stoi(allData.at(i)); roundNumber.push_back(intRoundNumber); }
        if (i % 10 == 9) { int intGameNumber = stoi(allData.at(i)); gameNumber.push_back(intGameNumber); }
    }
    int menuOption;
    displayMenuOptions();
    cin >> menuOption;
    while(menuOption != 7) {

        if(menuOption == 1) {
            menuOption1(region, winningTeam, roundNumber);
        }
        else if(menuOption == 2) { 
            menuOption2(winningTeam, team1, team2, gameNumber, roundNumber);
        }
        else if(menuOption == 3) {
            menuOption3(winningTeam, roundNumber, team1, team2, rank1, rank2, fileName);
        }
        else if(menuOption == 4) { 
        menuOption4(roundNumber, team1, team2, rank1, rank2); 
        }
        else if(menuOption == 5) { 
            menuOption5(roundNumber, team1, team2, score1, score2, winningTeam, gameNumber);
        }
        else if(menuOption == 6) { 
            menuOption6(roundNumber, winningTeam);
        }
        else  { cout << " Invalid value.  Please re-enter a value from the menu options below.\n"; }

        displayMenuOptions();
        cin >> menuOption;      // "increments" loop
        continue;               // restarts loop with new menuOption
    }
    cout << "Exiting Program ... "; 
   return 0;
}
