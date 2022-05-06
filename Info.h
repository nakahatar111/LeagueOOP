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
    }
    Info(string str){
      name = str;
    }
    string getName(){return name;}
  private:
    string name = "";
};
#endif