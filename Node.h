#ifndef NODE
#define NODE
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
#endif