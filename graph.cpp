#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <string.h>
#include <queue>
#include <bits/stdc++.h>
using namespace std;
#include "Node.h"
#include "hash.h"
#include "Info.h"

void addTeamEdge(Hash& hashtable, Info obj1, Info obj2){
  hashtable.searchHash(obj1.getName())->addTeam(obj2);
  hashtable.searchHash(obj2.getName())->addTeam(obj1);
}
void addYearEdge(Hash& hashtable, Info obj1, Info obj2){
  hashtable.searchHash(obj1.getName())->addPlayer(obj2);
  hashtable.searchHash(obj2.getName())->addTeam(obj1);
}
bool findTeamAdj(Hash& hashtable, Info obj1, Info obj2){
  return hashtable.searchHash(obj1.getName())->findTeam(obj2);
}



void ReadFile(string fileName, Hash& hashtable){
  string line;
  ifstream myfile (fileName);
  vector<string> fileLines;
  if (myfile.is_open()){
    while(getline(myfile,line)){
      fileLines.push_back(line);
    }
    myfile.close();
  }
  else{
    cout << "Could not open file " << fileName << endl;
    return;
  }
  string temp ="";
  //fileLines is vector of input file lines, now sort it.
  for(int i = 0; i < fileLines.size(); ++i){ //here is the slow af sort xD
    for(int j = i+1; j < fileLines.size(); ++j){
      if(fileLines.at(i) > fileLines.at(j)){
        temp = fileLines.at(i);
        fileLines.at(i) = fileLines.at(j);
        fileLines.at(j) = temp;
      }
    }
  }

  vector<string> allYearNodes;
  int index = 0;
  for(int i = 0; i < fileLines.size(); i++){
    string word;
    istringstream ss(fileLines.at(i));
    Info arr[3];
    int type_counter = 0;
    while(getline(ss, word, ',')){
      int type = type_counter%3;
      type_counter++;
      if(type == 2)
        word = arr[1].getName() + "_" + word;
      Node* exist = hashtable.searchHash(word);
      
      if(exist == nullptr){
        Info info(word, index);
        hashtable.insertItem(Node(info, type));
        arr[type] = info;
        index++;
      }
      else
        arr[type] = exist->getInfo();
    }
    if(!findTeamAdj(hashtable, arr[1], arr[2]))
      addTeamEdge(hashtable, arr[1], arr[2]);
    if(!findTeamAdj(hashtable, arr[0], arr[2]))
      addYearEdge(hashtable, arr[2], arr[0]);
    allYearNodes.push_back(arr[2].getName());
  }
  hashtable.addEdge(allYearNodes);
}

void ListPlayedTeam(Hash& hashtable, string player){
  Node* adj = hashtable.searchHash(player);
  if(adj != NULL){
    for(int i = 0; i < adj->getTeamSize(); i++){
      Info Team = adj->getTeamAt(i);
      string TeamName = Team.getName().substr(0, Team.getName().find('_'));
      string Year = Team.getName().substr(Team.getName().find('_')+1);
      cout << player << " played for the " <<Year <<" " << TeamName  <<endl;
    }
  }
  else
    cout << player <<" does not appear in the input file" << endl;
}

void ListPlayedYear(Hash& hashtable, string player, string team){
  Node* adj = hashtable.searchHash(player);
  Node* findTeam = hashtable.searchHash(team);
  if(findTeam == NULL){
    cout << "Team " << team << " was not found" << endl;
    return;
  }
  Info Team;
  bool played = false;
  if(adj != NULL){
    for(int i = 0; i < adj->getTeamSize(); i++){
      Team = adj->getTeamAt(i);
      if(!team.compare(Team.getName().substr(0, Team.getName().find('_')))){
        played = true;
        string TeamName = Team.getName().substr(0, adj->getTeamAt(i).getName().find('_'));
        string Year = Team.getName().substr(Team.getName().find('_')+1);
        cout << player << " played for " << TeamName << " in "<< Year <<endl;
      }
    }
    if(!played){
      cout << player << " has never played for the " << team << endl;
    }
  }
  else
    cout << player <<" does not appear in the input file" << endl;

}

