#pragma once

#ifndef __SORTARRAY__H
#define __SORTARRAY__H

#include "dictionaryForArray.h"
#include <vector>
#include <iostream>
#include <algorithm>


template<typename K,typename V>
class sortedArray : public dictionaryForArray<K,V>{
public:
    sortedArray(int initialCapacity = 10) :capacities(initialCapacity),dSize(0),element(10){}
    bool empty()const override{return dSize==0;}
    int size()const override{return dSize;}
    std::pair<K,V> *find(const K &)const override;
    void erase(const K &)override;
    void insert(const std::pair<K,V> &)override;
    void output(std::ostream &out)const;
    ~sortedArray();

private:
    //注意，在使用vector的时候，因为加入了const K
    //如果K也是类的话，那么我使用它的
    std::vector<std::pair<K,V>> element;          //存放字典
    int capacities;                         //表示这个字典总的大小
    int dSize;                              //表示字典当前的大小
};

//删除操作
template<typename K,typename V> void sortedArray<K,V>::erase(const K &theKey){
    int i = 0;
    while(i != dSize && element[i].first < theKey)
        i++;
    if(i != dSize && element[i].first == theKey){//找到了的话
        element.erase(element.begin()+i);
        dSize--;
    }
    //如果没找到的话，那就什么也不做
}
//插入操作
template<typename K,typename V> void sortedArray<K,V>::insert(const std::pair<K,V> &theElement){
    int i = 0;
    while(i != dSize && element[i].first < theElement.first)
        i++;
    if(i != dSize && element[i].first == theElement.first){//如果是相等的话
        element[i].second = theElement.second;
        return ;
    }
    //如果不相等的话，不用去考虑扩容问题，因为vector自带扩容性质
    element.insert(element.begin()+i,theElement);
    dSize++;
    return;
}
//查找操作
template<typename K,typename V> std::pair<K,V> *sortedArray<K,V>::find(const K &theKey)const{
    int left   = 0;
    int right  = dSize-1;
    int middle = (left+right)/2;
    while(left < right){
        if(element[middle].first < theKey){//目标值在中间的右边
            left    = middle+1;
            middle  = (left+right)/2;
        }else if(element[middle].first > theKey){//目标值在中间的左边
            right   = middle;
            middle  = (left+right)/2;
        }else{
            //注意，常量函数中，返回其成员的时候，返回的都是带着const的，如果你的常量函数的返回类型是指针或者引用的话
            //就要注意一下，因为const std::pair<const K,V> *p返回的时候是不能赋予给std::pair<const K,V>的，所以这个时候
            //有两种方法，一种是改变这个函数的常量属性；另一种是改变其返回类型，还有一种就是将其const属性去掉，跟下面的一样
            auto temp = &(element[middle]);
            return const_cast<std::pair<K,V> *>(temp);
        }
    }
    //到最后left=right
    if(element[middle].first == theKey){
        auto temp = &(element[middle]);
        return const_cast<std::pair<K,V> *>(temp);
    }else
        return NULL;//如果左边都超过右边了的话，那么就是NULL了
}

//析构函数
template<typename K,typename V> sortedArray<K,V>::~sortedArray(){
    element.clear();
    dSize = 0;
}
//output函数
template<typename K,typename V> void sortedArray<K,V>::output(std::ostream &out)const{
    /*
    for_each(element.begin(),element.end(),[](decltype(element.begin()) it)
                                    {std::cout<<"("<<it->first<<","<<it->second<<")"<<" ";});
    */
    for(auto i = 0;i != dSize;++i)
        std::cout<<"("<<element[i].first<<","<<element[i].second<<")"<<" ";
}
#endif
