#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Node.h"
#include "hash.h"
using namespace std;


Node::Node(){
    info = Info();
    type = -1;
}
Node::Node(Info data, int key){ // key = 0,1,2 -> 0 = player, 1 = team, 2 = year
    info = data;
    type = key;
}
Node::Node(const Node& other){
    info = other.info;
    type = other.type;
    team = other.team;
    player = other.player;
}
Info Node::getInfo()
{
    return info;
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
void Node::addTeam(Info data){
    team.push_back(data);
}
void Node::addPlayer(Info data){
    player.push_back(data);
}
int Node::getPlayerSize(){
    return player.size();
}
Info Node::getPlayerAt(int i){
    return player.at(i);
}
int Node::getTeamSize(){
    return team.size();
}
Info Node::getTeamAt(int i){
    return team.at(i);
}
bool Node::findTeam(Info data){
  for(int i = 0; i < team.size(); i++)
    if(!team.at(i).getName().compare(data.getName()))
      return true;
  return false;
}