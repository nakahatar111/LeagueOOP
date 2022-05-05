#ifndef _HASH_H_
#define _HASH_H_

#include <iostream>
#include<bits/stdc++.h>

using namespace std;

class Hash
{
    public:
        Hash(int V);
        void insertItem(string key);
        //void deleteItem(int key);
        int hashFunction(char *str);
        void displayHash();
    private: 
        int BUCKET;
        list<string> *table;
};

#endif