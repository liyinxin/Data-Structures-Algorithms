#pragma once
#ifndef __LINKEDSTACK__H
#include <iostream>
#include <string>
class illegalIndex : public std::invalid_argument{
public:
    explicit illegalIndex(std::string s):invalid_argument(s){}
};


template<typename T>
class chainNode{
public:
    chainNode(){}//默认构造函数
    chainNode(const T &theElement):next(NULL){
        element = theElement;
    }
    //前插法
    chainNode(const T &theElement,chainNode<T> *next){
        element = theElement;
        this->next = next;
    }
    chainNode<T> *next;
    T element;
};



template<typename T>
class linkedStack
{
public:
    linkedStack(int initialCapacity = 10):stackTop(NULL),stackSize(0){}
    bool empty()const{
        return stackSize == 0;
    }
    int size()const{
        return stackSize;
    }
    T &top(){
        if(stackSize == 0)
            throw illegalIndex("the stack is empty");
        return stackTop->element;
    }
    void pop();
    void push(const T &theElement){
        stackTop = new chainNode<T>(theElement,stackTop);
        stackSize++;
    }
    ~linkedStack();

private:
    chainNode<T> *stackTop;
    int stackSize;
};
//pop的方法
template<typename T> void linkedStack<T>::pop(){
    if(stackSize == 0)
        throw illegalIndex("the stack is now empty");
    auto temp = stackTop;//保留下当前的节点
    stackTop = stackTop->next;
    delete temp;
    stackSize--;
}

//析构函数

template<typename T> linkedStack<T>::~linkedStack(){
    while(stackTop != NULL){
        auto nextNode = stackTop->next;
        delete stackTop;
        stackTop = nextNode;
        stackSize--;
    }
}
#endif
