#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
using namespace std;

class Node{
  public:
    Node(){
      name = "";
    }
    Node(string str){
      name = str;
    }
    string getName(){return name;}
    vector<string>& getTeamVec(){return team;}
    vector<string>& getPlayerVec(){return player;}

  private:
    string name = "";
    vector<string> team;
    vector<string> player;
};

void addTeamEdge(Node adj[], int index1, string obj1, int index2, string obj2)
{
    adj[index1].getTeamVec().push_back(obj2);
    //adj[index2].getTeamVec().push_back(obj1);
}

void addPlayerEdge(Node adj[], int index1, string obj1, int index2, string obj2)
{
    adj[index1].getPlayerVec().push_back(obj2);
    adj[index2].getPlayerVec().push_back(obj1);
}

void printGraph(Node adj[], int V)
{
    for (int v = 0; v < V; ++v) {
        cout << endl << " Adjacency list of vertex " << v << endl;
        cout << "Team/Year  " << adj[v].getName();
        for (string x : adj[v].getTeamVec())
            cout << "-> " << x;
        cout << endl << "Player     " << adj[v].getName();;
        for (string x : adj[v].getPlayerVec())
            cout << "-> " << x;
        printf("\n");
    }
}
 
int main (int argc, char *argv[]){
  //make these hold indexes/ids
  string LA = "LA"; //0 --> struct that stores index and name
  string BC = "BC"; //1
  string MB = "MB"; //2
  string BC2022 = "2022"; //3
  string BC2021 = "2021"; //4
  string BC2020 = "2020"; //5
  string LA2019 = "2019"; //6
  string LA2018 = "2018"; //7
  string LA2017 = "2017"; //8
  string MB2016 = "2016"; //9
  string Mike = "Mike"; //10
  string Tim = "Tim"; //11
  string Katie = "Katie"; //12
  string Callisto = "Callisto"; //13
  string Yu = "Yu"; //14
  string Necati = "Necati"; //15

  int V = 16;
  Node adj[V];
  adj[0] = Node(LA);
  adj[1] = Node(BC);
  adj[2] = Node(MB);
  adj[3] = Node(BC2022);
  adj[4] = Node(BC2021);
  adj[5] = Node(BC2020);
  adj[6] = Node(LA2019);
  adj[7] = Node(LA2018);
  adj[8] = Node(LA2017);
  adj[9] = Node(MB2016);
  adj[10] = Node(Mike);
  adj[11] = Node(Tim);
  adj[12] = Node(Katie);
  adj[13] = Node(Callisto);
  adj[14] = Node(Yu);
  adj[15] = Node(Necati);

  //connecting Teams to its Year
  addTeamEdge(adj, 1, BC, 3, BC2022);
  addTeamEdge(adj, 1, BC, 4, BC2021);
  addTeamEdge(adj, 1, BC, 5, BC2020);
  addTeamEdge(adj, 0, LA, 6, LA2019);
  addTeamEdge(adj, 0, LA, 7, LA2018);
  addTeamEdge(adj, 0, LA, 8, LA2017);
  addTeamEdge(adj, 2, MB, 9, MB2016);
  //connecting Years to its Team members
  addTeamEdge(adj, 3, BC2022, 10, Mike);
  addTeamEdge(adj, 4, BC2021, 10, Mike);
  addTeamEdge(adj, 5, BC2020, 10, Mike);
  addTeamEdge(adj, 6, LA2019, 11, Tim);
  addTeamEdge(adj, 6, LA2019, 12, Katie);
  addTeamEdge(adj, 7, LA2018, 12, Katie);
  addTeamEdge(adj, 7, LA2018, 12, Katie);
  addTeamEdge(adj, 8, LA2017, 12, Katie);
  addTeamEdge(adj, 8, LA2017, 13, Callisto);
  addTeamEdge(adj, 8, LA2017, 14, Yu);
  addTeamEdge(adj, 9, MB2016, 14, Yu);
  addTeamEdge(adj, 9, MB2016, 15, Necati);
  
  //connecting Teammates to Teammates
  //condition: Connect if they are in the same team on the same year
  addPlayerEdge(adj, 10, Mike, 11, Tim);
  addPlayerEdge(adj, 11, Tim, 12, Katie);
  addPlayerEdge(adj, 12, Katie, 13, Callisto);
  addPlayerEdge(adj, 12, Katie, 14, Yu);
  addPlayerEdge(adj, 14, Yu, 15, Necati);
  printGraph(adj, V);

}

/*
Case 1 (File) -> read inputfile

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