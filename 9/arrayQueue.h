#pragma once
#ifndef __ARRAYQUEUE__H
#define __ARRAYQUEUE__H

#include "queue.h"
#include <sstream>
#include "illegalParameterValue.h"
#include <iostream>

template<typename T>
class arrayQueue : public queue<T>{
public:
    arrayQueue(int initialCapacity = 10);
    bool empty()const{return theFront == theBack;}
    //这个size主要是如果theBack的下标小于theFront的时候，需要加下arrayLength
    //然后再对arrayLength进行取余
    int size()const{return (theBack - theFront + arrayLength) % arrayLength;}
    //返回队列首部元素
    T &front(){
        if(theFront == theBack)
            throw illegalParameterValue("the queue is empthy");
        //注意，下面的这个取余操作是为了防止数组越界的，也就是在
        //队列尾巴是arrayLength-1的时候，下一个加1的时候会发生越界行为
        //
        return queue[(theFront+1) % arrayLength];
    }
    //返回队列尾部的数据
    T &back(){
        if(theFront == theBack)
            throw illegalParameterValue("the queue is empty");
        return queue[theBack];
    }
    //出队
    void pop(){
        if(theFront == theBack)
            throw illegalParameterValue("the queue is empty");
        //如果非空
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();   //析构掉该数据，其实也没必要析构
    }
    void push(const T &theElement);
    ~arrayQueue() {delete []queue;}
private:
    int arrayLength;    //表示的是队列的长度
    int theFront;       //表示的是队列首元素的前一个位置
    int theBack;        //队列的尾元素
    T *queue;           //用来存放数据的数组(类似于数组)
};

template<typename T> arrayQueue<T>::arrayQueue(int initialCapacity){
    if(initialCapacity < 1){
        std::ostringstream s;
        s<<"Initial capacity = "<<initialCapacity<<" must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    queue       = new T[arrayLength];
    theFront    = 0;        //theFront表示队列首元素的前一个位置
    theBack     = 0;        //表示当前队列的尾部元素的位置
}


template<typename T>void arrayQueue<T>::push(const T &theElement){
    if((theBack + 1) % arrayLength == theFront){//这样的话，就说明下一个要插入的位置是最后
        //一个位置了，这个时候就需要我们去扩容了
        T *newQueue = new T[2 * arrayLength];
        int start = (theFront + 1) % arrayLength;//找到当前队列的第一个元素的下标
        //如果是这个满的数据就从下标1开始的话，直接完整的copy
        if(start < 2){
            //之所以是<2，是因为第一次的时候start = 1;因为theFront=0；
            //然后，第二次以及以后的时候，theFront被改变成NewArrayLength-1；
            //也就是数组的最后一个元素了，所以这个时候start = 0；所以是
            //start < 2
            //std::copy([first,last))
            std::copy(queue + start,queue + theBack+1,newQueue);
        }
        else{
            //如果是数据跨了一个完整的数组的话，需要移动两次
            //复制从起始位置到数组的最后的一个位置
            std::copy(queue+start,queue+arrayLength,newQueue);
            //复制数组的开始到数组队列的尾部
            std::copy(queue,queue+theBack+1,newQueue+arrayLength-start);
        }
        theFront = 2 * arrayLength -1;
        theBack = arrayLength-2;//因为空了一个元素，所以是-2
        arrayLength *= 2;
        delete []queue;//把原先的那个删掉
        queue = newQueue;
    }
    //如果没有满的话，我们要插入数据，要是满的话，上边已经处理好
    //新的空间了，我们可以直接插入了
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}
#endif
