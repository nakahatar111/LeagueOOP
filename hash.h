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
        int getSize();
    private: 
        int BUCKET;
        int size;
        vector<vector<Node>> table;
};

#endif