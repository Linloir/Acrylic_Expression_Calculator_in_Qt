#include "hashmap.h"

HashMap::HashMap() : size(DEFAULT_MAP_SIZE)
{
    headList = new struct hashNode[size];
}

HashMap::HashMap(int _size) : size(_size)
{
    headList = new struct hashNode[size];
}

HashMap::~HashMap(){
    for(int i = 0; i < size; i++){
        delete headList[i].next;
    }
    delete [] headList;
}

int HashMap::hashAddr(char key){
    return key % 10;
}

struct hashNode* HashMap::find(char key){
    int addr = hashAddr(key);
    struct hashNode* ptr = headList[addr].next;
    while(ptr != nullptr){
        if(ptr->key == key)
            return ptr;
        ptr = ptr->next;
    }
    return ptr;
}

bool HashMap::insert(char key, int val){
    struct hashNode* ptr = find(key);
    if(ptr == nullptr){
        int addr = hashAddr(key);
        struct hashNode* newNode = new struct hashNode(key, val);
        newNode->next = headList[addr].next;
        headList[addr].next = newNode;
        return true;
    }
    else
        return false;
}

int HashMap::getVal(char key){
    struct hashNode* ptr = find(key);
    if(ptr == nullptr)
        return -1;
    else
        return ptr->val;
}

int HashMap::operator[](char key){
    return getVal(key);
}

void initOpMap(){
    opMap.insert('+', 0);
    opMap.insert('-', 0);
    opMap.insert('*', 1);
    opMap.insert('/', 1);
    opMap.insert('%', 1);
    opMap.insert('^', 2);
    opMap.insert('.', 3);
}
