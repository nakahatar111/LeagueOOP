#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Node.h"
#include "hash.h"

using namespace std;

Hash::Hash(int V)
{
    this->BUCKET = V;
    table = new vector<Node>[BUCKET];
}

void Hash::insertItem(Node key)
{
    string name = key.getName();
    int index = hashFunction(name);
    table[index].push_back(key);
}

int Hash::hashFunction(string key)
{
    int sum = 0;
    for(int i = 0; i < 3 || i < key.length(); i++)
    {
        char x = key.at(i);
        sum += (int)x;
    }
    return sum;
}

void Hash::displayHash()
{
    for (int i = 0; i < BUCKET; i++) 
    {
        cout << i;
        for (auto x : table[i])
        {
            cout << x.getName() << endl;
            cout << endl;
        }
    }
}
