#pragma once
#include "queue.h"
#include "illegalParameterValue.h"
#include "chainNode.h"


template<typename T>
class linkedQueue
{
public:
    linkedQueue(int initialCapacity = 10) {
        queueFront = NULL;
        queueSize  = 0;
    }
    ~linkedQueue() {
        while(queueFront != NULL){
            auto nextNode = queueFront->next;
            delete queueFront;
            queueFront = nextNode;
            queueSize--;
        }
    }
    
    bool empty()const{return queueSize==0;}
    int size()const{return queueSize;}
    T &front(){
        if(queueSize==0)//首先判断下当前队列中有没有数据
            throw illegalParameterValue("the queue is empty");
        return queueFront->element;
    }
    T &back(){
        if(queueSize==0)//首先判断下当前队列中有没有数据
            throw illegalParameterValue("the queue is empty");
        return queueBack->element;
    }
    void pop();
    void push(const T &theElement);
private:
    chainNode<T> *queueFront;     //队列的尾后位置的
    chainNode<T> *queueBack;     //队列的前向位置的
    int queueSize;              //这个队列的大小
};


template<typename T> void linkedQueue<T>::pop(){
    if(queueSize == 0)
        throw illegalParameterValue("the queue is empty");
    auto nextNode = queueFront->next;
    delete queueFront;
    queueFront = nextNode;
    queueSize--;
}

template<typename T> void linkedQueue<T>::push(const T &theElement){
    
    auto newNode = new chainNode<T>(theElement,NULL);//创建一个新的节点
    if(queueSize == 0){//如果是第一个点的话
        queueFront  = newNode;
    }
    else{//如果这个队列已经有成员了
        queueBack->next = newNode;
    }
    queueBack = newNode;//这一步就是让queueBack指向下一个节点的
    //如果当前的是第一个的时候，queueFront跟queueBack指向的是
    //同一个位置
    queueSize++;
}
