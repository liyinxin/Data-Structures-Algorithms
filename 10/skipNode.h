#pragma once

#ifndef __SKIPNODE__H
#define __SKIPNODE__H
#include <iostream>
#include <utility>


template<typename K,typename V>
struct skipNode{
    typedef std::pair<const K,V>    pairType;//在外部使用这个的时候，利用作用域运算符去调用::
    pairType element;
    skipNode<K,V> **next;//这个表示的是，该节点共有几个链表，这些链表分别表示的是每一级的链表
    skipNode(const pairType &theElement,int size) : element(theElement){
        next = new skipNode<K,V> *[size];
    }
};

#endif
