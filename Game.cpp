#include "Game.h"

Game::Game(int id, string name){
    gameID = id;
    gameName = name;
}

int Game::getID() { return gameID; }

string Game::getName() { return gameName; }

void Game::addVictory(Victory* v) {
    victories[v->victoryID] = v;
}

Victory* Game::getVictory(int id) { return victories[id]; }

void Game::addPlayerToPlayedBy(int id) {
    playedBy.push_back(id);
}
