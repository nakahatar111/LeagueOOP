#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Node.h"
#include "hash.h"
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

Node::string getName()
{
    return data.getName();
}
Node::int getIndex()
{
    return data.getIndex();
}
Node::Info& getInfo()
{
    return data;
}
Node::int getType()
{
    return type;
}
Node::vector<Info>& getTeamVec()
{
    return team;
}
Node::vector<Info>& getPlayerVec()
{
    return player;
}