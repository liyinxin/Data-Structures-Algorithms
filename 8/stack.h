#pragma once
#ifndef __STACK__H
#include <iostream>

template<typename T>
class stack
{
public:
    virtual bool empty()const=0;        //栈空时返回true；否则返回false
    virtual int size()const=0;          //返回栈中元素的个数
    virtual T &top()const=0;            //返回栈顶元素
    virtual void pop()=0;               //删除栈顶元素
    virtual void push(const T &theElement)=0;//将元素x入栈
    virtual ~stack() {}
private:
    
};
#endif
