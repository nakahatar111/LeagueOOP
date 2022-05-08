#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Node.h"
#include "hash.h"
using namespace std;


Node::Node(){
    info = "";
    type = -1;
}
Node::Node(string data, int key){ // key = 0,1,2 -> 0 = player, 1 = team, 2 = year
    info = data;
    type = key;
}
Node::Node(const Node& other){
    info = other.info;
    type = other.type;
    team = other.team;
    player = other.player;
}
string Node::getInfo()
{
    return info;
}
int Node::getType()
{
    return type;
}
vector<string>& Node::getTeamVec()
{
    return team;
}
vector<string>& Node::getPlayerVec()
{
    return player;
}
void Node::addTeam(string data){
    team.push_back(data);
}
void Node::addPlayer(string data){
    player.push_back(data);
}
int Node::getPlayerSize(){
    return player.size();
}
string Node::getPlayerAt(int i){
    return player.at(i);
}
int Node::getTeamSize(){
    return team.size();
}
string Node::getTeamAt(int i){
    return team.at(i);
}
bool Node::findTeam(string data){
  for(int i = 0; i < team.size(); i++)
    if(!team.at(i).compare(data))
      return true;
  return false;
}