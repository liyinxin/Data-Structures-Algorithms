#pragma once
#ifndef __DERIVEDARRAYSTACK__H

#include "stack.h"
#include "array.h"

template<typename T>
class derivedArrayStack : public stack<T>,
                          private arrayList<T>{
public:
    derivedArrayStack(int initialCapacity = 10):arrayList<T>(initialCapacity){}
    bool empty()const{return this->arrayList<T>::empty();}
    int size()const{return this->arrayList<T>::size();}
    T &top()const{
        if(empty())
            throw illegalParameterValues("stack is empty");
        return this->arrayList<T>::get(this->size()-1);
    }
    void pop(){
        if(empty())
            throw illegalParameterValues("stack is empty");
        this->arrayList<T>::erase(this->size()-1);
    }
    void push(const T &theElement){
        this->arrayList<T>::push_back(theElement);
    }
    ~derivedArrayStack() {}

private:

};

#endif
