#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Node.h"
#include "hash.h"

using namespace std;

Hash::Hash(int V)
{
    BUCKET = V;
    table.resize(BUCKET);
}

void Hash::insertItem(Node key)
{
    int index = hashFunction(key.getInfo().getName());
    table.at(index).push_back(key);
    size++;
}

int Hash::hashFunction(string key)
{ 
    int sum = 0;
    int length = 3;
    if(key.length() < 3)
        length = key.length();
    for(int i = 0; i < length; i++)
    {
        char x = key.at(i);
        sum += (int)x;
    }
    return sum % BUCKET;
}

void Hash::displayHash()
{
    for (int i = 0; i < BUCKET; i++) {
        cout << i << " ";
        for(Node x : table.at(i))
        {
            cout << x.getInfo().getName() << "--> "; 
            cout << "THIS IS THE INDEX" << x.getInfo().getIndex();
        }
        cout << endl;
    }
}

void Hash::displayAdj()
{
    for (int i = 0; i < BUCKET; i++){
      for(Node x : table.at(i)){
        cout << " Team/Year  " << x.getInfo().getName();
        for (Info y : x.getTeamVec())
          cout << "-> " << y.getName();
        //print list of adj Player
        cout << endl << " Player     " << x.getInfo().getName();
        for (Info y : x.getPlayerVec())
          cout << "-> " << y.getName();
        cout << endl << endl;
      }
    }
}

Node* Hash::searchHash(string key)
{
    int index = hashFunction(key);
    for(int i = 0; i < table.at(index).size(); i++)
        if(table.at(index).at(i).getInfo().getName() == key)
            return &(table.at(index).at(i));
            
    return nullptr;
}

void Hash::addEdge(){
    for (int i = 0; i < BUCKET; i++){
        for(Node node : table.at(i)){
            if(node.getType() == 2 && (node.getPlayerSize() > 0)){ // get Year Node
                for(int i = 0; i < node.getPlayerSize() - 1 ; i++){
                    for(int j = i + 1; j < node.getPlayerSize(); j++){
                        searchHash(node.getPlayerAt(i).getName())->addPlayer(node.getPlayerAt(j));
                        searchHash(node.getPlayerAt(j).getName())->addPlayer(node.getPlayerAt(i));
                    } 
                }
            }
        }
    }
}

int Hash::getSize(){
    return size;
}