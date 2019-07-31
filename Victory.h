#ifndef VICTORY_H
#define VICTORY_H

#include <string>
#include <vector>

using namespace std;

struct Victory {
    Victory(int gid, int vid, string vname, int vpoints, int timesAchieved=0) :
        gameID(gid), victoryID(vid), victoryName(vname), victoryPoints(vpoints) {}

    int timesAchieved;
    int gameID;
    int victoryID;
    string victoryName;
    int victoryPoints;
    vector<int> playersAchieved;
};

#endif
