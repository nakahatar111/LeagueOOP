#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

using namespace std;

Hash::Hash(int V)
{
    this->BUCKET = V;
    table = new list<string>[BUCKET];
}

void Hash::insertItem(string key)
{
    char charArray[key.size()];
    key.copy(charArray, key.size());
    int index = hashFunction(charArray);
    table[index].push_back(key);
}

int Hash::hashFunction(char *str)
{
    unsigned long hash = 5381;
    int c;

    while(c = *str++)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

void Hash::displayHash()
{
    for (int i = 0; i < BUCKET; i++) 
    {
        cout << i;
        for (auto x : table[i])
        {
            cout << " --> " << x;
            cout << endl;
        }
    }
}
