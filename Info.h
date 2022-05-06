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
#endif