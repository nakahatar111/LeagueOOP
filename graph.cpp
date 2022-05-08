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
//Info stores the name and Index
//Node stores Info and whether the Node is a Player, Team, Year
  // Additionally, Node stores two vectors, Adj Players and Adj Team/Year
void addTeamEdge(Hash& hashtable, string obj1, string obj2){ //when adding edges, we got to index of obj1, and append obj2 to the Team Vector of string
  hashtable.searchHash(obj1)->addTeam(obj2);
  hashtable.searchHash(obj2)->addTeam(obj1);
}
void addYearEdge(Hash& hashtable, string obj1, string obj2){//when adding edges, we got to index of obj1, and append obj2 to the Player Vector of string
  hashtable.searchHash(obj1)->addPlayer(obj2);
  hashtable.searchHash(obj2)->addTeam(obj1);
}
bool findTeamAdj(Hash& hashtable, string obj1, string obj2){
  return hashtable.searchHash(obj1)->findTeam(obj2);
}

void ReadFile(string fileName, Hash& hashtable){
  string line;
  ifstream myfile (fileName);
  if (myfile.is_open()){
    int index = 0;
    while(getline(myfile,line)){
      string word;
      istringstream ss(line);
      string arr[3];
      int type_counter = 0;
      while(getline(ss, word, ',')){
        int type = type_counter%3;
        type_counter++;
        if(type == 2)
          word = arr[1] + "_" + word;

        //finding if it exists
        Node* exist = hashtable.searchHash(word);
        
        if(exist == nullptr){
          hashtable.insertItem(Node(word, type));
          arr[type] = word;
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
    myfile.close();
  }
  else
    cout << "Could not open file " << fileName << endl;
}

void ListPlayedTeam(Hash& hashtable, string player){
  // Case 2a (Player1, , ) -> print Player1's list of teams, sorted by year
  Node* adj = hashtable.searchHash(player);
  if(adj != NULL){
    for(int i = 0; i < adj->getTeamSize(); i++){
      string Team = adj->getTeamAt(i);
      string TeamName = Team.substr(0, Team.find('_'));
      string Year = Team.substr(Team.find('_')+1);
      cout << player << " player for " << TeamName << " in "<< Year <<endl;
    }
  }
  else
    cout << "Player "<< player <<" not found" << endl;
}

void ListPlayedYear(Hash& hashtable, string player, string team){
  Node* adj = hashtable.searchHash(player);
  string Team = "";
  if(adj != NULL){
    for(int i = 0; i < adj->getTeamSize(); i++){
      Team = adj->getTeamAt(i);
      if(!team.compare(Team.substr(0, Team.find('_')))){
        string TeamName = adj->getTeamAt(i).substr(0, adj->getTeamAt(i).find('_'));
        string Year = Team.substr(Team.find('_')+1);
        cout << player << " player for " << TeamName << " in "<< Year <<endl;
      }
    }
  }
  else
    cout << "Player "<< player <<" not found" << endl;
}
  // Case 3 ( , , Team) -> print all players who played on Team
  // Get index of Team in array
  // Go to Team Node
  // Do Node.getTeamVec() to get the Years the team played
  // For each Year,
  //   go to Year Node in array
  //   Do Node.getPlayerVec() to get Players under that year
  //   Print
void ListPlayer(Hash& hashtable, string team){
  Node* adjYears = hashtable.searchHash(team);
  string year = "";
  if(adjYears != NULL){
    for(int i = 0; i < adjYears->getTeamSize(); i++){
      year = adjYears->getTeamAt(i);
      Node* adjPlayers = hashtable.searchHash(year);
      string player = "";
      for(int i = 0; i < adjPlayers->getPlayerSize(); i++){
        player = adjPlayers->getPlayerAt(i);
        string TeamName = year.substr(0, year.find('_'));
        string yearPlayed = year.substr(year.find('_')+1);
        cout << player << " played on "<< TeamName << " in " << yearPlayed << endl;
      }
    }
  }
}

void ShortestPath(Hash& hashtable, string playerA, string playerB){
  cout << "this is no where near BFS lolol" << endl;
  cout << "Finding Shortest Path from " << playerA << " to " << playerB << "..."<< endl << endl;
  queue<string> queue;
  queue.push(playerA);
  while(!queue.empty()){
    string path = queue.front();
    queue.pop();
    cout << path << "->";
    if(!path.compare(playerB)){
      cout << "found"<< endl;
      return;
    }
    Node* currentNode = hashtable.searchHash(path);
    for(int i = 0; i < currentNode->getPlayerSize(); i++){
      queue.push(currentNode->getPlayerAt(i));
    }
  }



}
int main (int argc, char *argv[]){
  //Initalize adjacency list of Nodes
  //-> Adjaceny List will be a vector of Nodes
  //--> Nodes will have two vectors (Player adj Vector and Team adj Vector) + any Info needed

  //testing if hash works
  int V = 64;
  Hash hashtable(V);

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
  ShortestPath(hashtable, "Mike Lewis", "Yu Sun");
  //cout << "Case4b:" << endl;
  
}

/*
What we need to do::

Case 1 (File) -> read inputfile
  Given input fileName, make function called ReadFile(fileName, vector<Node> adj)
  int index = 0; **for index to be stored inside Node (reason -> refer to line 104/105)
  For each line of inputFile:
    Parse into: Name, Team, Year **as strings
    if(Name/Team/Year does not exist)
      Make Info(string Name/Team/Year, index);
      index++
      adj.push_back(Info) add Nodes to adj list x3 for Name/Team/Year
    if(Name/Team/Year does exist)
      find it inside adj list to get its index (Reason: need to add edges so we need to find ALL THREE NODES)
    addTeamEdge() -> add edges between these Name/Team/Year
  After "Black edges" are fully made, we make the "Red edges"
  For Every Year Node (Type = 2), connect all Players together inside its Player Vector (Refer to line 147)



Case 2a (Player1, , ) -> print Player1's list of teams, sorted by year
  Get index of Player1 in array
  Go to Player1 Node
  Do Node.getTeamVec() to get teams/years of player
  print

Case 2b (Player1, , Team) -> print when PLayer1 played on Team
  Get index of Player1 in array
  Go to Player1 Node
  Do Node.getTeamVec() to get teams/years of player
  Within the vector of teams, if teamName == Team, print

Case 3 ( , , Team) -> print all players who played on Team
  Get index of Team in array
  Go to Team Node
  Do Node.getTeamVec() to get the Years the team played
  For each Year,
    go to Year Node in array
    Do Node.getPlayerVec() to get Players under that year
    Print

Case 4a (Player1, Player2, ) -> Shortest Path from Player1 to Player2
  Simple BFS on Player Vector of the Nodes (.getPlayerVec())***keeps track of the path
  print path

*/






  /*
  //Info holds name and index when its inside the vector
  //-> Reason for index: Once you go thru adj node, U want to jump to where that adj node is in the adjacency list vector
  //-> Visually, u want to go from the horizontal vector to the vertical vector. To jump to the right spot, U need to know its index
  //--> Whats inside the adjacency list is NOT node obj, it is Info obj
  Info LA("LA", 0);
  Info BC("BC",1); 
  Info MB("MB",2); 
  Info BC2022("2022",3);
  Info BC2021("2021",4);
  Info BC2020("2020",5);
  Info LA2019("2019",6);
  Info LA2018("2018",7);
  Info LA2017("2017",8);
  Info MB2016("2016",9);
  Info Mike("Mike",10); 
  Info Tim("Tim",11); 
  Info Katie("Katie",12);
  Info Callisto("Callisto",13);
  Info Yu("Yu",14);
  Info Necati("Necati",15);

  //Create Nodes from the Info and the type of info
  //-> 0: Player Node, 1: Team Node, 2: Year Node
  //--> Reason why we need "type" -> when traversing through the adj list, and lets say we are looping for all the players,
  //--> we can simply identify which nodes are Player Node by the "Type"
  //--> Or else, we will traverse thru ALL Team, Year, AND Player Nodes
  adj.push_back(Node(LA,1));
  adj.push_back(Node(BC,1));
  adj.push_back(Node(MB,1));
  adj.push_back(Node(BC2022,2));
  adj.push_back(Node(BC2021,2));
  adj.push_back(Node(BC2020,2));
  adj.push_back(Node(LA2019,2));
  adj.push_back(Node(LA2018,2));
  adj.push_back(Node(LA2017,2));
  adj.push_back(Node(MB2016,2));
  adj.push_back(Node(Mike,0));
  adj.push_back(Node(Tim,0));
  adj.push_back(Node(Katie,0));
  adj.push_back(Node(Callisto,0));
  adj.push_back(Node(Yu,0));
  adj.push_back(Node(Necati,0));

  //Setting up Team adjacency with Year
  addTeamEdge(adj, BC, BC2022);
  addTeamEdge(adj, BC, BC2021);
  addTeamEdge(adj, BC, BC2020);
  addTeamEdge(adj, LA, LA2019);
  addTeamEdge(adj, LA, LA2018);
  addTeamEdge(adj, LA, LA2017);
  addTeamEdge(adj, MB, MB2016);
  //Setting up Year adjacency with Player
  addTeamEdge(adj, BC2022, Mike);
  addTeamEdge(adj, BC2021, Mike);
  addTeamEdge(adj, BC2020, Mike);
  addTeamEdge(adj, LA2019, Tim);
  addTeamEdge(adj, LA2019, Katie);
  addTeamEdge(adj, LA2018, Katie);
  addTeamEdge(adj, LA2018, Katie);
  addTeamEdge(adj, LA2017, Katie);
  addTeamEdge(adj, LA2017, Callisto);
  addTeamEdge(adj, LA2017, Yu);
  addTeamEdge(adj, MB2016, Yu);
  addTeamEdge(adj, MB2016, Necati);

  //Once all "Black Edges" are connected properly, we now connect the "Red Edges"
  //Set an algorithm that looks at ALL Year Nodes (type = 2), 
  //And connect all adjacenty Players to each other
  //--> Result of this: All players that played in the same team/same year will be "connected" by a red Edge.
  //--> Distinguish "Red Edges" with addPlayerEdge. -> this appends adjacency into a different vector (**Look at Node class (private:))
  addPlayerEdge(adj, Mike, Tim);
  addPlayerEdge(adj, Tim, Katie);
  addPlayerEdge(adj, Katie, Callisto);
  addPlayerEdge(adj, Katie, Yu);
  addPlayerEdge(adj, Yu, Necati);
  printGraph(adj);
  */