void ListPlayer(Hash& hashtable, string team){
  struct player{
    string name;
    int count;
  };
  vector<player> list;
  Node* teamNode = hashtable.searchHash(team);
  Info year;
  if(teamNode != NULL){
    for(int i = 0; i < teamNode->getTeamSize(); i++){
      year = teamNode->getTeamAt(i);
      Node* adjPlayers = hashtable.searchHash(year.getName());
      Info person;
      for(int i = 0; i < adjPlayers->getPlayerSize(); i++){
        string playerName = adjPlayers->getPlayerAt(i).getName();
        if(list.empty()){
          list.push_back(player{playerName, 1});
        }
        else if(list.back().name != playerName){
          int index = -1;
          for(int j = 0; j < list.size(); j++)
            if(!(list.at(j).name).compare(playerName))
              index = j;
          if(index != -1)
            list.at(index).count++;
          else
            list.push_back(player{playerName, 1}); 
        }
        else{
          list.back().count++;
        }
      }
    }
    // sort the list by x.count
    player temp;
    //fileLines is vector of input file lines, now sort it.
    for(int i = 0; i < list.size(); ++i){ //here is the slow af sort xD
      for(int j = i+1; j < list.size(); ++j){
        if(list.at(i).count < list.at(j).count){
          temp = list.at(i);
          list.at(i) = list.at(j);
          list.at(j) = temp;
        }
      }
    }
    int prev = -1;
    int start = -1;
    int end = -1;
    for(int i = 0; i < list.size(); i++){
      if(prev == -1){
        prev = list.at(i).count;
        start = i;
      }
      //cout << !(list.back().name.compare(list.at(i).name)) << " " << (prev != list.at(i).count) << endl;
      if(!(list.back().name.compare(list.at(i).name)) || prev != list.at(i).count){
        prev = list.at(i).count;
        end = i;
        if(!(list.back().name.compare(list.at(i).name))){
          end = i+1;
        }
        player temp;
        for(int a = start; a < end; a++){ //here is the slow af sort xD
          for(int b = a+1; b < end; b++){
            if(list.at(a).name > list.at(b).name){
              temp = list.at(a);
              list.at(a) = list.at(b);
              list.at(b) = temp;
            }
          }
        }
        start = i;
      }
    }
    for(player x : list){
      cout << x.name << " played " << x.count << " years for the " << team << endl;
    }
  }
}


bool ShortestPath(Hash& hashtable, string playerA, string playerB, int v, vector<Info>& pred, vector<int>& dist){
  vector<bool> visited;
  visited.resize(v, false);
  dist.resize(v, INT_MAX);
  pred.resize(v, Info());
  
  vector<Node> queue;
  Node* srcNodeptr = hashtable.searchHash(playerA);
  Node* destNodeptr = hashtable.searchHash(playerB);
  Node srcNode;
  Node destNode;
  int srcIdx = 0;
  int destIdx = 0;
  if(srcNodeptr != NULL && destNodeptr != NULL){
    srcIdx = srcNodeptr->getInfo().getIndex();
    srcNode = *srcNodeptr;
    destIdx = destNodeptr->getInfo().getIndex();
    destNode = *destNodeptr;
  }
  else 
    return false;

  visited.at(srcIdx) = true;
  dist.at(srcIdx) = 0;
  queue.push_back(srcNode);

  while(!queue.empty()){
    Node current = queue.front();
    queue.erase(queue.begin());
    for(int i = 0; i < current.getPlayerSize(); i++){
      int playerIdx = current.getPlayerAt(i).getIndex();
      if(visited.at(playerIdx) == false){
        visited.at(playerIdx) = true;
        dist.at(playerIdx) = dist.at(current.getInfo().getIndex()) + 1;
        pred.at(playerIdx) = current.getInfo();
        queue.push_back( *(hashtable.searchHash(current.getPlayerAt(i).getName())));
        if(playerIdx == destIdx){
          return true;
        }
      }
    }
  }
  
  return false;
}

bool sameTeam(Node playerNode, string teamName){
  for(Info yearInfo : playerNode.getTeamVec()){
    if(!(teamName.compare(yearInfo.getName().substr(0, yearInfo.getName().find('_'))))){
      return true;
    }
  }
  return false;
}

bool ShortestPathWithTeam(Hash& hashtable, string playerA, string playerB, string team, int v, vector<Info>& pred, vector<int>& dist){
  
  vector<bool> visited;
  visited.resize(v, false);
  dist.resize(v, INT_MAX);
  pred.resize(v, Info());
  
  vector<Node> queue;
  Node* srcNodeptr = hashtable.searchHash(playerA);
  Node* destNodeptr = hashtable.searchHash(playerB);
  Node srcNode;
  Node destNode;
  int srcIdx = 0;
  int destIdx = 0;
  if(srcNodeptr != NULL && destNodeptr != NULL){
    srcIdx = srcNodeptr->getInfo().getIndex();
    srcNode = *srcNodeptr;
    destIdx = destNodeptr->getInfo().getIndex();
    destNode = *destNodeptr;
    if((!sameTeam(srcNode, team)) || (!sameTeam(destNode, team))){
      cout << "Error: Players are not all in "<< team << endl;
      return false;
    }
  }
  else 
    return false;

  visited.at(srcIdx) = true;
  dist.at(srcIdx) = 0;
  queue.push_back(srcNode);

  while(!queue.empty()){
    Node current = queue.front();
    queue.erase(queue.begin());
    for(int i = 0; i < current.getPlayerSize(); i++){
      int playerIdx = current.getPlayerAt(i).getIndex();
      if(visited.at(playerIdx) == false){
        visited.at(playerIdx) = true;
        dist.at(playerIdx) = dist.at(current.getInfo().getIndex()) + 1;
        pred.at(playerIdx) = current.getInfo();
        //check adj for team
        Node adjPlayer = *(hashtable.searchHash(current.getPlayerAt(i).getName()));
        if(sameTeam(adjPlayer, team)){
          queue.push_back(adjPlayer);
        }
        if(playerIdx == destIdx){
          return true;
        }
      }
    }
  }
  
  return false;
}

