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
    virtual std::pair<const K,V/*K表示的是字典的Key，V表示的是字典的Value*/> *find(const K &) const=0;
    virtual void erase(const K &) =0;
    virtual void insert(const std::pair<const K,V> &) =0;
};

#endif
