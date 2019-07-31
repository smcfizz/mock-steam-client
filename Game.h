#ifndef GAME_H
#define GAME_H

#include <map>
#include <string>
#include <vector>
#include "Player.h"
#include "Victory.h"

using namespace std;

class Game{
    private:
        int gameID;
        string gameName;
    public:
        vector<int> playedBy;
        map<int, Victory*> victories;
        Game(int id, string name);
        int getID();
        string getName();
        Victory* getVictory(int id);
        void addVictory(Victory* v);
        void addPlayerToPlayedBy(int id);
};

#endif
