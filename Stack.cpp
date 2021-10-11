#include "Stack.h"

template<typename T>
bool Stack<T>::Resize(int _capacity){
    capacity = _capacity;
    T* newStack = (T*)realloc(stack, sizeof(T) * capacity);
    if(!newStack){
        //Error
        return false;
    }
    stack = newStack;
    return true;
}

template<typename T>
Stack<T>::Stack() : capacity(DEFAULT_CAPACITY), size(0) {
    stack = (T*)malloc(sizeof(T) * capacity);
    if(!stack){
        //Error
    }
}

template<typename T>
Stack<T>::Stack(int _capacity) : capacity(_capacity), size(0) {
    stack = (T*)malloc(sizeof(T) * capacity);
    if(!stack){
        //Error
    }
}

template<typename T>
Stack<T>::Stack(const Stack<T> & s){
    //construct
    capacity = s.capacity;
    size = s.size;
    stack = (T*)malloc(sizeof(T) * capacity);
    if(!stack){
        //Error
    }
    //copy
    for(int i = 0; i < size; i++)
        stack[i] = s.stack[i];
}

template<typename T>
Stack<T>::~Stack(){
    free(stack);
    stack = nullptr;
}

template<typename T>
void Stack<T>::PushBack(T val){
    stack[size++] = val;
    if(size == capacity){
        bool res = Resize(capacity * 2);
        if(!res){
            //Resize Error
        }
    }
}

template<typename T>
T Stack<T>::PopBack(){
    if(size == 0){
        //Tries to pop from an empty stack
        //throw an error?
        T emptyT;
        return emptyT;
    }
    else{
        T res = stack[--size];
        return res;
    }
}

template<typename T>
T Stack<T>::TopElement(){
    if(size == 0){
        //Tries to get an element from an empty stack
        //throw an error?
        T emptyT;
        return emptyT;
    }
    else{
        return stack[size - 1];
    }
}

template<typename T>
int Stack<T>::Size(){
    return size;
}

template<typename T>
bool Stack<T>::IsEmpty(){
    return size == 0;
}
