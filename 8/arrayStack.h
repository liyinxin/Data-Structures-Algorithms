#pragma once
#ifndef __ARRAYSTACK__H

#include "stack.h"
class illegalIndex : public std::invalid_argument{
public:
    explicit illegalIndex(std::string s):invalid_argument(s){}
};

template<typename T>
class arrayStack : public stack<T>{
public:
    arrayStack(int initialCapacity=10);
    
    ~arrayStack() {delete []stack;}

    bool empty()const{return stackTop == -1;}
    int size()const{return stackTop + 1;}
    T &top()const{
        if(stackTop==-1)
            throw illegalIndex("the operator of top,and the error is the stack is empty");
        return stack[stackTop];
    }
    void pop(){
        if(stackTop==-1)
            throw illegalIndex("the operator of pop,and the error is the stack is empty");
        stack[stackTop--].~T();//任何类型的都有自己的析构函数，所以
        //可以这样使用.
    }
    void push(const T &theElement);
    T get(int i)const{
        if(i < 0 || i >= arrayLength)
            throw illegalIndex("the operator of get,and the error is the index is not right");
        return stack[i];
    }
    void clear(){
        while(size() != 0){
            pop();
        }
    }
private:
    int stackTop;       //栈顶的索引
    int arrayLength;    //栈的长度
    T *stack;           //用来保存数据的一个指针
};

//构造函数
template<typename T> arrayStack<T>::arrayStack(int initialCapacity){
    if(initialCapacity<1)
        throw illegalIndex("the initialCapacity must be >0");
    arrayLength = initialCapacity;
    stackTop= -1;
    stack = new T[initialCapacity];
}

template<typename T>void arrayStack<T>::push(const T &theElement){
    if(stackTop+1 == arrayLength)//如果当前的栈内元素的长度等于总长度的话，也就是已经占满了空间
    {//分配新的内存空间
        auto temp = new T[arrayLength * 2];
        arrayLength *= 2;
        for(int i = 0;i != arrayLength;++i){
            temp[i] = stack[i];
        }
        delete []stack;
        stack = temp;
    }
    //如果内存空间没有满的话，直接压入到栈内
    stack[++stackTop] = theElement;
}
#endif
