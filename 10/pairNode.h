#pragma once
#ifndef __PAIRNODE__H

#include <utility>
#include <iostream>

template<typename K,typename V>
struct pairNode{
    typedef std::pair<const K,V> pairType;
    pairType element;
    pairNode<K,V> *next;
    pairNode(const pairType &theElement):element(theElement){}
    //头插法
    pairNode(const pairType &theElement,pairNode<K,V> *theNext):element(theElement){
        next = theNext;
    }
};

#endif
