#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Node.h"
#include "hash.h"
#include "Info.h"
using namespace std;


Node::Node(){
    type = -1;
}
Node::Node(Info info, int key){ // key = 0,1,2 -> 0 = player, 1 = team, 2 = year
    data = info;
    type = key;
}
Node::Node(const Node& other){
    data = other.data;
    type = other.type;
    team = other.team;
    player = other.player;
}

string Node::getName()
{
    return data.getName();
}
Info& Node::getInfo()
{
    return data;
}
int Node::getType()
{
    return type;
}
vector<Info>& Node::getTeamVec()
{
    return team;
}
vector<Info>& Node::getPlayerVec()
{
    return player;
}