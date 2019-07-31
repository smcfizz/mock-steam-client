#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>
#include "Game.h"
#include "Victory.h"

using namespace std;

class Player {
    private:
        int playerID;
        int gamerScore;
        string playerName;
        map<int, string> gamesPlayed;
        
    public:
        map<int, Player*> friendsList;
        map<int, Victory*> gameVictoriesEarned;
        map<int, string> getGamesPlayed();

        Player(int id, string name);

        int getID();
        string getName();
        int getGamerScore();

        void addGame(int gameID, string ign);
        void addFriend(Player* p);
        void addWinVictory(Victory* v);
        bool playsGame(int id);
};

#endif
