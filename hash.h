#ifndef _HASH_H_
#define _HASH_H_
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
        void displayAdj();
    private: 
        int BUCKET;
        vector<vector<Node>> table;
};

#endif