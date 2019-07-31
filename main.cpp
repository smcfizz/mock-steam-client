#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <map>
#include <climits>
#include <cstdlib>
#include "Victory.h"
#include "Player.h"
#include "Game.h"

using namespace std;

const int COLUMN = 25;

//Print out all players or games that have been added to the database
template <typename T>
void print(map<int, T*> m) {
    for (auto elem : m) {
        cout << "ID: " << elem.second->getID() << "\t\tName: " <<
            elem.second->getName() << endl;
    }
}

//Traverses a string and removes any whitespace or double quotes that
//are found. The firstQuoteRemoved flag determines if any whitespace found
//should be removed from the string based off whether or not the beginning
//double quote was already removed, which is a side effect of processing
//some of the initial input.
string removeWhitespaceAndQuotes(string s, bool firstQuoteRemoved) {
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) == '\"') {
            //Toggle flag (1st quote = don't delete whitespace, 2nd = do delete)
            firstQuoteRemoved = !firstQuoteRemoved;
            s.erase(s.begin()+i);
        }
        else if (s.at(i) == ' ' && !firstQuoteRemoved)
            s.erase(s.begin()+i);
    }
    return s;
}

int main() {

    map<int, Player*> players;
    map<int, Game*> games;

    string command;

    while (true) {

        /*
            The program processes commands by taking the first parameter
            from the standard input stream to determine which command to
            execute and then acting accordingly. The loop will terminate
            when an 'X' (non-case-sensitive) is passed in as a leading
            argument/command.
        */

        cin >> command;

        if (command == "x" || command == "X") {
            break;
        }

        //Determine following steps based off of given command

        if (command == "AddPlayer") {
            //The same basic process is followed for each possible command
            //1: Declare required variables to store remaining parameters
            int id;
            string name;

            //2: Store remaining parameters
            cin >> id;

            //The following code is used to discard of unnecessary characters
            //and ensure proper formatting of data before entry
            getline(cin, name);
            name = name.substr(2, name.size());
            name = removeWhitespaceAndQuotes(name, true);

            //3: Create object and/or add to data structure 
            //   or output data to console (if necessary)
            players[id] = new Player(id, name);
        }
        else if (command == "AddGame") {
            //1
            int id;
            string name;

            //2
            cin >> id;
            getline(cin, name);

            name = name.substr(2, name.size());
            name = removeWhitespaceAndQuotes(name, true);

            //3
            games[id] = new Game(id, name);
        }
        else if (command == "AddVictory") {
            //1
            int gameID;
            int victoryID;
            string victoryName;
            int victoryPoints;
            string temp;

            //2
            cin >> gameID;
            cin >> victoryID;
            getline(cin, temp); //Will be split into 2 remaining parameters

            //Separate 3rd param (achievement name) from 4th param (victory points)
            int i = 0;
            temp = temp.substr(2, temp.size());
            while (temp.at(i) != '\"') {
                i++;
            }
            victoryName = temp.substr(0, i);
            temp.erase(0, i);
            temp = temp.substr(2, temp.size());
            victoryPoints = stoi(temp);
            victoryName = removeWhitespaceAndQuotes(victoryName, true);

            //3
            auto g_it = games.find(gameID);
            g_it->second->addVictory(
                new Victory(gameID, victoryID, victoryName, victoryPoints));
        }
        else if (command == "Plays") {
            //1
            int playerID;
            int gameID;
            string playerIGN;

            //2
            cin >> playerID;
            cin >> gameID;
            getline(cin, playerIGN);

            playerIGN = playerIGN.substr(2, playerIGN.size());
            playerIGN = removeWhitespaceAndQuotes(playerIGN, true);

            //3
            auto p_it = players.find(playerID);
            auto g_it = games.find(gameID);

            p_it->second->addGame(g_it->first, playerIGN);
            g_it->second->addPlayerToPlayedBy(p_it->first);
        }
        else if (command == "AddFriends") {
            //1
            int playerID_1;
            int playerID_2;

            //2
            cin >> playerID_1;
            cin >> playerID_2;

            //3
            auto p_it1 = players.find(playerID_1);
            auto p_it2 = players.find(playerID_2);

            p_it1->second->addFriend(p_it2->second);
            p_it2->second->addFriend(p_it1->second);
        }
        else if (command == "WinVictory") {
            //1
            int playerID;
            int gameID;
            int victoryID;

            //2
            cin >> playerID;
            cin >> gameID;
            cin >> victoryID;

            //3
            auto p_it = players.find(playerID);
            auto g_it = games.find(gameID);

            p_it->second->addWinVictory(g_it->second->getVictory(victoryID));
        }
        else if (command == "FriendsWhoPlay") {
            //1
            int playerID;
            int gameID;

            //2
            cin >> playerID;
            cin >> gameID;

            //3
            string name = players.find(playerID)->second->getName();

            cout << string(3*COLUMN, '-') << endl;
            cout << "FriendsWhoPlay" << endl;
            cout << string(3*COLUMN, '-') << endl;

            string game = games[gameID]->getName();
            cout << name << "'s friends who play " << game << ":" << endl << endl;

            int position = 1;
            for (auto it : players[playerID]->friendsList) {
                if (it.second->playsGame(gameID))
                    cout << position++ << ". " << it.second->getName() << endl;
            }

            cout << endl << endl << endl << endl << endl;
        }
        else if (command == "ComparePlayers") {
            //1
            int playerID_1;
            int playerID_2;
            int gameID;
        
            //2
            cin >> playerID_1;
            cin >> playerID_2;
            cin >> gameID;
        
            //3
            auto p_it1 = players.find(playerID_1);
            auto p_it2 = players.find(playerID_2);
            auto g_it = games.find(gameID);

            int p1_vScore = 0;
            int p2_vScore = 0;

            cout << string(3*COLUMN, '-') << endl;
            cout << "ComparePlayers" << endl;
            cout << string(3*COLUMN, '-') << endl << endl;

            cout << string(COLUMN,' ');
            cout << "GAME: " << g_it->second->getName() << endl << endl;

            //p1
            cout << p_it1->second->getName() << endl;
            cout << string(3*COLUMN,'-') << endl;
            cout << left << setw(COLUMN) << "Victory name";
            cout << "Victory points" << endl << endl;

            //Print victories and their corresponding victoryPoint values. Sum p1 victory score
            for (auto elem : p_it1->second->gameVictoriesEarned) {
                if (elem.second->gameID == gameID) {
                    cout << left << setw(COLUMN) << elem.second->victoryName;
                    cout << left << setw(COLUMN) << elem.second->victoryPoints << endl;
                    p1_vScore += elem.second->victoryPoints;
                }
            }
            cout << endl;
            cout << left << setw(COLUMN) << "Total victory Score: ";
            cout << left << setw(COLUMN) << p1_vScore << endl << endl << endl;

            //p2
            cout << p_it2->second->getName() << endl;
            cout << string(3*COLUMN,'-') << endl;
            cout << left << setw(COLUMN) << "Victory name";
            cout << "Victory points" << endl << endl;

            //Repeat like above for p2
            for (auto elem : p_it2->second->gameVictoriesEarned) {
                if (elem.second->gameID == gameID) {
                    cout << left << setw(COLUMN) << elem.second->victoryName;
                    cout << left << setw(COLUMN) << elem.second->victoryPoints << endl;
                    p2_vScore += elem.second->victoryPoints;
                }
            }
            cout << endl;
            cout << left << setw(COLUMN) << "Total victory Score: ";
            cout << left << setw(COLUMN) << p2_vScore << endl << endl << endl << endl << endl;
        }
        else if (command == "SummarizePlayer") {
            //1
            int playerID;

            //2
            cin >> playerID;

            //3
            string name;
            int score;
            map<int, Player*> friends;
            map<int, string> pGames;

            auto p_it = players.find(playerID);
            score = p_it->second->getGamerScore();
            name = p_it->second->getName();
            friends = p_it->second->friendsList;
            pGames = p_it->second->getGamesPlayed();

            cout << string(3*COLUMN, '-') << endl;
            cout << "SumarizePlayer" << endl;
            cout << string(3*COLUMN, '-') << endl;

            cout << "Player: " << name << endl;
            cout << "Total Gamerscore: " << score << endl << endl;

            cout << left << setw(COLUMN) << "Game";
            cout << left << setw(COLUMN-10) << "Victories";
            cout << left << setw(COLUMN-10) << "Gamerscore";
            cout << "IGN" << endl;
            cout << string(3*COLUMN,'-') << endl;

            //Print games
            int position = 1;
            int totalGameVictories;
            for (auto g_elem : pGames) { //Iterate through games played by player
                auto g_it = games.find(g_elem.first); //Focus on current game
                cout << position << ". ";
                cout << left << setw(COLUMN-3) << g_it->second->getName(); //Print name of game
                int relevantVictories = 0;
                int victoryPointsEarned = 0;
                for (auto pv_it : p_it->second->gameVictoriesEarned) { //Iterate through list of player-earned victories
                    if (pv_it.second->gameID == g_it->first) { //Check if a victory belongs to current game
                        relevantVictories++;
                        victoryPointsEarned += pv_it.second->victoryPoints;
                    }
                }
                totalGameVictories = g_it->second->victories.size();
                string victoryRatio = to_string(relevantVictories) + "/" + to_string(totalGameVictories);

                cout << left << setw(COLUMN-10) << victoryRatio;
                cout << left << setw(COLUMN-10) << victoryPointsEarned;
                cout << g_elem.second << endl;
                position++;
            }
            cout << endl;

            cout << left << setw(COLUMN) << "Friend";
            cout << "Gamerscore" << endl;
            cout << string(2*COLUMN,'-') << endl;
            
            //Print friends and their gamer scores
            position = 1;
            for (auto elem : p_it->second->friendsList) {
                cout << position << ". ";
                cout << left << setw(COLUMN-3) << elem.second->getName();
                cout << elem.second->getGamerScore() << endl;
                position++;
            }
            cout << endl << endl << endl << endl << endl;
        }
        else if (command == "SummarizeGame") {
            //1
            int gameID;

            //2
            cin >> gameID;

            //3
            cout << string(3*COLUMN, '-') << endl;
            cout << "SumarizeGame" << endl;
            cout << string(3*COLUMN, '-') << endl << endl;

            auto g_it = games.find(gameID);
            cout << left << string(1.25*COLUMN,' ');
            cout << g_it->second->getName() << endl << endl;
            cout << "Players" << endl;
            cout << string(3*COLUMN,'-') << endl;

            //Print players who play this game
            int position = 1;
            for (auto it : g_it->second->playedBy) {
                auto p_it = players.find(it);
                cout << position << ". ";
                cout << p_it->second->getName() << endl;
                position++;
            }
            cout << endl;

            cout << left << setw(COLUMN) << "Victories";
            cout << "Times Achieved" << endl;
            cout << string(3*COLUMN,'-') << endl;

            //Print victories for this game and how many times they've been achieved
            position = 1;
            for (auto it : g_it->second->victories) {
                cout << position << ". ";
                cout << left << setw(COLUMN-3) << it.second->victoryName;
                cout << it.second->timesAchieved << endl;
                position++;
            }
            cout << endl << endl << endl << endl << endl;
        }
        else if (command == "SummarizeVictory") {
            //1
            int gameID;
            int victoryID;

            //2
            cin >> gameID;
            cin >> victoryID;

            //3
            cout << string(3*COLUMN, '-') << endl;
            cout << "SumarizeVictory" << endl;
            cout << string(3*COLUMN, '-') << endl << endl;

            auto g_it = games.find(gameID);
            auto v_it = g_it->second->victories.find(victoryID);
            cout << left << string(COLUMN,' '); 
            cout << v_it->second->victoryName << " (" << g_it->second->getName() << ")" << endl;
            cout << endl << endl;
            cout << "Players achieved" << endl;
            cout << string(3*COLUMN,'-') << endl;

            //Print players who have achieved this victory
            double numberOfPlayers;
            int position = 1;
            for (auto it : v_it->second->playersAchieved) {
                cout << position << ". ";
                cout << players.find(it)->second->getName() << endl;
                numberOfPlayers++;
                position++;
            }

            cout << endl << "Percent with this victory: ";
            cout << (double) numberOfPlayers / ((double) g_it->second->playedBy.size()) << endl;

            cout << endl << endl << endl << endl << endl;
        }
        else if (command == "VictoryRanking") {
            //TODO adjust variable names and output for understandability

            //3
            cout << string(3*COLUMN,'-') << endl;
            cout << "VictoryRanking" << endl;
            cout << string(3*COLUMN,'-') << endl << endl;

            map<int,int> scoresAndIds;
            vector<int> scores;
            vector<int> temp;
            //Copy all players into map where key is gamerscore
            //Copy all scores into a vector
            for (auto p_it : players) {
                scoresAndIds[p_it.second->getGamerScore()] = p_it.second->getID();
                temp.push_back(p_it.second->getGamerScore());
            }
            //Sort vector of gamerscores
            sort(temp.begin(), temp.end());
            //Flip data set by emptying into a new vector
            for (int i = temp.size()-1; i >= 0; i--) {
                scores.push_back(temp.at(i));
            }
            //Print players in order of decending gamerscore by searching for them via 
            //map where gamerscore is key
            int position = 1;
            for (auto it : scores) {
                auto a = scoresAndIds.find(it);
                cout << position << "." << players.find(a->second)->second->getName() << 
                    "\t\t" << a->first << endl;
                position++;
            }
            cout << endl << endl << endl << endl << endl;
        }
        //Additional commands
        else if (command == "PrintPlayers") {
            cout << "Players:" << endl;
            print(players);
            cout << endl;
        }
        else if (command == "PrintGames") {
            cout << "Games:" << endl;
            print(games);
            cout << endl;
        }
    }
}
