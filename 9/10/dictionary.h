#pragma once
#ifndef __DICTIONARY__H
#define __DICTIONARY__H
#include <iostream>
#include <utility>


template<typename K,typename V>
class dictionary{
public:
    virtual ~dictionary() {}
    virtual bool empty()const =0;
    virtual int size()const =0;
    virtual std::pair<const K,V> *find(const K &)const =0;


private:

};

#endif
