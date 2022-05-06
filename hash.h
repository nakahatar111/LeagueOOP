#ifndef _HASH_H_
#define _HASH_H_

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Hash
{
    public:
        Hash(int V);
        void insertItem(Node key);
        //void deleteItem(int key);
        int hashFunction(string key);
        void displayHash();
        Node* searchHash(string key);
        void addEdge();
    private: 
        int BUCKET;
        vector<vector<Node>> table;
};

#endif