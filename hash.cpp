#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Node.h"
#include "hash.h"
#include "Info.h"

using namespace std;

Hash::Hash(int V)
{
    this->BUCKET = V;
    // table = new vector<Node>[BUCKET];
    //vector<Node> table;
    table.resize(BUCKET);
}

void Hash::insertItem(Node key)
{
    string name = key.getName();
    int index = hashFunction(name);
    table.at(index).push_back(key);
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
    for (int i = 0; i < BUCKET; i++) 
    {
        cout << i << " ";
        for(Node x : table.at(i))
        {
            cout << x.getName() << "--> "; 
        }
        cout << endl;
    }
}

Node* Hash::searchHash(string key)
{
    int index = hashFunction(key);
    for(int i = 0; i < table.at(index).size(); i++){
        if(table.at(index).at(i).getName() == key){
            return &(table.at(index).at(i));
        }   
    }
    return nullptr;
}

void Hash::addEdge(){
    for (int i = 0; i < BUCKET; i++) 
    {
        for(Node x : table.at(i))
        {
            if(x.getType() == 2){ // get Year Node
                vector<Info> PlayerVec = x.getPlayerVec();
                for(int i = 0; i < PlayerVec.size() - 1 ; i++)
                {
                    for(int j = i + 1; j < PlayerVec.size(); j++)
                    {
                        cout << "jasdkf" << endl;
                        searchHash(PlayerVec.at(i).getName())->getPlayerVec().push_back(PlayerVec.at(j));
                        searchHash(PlayerVec.at(j).getName())->getPlayerVec().push_back(PlayerVec.at(i));
                    } 
                }
            }
        }
    }
}