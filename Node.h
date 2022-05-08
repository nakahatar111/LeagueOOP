#ifndef _NODE_H_
#define _NODE_H_

#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;
class Node{
  public:
    Node();
    Node(string info, int key); // key = 0,1,2 -> 0 = player, 1 = team, 2 = year
    Node(const Node& other);
    string getInfo();
    int getType();
    vector<string>& getTeamVec();
    vector<string>& getPlayerVec();
    bool findTeam(string data);
    void addTeam(string data);
    void addPlayer(string data);
    string getPlayerAt(int i);
    string getTeamAt(int i);
    int getPlayerSize();
    int getTeamSize();
  private:
    int type = -1;
    string info = "";
    vector<string> team;
    vector<string> player;
};
#endif