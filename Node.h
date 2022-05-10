#ifndef _NODE_H_
#define _NODE_H_

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "Info.h"

using namespace std;
class Node{
  public:
    Node();
    Node(Info info, int key); // key = 0,1,2 -> 0 = player, 1 = team, 2 = year
    Node(const Node& other);
    Info getInfo();
    int getType();
    vector<Info>& getTeamVec();
    vector<Info>& getPlayerVec();
    bool findTeam(Info data);
    void addTeam(Info data);
    void addPlayer(Info data);
    Info getPlayerAt(int i);
    Info getTeamAt(int i);
    int getPlayerSize();
    int getTeamSize();
  private:
    int type = -1;
    Info info;
    vector<Info> team;
    vector<Info> player;
};
#endif