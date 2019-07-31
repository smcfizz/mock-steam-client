#include <iostream>
#include "Player.h"

Player::Player(int id, string name){
    playerID = id;
    playerName = name;
}

int Player::getID() { return playerID; }

string Player::getName() { return playerName; }

int Player::getGamerScore() {return gamerScore; }

void Player::addGame(int gameID, string ign) {
    //Add ign with key being id of game played
    gamesPlayed[gameID] = ign;
}

void Player::addFriend(Player* p) {
    friendsList[p->getID()] = p;
}

void Player::addWinVictory(Victory* v) {
    gameVictoriesEarned[v->victoryID] = v;
    gamerScore += v->victoryPoints;
    v->timesAchieved++;
    v->playersAchieved.push_back(this->playerID);
}

bool Player::playsGame(int id) {
    auto it = gamesPlayed.find(id);
    return it != gamesPlayed.end();
}

map<int, string> Player::getGamesPlayed() { return gamesPlayed; }