Info findAdjYear(Hash& hashtable, string playerA, string playerB){
  vector<Info> A = hashtable.searchHash(playerA)->getTeamVec();
  vector<Info> B = hashtable.searchHash(playerB)->getTeamVec();
  for(int i = 0; i < A.size(); i ++){
    for(int j = 0; j < B.size(); j++){
      if(!(A.at(i).getName().compare(B.at(j).getName()))){
        return A.at(i);
      }
    }
  }
  return Info();
}
void printSD(Hash& hashtable, string playerA, string playerB, int v, vector<Info>& pred, vector<int>& dist){
  vector<Info> path;
  Info crawl = hashtable.searchHash(playerB)->getInfo();
  path.push_back(crawl);
  while(pred.at(crawl.getIndex()).getIndex() != -1){
    path.push_back(pred.at(crawl.getIndex()));
    crawl = pred.at(crawl.getIndex());
  }

  cout << playerB << "'s " << playerA << " number is "<< dist.at(hashtable.searchHash(playerB)->getInfo().getIndex()) << endl;
  
  for(int i = path.size()-1; i >= 1; i--){
    Info Year = findAdjYear(hashtable, path.at(i).getName(), path.at(i-1).getName());
    string TeamName = Year.getName().substr(0, Year.getName().find('_'));
    string currYear = Year.getName().substr(Year.getName().find('_')+1);
    cout << path.at(i).getName() << " played with " << path.at(i-1).getName() << " on the " << currYear << " " << TeamName <<  endl;
  }
  cout << endl;
}



int main (int argc, char *argv[]){
  string inputfile;
  string player1Name;
  string player2Name;
  string teamName;

  int c = 0;

  while((c = getopt(argc, argv, "i:s:d:t:")) != -1){

      switch(c){
          case 'i':
            inputfile = optarg;
            break;
          case 's':
            player1Name = optarg;
            break;
          case 'd':
            player2Name = optarg;
            break;
          case 't':
            teamName = optarg;
            break;
          default:
              break;
      }
  }
  
  int V = 2500;
  Hash hashtable(V);
  ReadFile(inputfile, hashtable);
  //case 0a
  if(inputfile.empty()){
    cout << "Case0a:" << endl;
    cout << "No input file provided " << endl;
    return -1;
  }
  //case 0b
  else if( (!player2Name.empty()) && (player1Name.empty())){
    cout << "Case0b:" << endl;
    cout << "Please provide a player 1 name " << endl;
    return -1;
  }
  //case 1
  else if((!inputfile.empty()) && (player1Name.empty()) && (player2Name.empty()) && (teamName.empty())){
    string line;
    ifstream myfile (inputfile);
    if(myfile.is_open()){
      while(getline(myfile,line)){
        cout << line << endl;
      }
      myfile.close();
    }
    else{
      cout << "Could not open file " << inputfile << endl;
    }
  }
  else if((!inputfile.empty()) && (!player1Name.empty()) && (player2Name.empty()) && (teamName.empty())){
    cout << "Case2a:" << endl;
    ListPlayedTeam(hashtable, player1Name);
    cout << endl;
  }
  else if((!inputfile.empty()) && (!player1Name.empty()) && (player2Name.empty()) && (!teamName.empty())){
    cout << "Case2b:" << endl;
    ListPlayedYear(hashtable, player1Name, teamName);
    cout << endl;
  }
  else if((!inputfile.empty()) && (player1Name.empty()) && (player2Name.empty()) && (!teamName.empty())){
    cout << "Case3:" <<  endl;
    ListPlayer(hashtable, teamName);
    cout << endl;
  }
  
  else if( (!inputfile.empty()) && (!player1Name.empty()) && (!player2Name.empty()) && (teamName.empty())) {
    cout << "Case 4a:" << endl;
    int v = hashtable.getSize();
    vector<Info> pred;
    vector<int> dist;
    string A = player1Name;
    string B = player2Name;
    bool foundPath = ShortestPath(hashtable, A, B, v, pred, dist);
    if(foundPath){
      printSD(hashtable, A, B, v, pred, dist);
    }
    else
    {
      cout << "No teammate path exists between " << player1Name << " and " << player2Name  << endl;
    }
  }
  else if( (!inputfile.empty()) && (!player1Name.empty()) && (!player2Name.empty()) && (!teamName.empty())){
    cout << "Case 4b:" << endl;
    vector<Info> pred;
    vector<int> dist;
    int v = hashtable.getSize();
    string A = player1Name;
    string B = player2Name;
    bool foundPath = ShortestPathWithTeam(hashtable, A, B, teamName, v, pred, dist);
    if(foundPath){
      printSD(hashtable, A, B, v, pred, dist);
    }
    else{
      cout << "No teammate path exists between " << player1Name << " and " << player2Name  << endl;
    }
  }
}