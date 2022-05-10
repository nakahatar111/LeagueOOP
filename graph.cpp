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


  int index = 0;
  for(int i = 0; i < fileLines.size(); i++){
    cout << fileLines.at(i) << endl;
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
  }
  hashtable.addEdge();
}

void ListPlayedTeam(Hash& hashtable, string player){
  Node* adj = hashtable.searchHash(player);
  if(adj != NULL){
    for(int i = 0; i < adj->getTeamSize(); i++){
      Info Team = adj->getTeamAt(i);
      string TeamName = Team.getName().substr(0, Team.getName().find('_'));
      string Year = Team.getName().substr(Team.getName().find('_')+1);
      cout << player << " player for " << TeamName << " in "<< Year <<endl;
    }
  }
  else
    cout << "Player "<< player <<" not found" << endl;
}

void ListPlayedYear(Hash& hashtable, string player, string team){
  Node* adj = hashtable.searchHash(player);
  Info Team;
  if(adj != NULL){
    for(int i = 0; i < adj->getTeamSize(); i++){
      Team = adj->getTeamAt(i);
      if(!team.compare(Team.getName().substr(0, Team.getName().find('_')))){
        string TeamName = Team.getName().substr(0, adj->getTeamAt(i).getName().find('_'));
        string Year = Team.getName().substr(Team.getName().find('_')+1);
        cout << player << " player for " << TeamName << " in "<< Year <<endl;
      }
    }
  }
  else
    cout << "Player "<< player <<" not found" << endl;
}

void ListPlayer(Hash& hashtable, string team){
  struct player{
    string name;
    int count;
  };
  vector<player> list;
  Node* adjYears = hashtable.searchHash(team);
  Info year;
  if(adjYears != NULL){
    for(int i = 0; i < adjYears->getTeamSize(); i++){
      year = adjYears->getTeamAt(i);
      Node* adjPlayers = hashtable.searchHash(year.getName());
      Info person;
      for(int i = 0; i < adjPlayers->getPlayerSize(); i++){
        string playerName = adjPlayers->getPlayerAt(i).getName();
        if(list.empty() || list.back().name != playerName){
          list.push_back(player{playerName, 1});
        }
        else{
          list.back().count++;
        }
      }
    }
    // sort the list by x.count
    for(player x : list){
      cout << x.name << " played " << x.count << " year in " << team << endl;
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

void printSD(Hash& hashtable, string playerA, string playerB, int v, vector<Info>& pred, vector<int>& dist){
  vector<Info> path;
  Info crawl = hashtable.searchHash(playerB)->getInfo();
  path.push_back(crawl);
  while(pred.at(crawl.getIndex()).getIndex() != -1){
    path.push_back(pred.at(crawl.getIndex()));
    crawl = pred.at(crawl.getIndex());
  }

  cout << "Shortest Path Dist is " << dist.at(hashtable.searchHash(playerB)->getInfo().getIndex()) << endl;

  cout << "Path is: "<< endl;
  for(int i = path.size()-1; i >= 0; i--){
    cout << path.at(i).getName() << " -> ";
  }
      cout << endl;
}



int main (int argc, char *argv[]){
//     string inputfile;

//     int c = 0;

//     while((c = getopt(argc, argv, "i:s:d:t: ")) != -1){

//         switch(c){
//             case 'i':
//               inputfile = optarg;
//               break;

//             case 's':
//               break;
//             case 'd':
//               break;
//             case 't':
//               break;
//             default:
//                 break;
//             }
//     }
  int V = 64;
  Hash hashtable(V);
  // if(inputfile.empty()){
  //   return -1;
  // }
  string file = "input.txt";
  ReadFile(file, hashtable);
  hashtable.displayHash();
  hashtable.displayAdj();
  //case 2a
  cout << "Case2a:" << endl;
  ListPlayedTeam(hashtable, "Mike Lewis");
  cout << endl;
  ListPlayedTeam(hashtable, "Mike Leswis");
  cout << endl;
  ListPlayedTeam(hashtable, "Yu Sun");
  cout << endl;
  cout << "Case2b:" << endl;
  ListPlayedYear(hashtable, "Yu Sun", "LA Lakers");
  cout << endl;
  cout << "Case3:" << endl;
  ListPlayer(hashtable, "LA Lakers");
  cout << endl;
  cout << "Case4a:" << endl;
  int v = hashtable.getSize();
  vector<Info> pred;
  vector<int> dist;
  string A = "Mike Lewis";
  string B = "Callisto Hess";
  bool foundPath = ShortestPath(hashtable, A, B, v, pred, dist);
  if(foundPath){
    cout << "pred " << endl << endl;
    for(Info x : pred){
      cout << "index and name: " << x.getIndex() << " " << x.getName() << endl;
    }
    cout << "dist " << endl << endl;

    for(int x : dist){
      cout << "index: " << x << endl;
    }
    printSD(hashtable, A, B, v, pred, dist);
  }
  else
  {
    cout << "No worky" << endl;
  }

}