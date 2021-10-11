#ifndef HASHMAP_H
#define HASHMAP_H

#define DEFAULT_MAP_SIZE 10

struct hashNode{
    char key;
    int val;
    struct hashNode* next;
    hashNode() : next(nullptr){}
    hashNode(char _key, int _val) : key(_key), val(_val), next(nullptr){}
    ~hashNode(){if(next == nullptr) return; else delete next;}
};

class HashMap
{
private:
    int size;
    struct hashNode* headList;
    int hashAddr(char key);
    struct hashNode* find(char key);
public:
    HashMap();
    HashMap(int size);
    ~HashMap();
    bool insert(char key, int val);
    int getVal(char key);
    int operator [](char key);  //equals to getVal
};

extern HashMap opMap;
void initOpMap();

#endif // HASHMAP_H
