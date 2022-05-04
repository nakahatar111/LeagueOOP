#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <string.h>
using namespace std;
//Info stores the name and Index
//Node stores Info and whether the Node is a Player, Team, Year
  // Additionally, Node stores two vectors, Adj Players and Adj Team/Year

class Info{
  public:
    Info(){
      name = "";
      index = -1;
    }
    Info(string str, int idx){
      name = str;
      index = idx;
    }
    string getName(){return name;}
    int getIndex(){return index;}
  private:
    string name = "";
    int index = -1;
};

class Node{
  public:
    Node(){
      type = -1;
    }
    Node(Info info, int key){ // key = 0,1,2 -> 0 = player, 1 = team, 2 = year
      data = info;
      type = key;
    }
    Node(const Node& other){
      data = other.data;
      type = other.type;
      team = other.team;
      player = other.player;
    }
    string getName(){return data.getName();}
    int getIndex(){return data.getIndex();}
    Info& getInfo(){return data;}
    int getType(){return type;}
    vector<Info>& getTeamVec(){return team;}
    vector<Info>& getPlayerVec(){return player;}

  private:
    int type = -1;
    Info data;
    vector<Info> team;
    vector<Info> player;
};

void addTeamEdge(vector<Node>& adj, Info obj1, Info obj2){ //when adding edges, we got to index of obj1, and append obj2 to the Team Vector of Info
  adj.at(obj1.getIndex()).getTeamVec().push_back(obj2);
}

void addPlayerEdge(vector<Node>& adj, Info obj1, Info obj2){//when adding edges, we got to index of obj1, and append obj2 to the Player Vector of Info
  adj.at(obj1.getIndex()).getPlayerVec().push_back(obj2);
  adj.at(obj2.getIndex()).getPlayerVec().push_back(obj1);
}

void printGraph(vector<Node>& adj){ //simply look through the two Vectors inside Node
  for (int v = 0; v < adj.size(); ++v) {
    cout << endl << "Adjacency list of vertex " << v << endl;
    //print list of adj Team/Year
    cout << " Team/Year  " << adj.at(v).getName();
    for (Info x : adj.at(v).getTeamVec())
      cout << "-> " << x.getName();
    //print list of adj Player
    cout << endl << " Player     " << adj.at(v).getName();;
    for (Info x : adj.at(v).getPlayerVec())
      cout << "-> " << x.getName();
    cout << endl;
  }
}

bool findTeamAdj(vector<Node> adj, Info obj1, Info obj2){
  vector<Info> TeamVec = adj.at(obj1.getIndex()).getTeamVec();
  for(Info x : TeamVec)
    if(!x.getName().compare(obj2.getName()))
      return true;
  return false;
}

void ReadFile(string fileName, vector<Node>& adj){
  string line;
  ifstream myfile (fileName);
  if (myfile.is_open()){
    int index = 0;
    while(getline(myfile,line)){
      string word;
      istringstream ss(line);
      Info arr[3];
      int type_counter = 0;
      while(getline(ss, word, ',')){
        int type = type_counter%3;
        type_counter++;
        if(type == 2)
          word = arr[1].getName() + "_" + word;

        //find if obj already exists
        bool exist = false;
        int counter = 0;
        int idx = 0;
        for(Node x : adj){
          if(!word.compare(x.getName())){
            exist = true;
            idx = counter;
          }
          counter++;
        }
        if(!exist){
          Info infoObj(word, index);
          adj.push_back(Node(infoObj, type));
          arr[type] = infoObj;
          index++;
        }
        else{
          Info infoObj = adj.at(idx).getInfo();
          arr[type] = infoObj;
        }
      }
      if(!findTeamAdj(adj, arr[1], arr[2]))
        addTeamEdge(adj, arr[1], arr[2]);
      if(!findTeamAdj(adj, arr[2], arr[0]))
        addTeamEdge(adj, arr[2], arr[0]);
    }
    //connect red edges
    for(Node x : adj){
      if(x.getType() == 2){
        vector<Info> TeamVec = x.getTeamVec();
        for(int i = 0; i < TeamVec.size() - 1 ; i++)
          for(int j = i + 1; j < TeamVec.size(); j++)
            addPlayerEdge(adj, TeamVec.at(i), TeamVec.at(j));
      }
    }
    myfile.close();
  }
  else
    cout << "Could not open file " << fileName << endl;
}
 
int main (int argc, char *argv[]){
  //Initalize adjacency list of Nodes
  //-> Adjaceny List will be a vector of Nodes
  //--> Nodes will have two vectors (Player adj Vector and Team adj Vector) + any Info needed
  vector<Node> adj;

  string file = "input.txt";
  ReadFile(file, adj);
  printGraph(adj);



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