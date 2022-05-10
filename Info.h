#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#ifndef INFO
#define INFO
class Info{
  public:
    Info(){
      name = "";
      index = -1;
    }
    Info(string str, int ind){
      name = str;
      index = ind;
    }
    string getName(){return name;}
    int getIndex(){return index;}
  private:
    string name = "";
    int index;
};
#endif