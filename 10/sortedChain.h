#pragma once
#ifndef __SORTEDCHAIN__H
#define __SORTEDCHAIN__H

#include "pairNode.h"
#include "dictionary.h"
#include "illegalValue.h"

template<typename K,typename V>
class sortedChain : public dictionary<K,V>{
public:
    sortedChain():firstNode(NULL),dSize(0){}
    ~sortedChain();//在类外边实现
    //返回字典是不是空
    bool empty()const{
        return dSize == 0;
    }
    //返回字典的大小
    int size()const{
        return dSize;
    }
    //在类外边实现
    std::pair<const K,V> *find(const K &)const;
    //在类外边实现
    void erase(const K &);
    //在类外边实现
    void insert(const std::pair<const K ,V> &);
    
    //新增加的功能
    void output(std::ostream &out)const;
protected:
    pairNode<K,V> *firstNode;//指向链表的头节点的
    int dSize;              //表示字典的大小的
};

//注意，这个查找法不是二分法查找
template<typename K,typename V> std::pair<const K,V> *sortedChain<K,V>::find(const K &theKey)const{
    pairNode<K,V> *currentNode = firstNode;
    //这个不是二分法查找，这个是从头到尾查找
    while(currentNode != NULL && currentNode->element.first != theKey)
        currentNode = currentNode->next;
    if(currentNode != NULL && currentNode->element.first == theKey)
        return &currentNode->element;
    return NULL;
}
//定义删除函数
template<typename K,typename V> void sortedChain<K,V>::erase(const K &theKey){
    pairNode<K,V> *p  = firstNode,   //用来查找pairNode的
                  *tp = NULL;       //tp 用来表示p的前一个元素，用来删除的时候有用
    while(p != NULL && p->element.first != theKey){
        tp = p;
        p  = p->next;
    }
    if(p != NULL && p->element.first == theKey){//如果找到了的话
        if(tp == NULL){//也就是如果第一个节点就已经匹配的话
            firstNode = p->next;
        }
        else//如果不是最后一个的话
            tp->next = p->next;
        delete p;
        dSize--;
    }
}

//定义析构函数
template<typename K,typename V> sortedChain<K,V>::~sortedChain<K,V>(){
    pairNode<K,V> *currentNode = firstNode;
    while(currentNode != NULL){
        currentNode = currentNode->next;
        delete firstNode;
        firstNode = currentNode;
        dSize--;
    }
}
//定义插入函数
template<typename K,typename V> void sortedChain<K,V>::insert(const std::pair<const K,V> &thePair){
    //插入操作的话
    pairNode<K,V> *currentNode = firstNode,
                  *tp          = NULL;//用来保存要插入位置的前一个节点的
    while(currentNode != NULL && currentNode->element.first < thePair.first){
        tp          = currentNode;
        currentNode = currentNode->next;
    }
    //如果跳出这个循环了
    //如果thePair出现在这个字典中了，那么就把value更改一下
    if(currentNode != NULL && currentNode->element.first == thePair.first){//如果这个thePair出现在中间的话且等于某一个节点的值的话
        currentNode->element.second = thePair.second;
        dSize++;
        return  ;
    }
    //如果没有出现的话，那么判断下这个thePair是在首节点位置还是别的节点
    auto newNode = new pairNode<K,V>(thePair,currentNode);
    if(tp == NULL){//这表示的是当前插入的节点的Key是比所有节点的Key都要小的
        firstNode = newNode;
    }else
        tp->next  = newNode;
    dSize++;
}

template<typename K,typename V> void sortedChain<K,V>::output(std::ostream &out)const{
    auto p = firstNode;
    while(p != NULL){
        std::cout<<'('<<p->element.first<<','<<p->element.second<<')'<<" ";
        p = p->next;
    }
}
#endif
