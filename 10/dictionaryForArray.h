#pragma once
#ifndef __DICTIONARYFORARRAY__H
#define __DICTIONARYFORARRAY__H

#include <iostream>
#include <utility>


template<typename K,typename V>
class dictionaryForArray{
public:
    virtual ~dictionaryForArray() {}
    virtual bool empty()const =0;
    virtual int size()const =0;
    virtual std::pair<K,V/*K表示的是字典的Key，V表示的是字典的Value*/> *find(const K &) const=0;
    virtual void erase(const K &) =0;
    virtual void insert(const std::pair<K,V> &) =0;
};

#endif
