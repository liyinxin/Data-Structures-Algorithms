#pragma once
#ifndef __SKIPLIST__H
#define __SKIPLIST__H

#include "skipNode.h"
#include <vector>
#include <math.h>
#include <sstream>
#include "dictionary.h"
#include "illegalValue.h"


/*
 *
 *
 *      []------------->[]------------->[]->[]第三层链表
 *      []----->[]----->[]----->[]----->[]->[]第二层链表
 *      []->[]->[]->[]->[]->[]->[]->[]->[]->[]第一层链表
 *    头结点1   2   3   4   5   6   7   8 尾节点
 *   所以MaxLevel = log2(8) - 1 = 2;也就是0,1,2
 *  [0]表示的是0级链表，[1]表示的是一级链表，[2]表示的是二级链表
 *  注意，这里有一个小细节可以说明一下，我的最后的一个尾节点可以只有一层
 *  因为所有的倒数第二个节点都是会指向该节点也就是类似下面这种形式 
 *      []------------->[]------------->[]  \
 *                                           \       
 *      []----->[]----->[]----->[]----->[]----\
 *                                             \
 *      []->[]->[]->[]->[]->[]->[]->[]->[]------>[]
 *  所以我们的尾节点可以设置为只有一层链表就好了
 */




template<typename K,typename V>
class skipList : public dictionary<K,V>
{
public:
    skipList(K,int maxPairs = 10000,float prob = 0.5);
    ~skipList() {}
    bool empty()const override{return dSize==0;}
    int size()const override{return dSize;}
    std::pair<const K,V> *find(const K &)const override;
    void erase(const K &)override;
    void insert(const std::pair<const K,V> &)override;
    void output(std::ostream &out)const;

protected:
    float cutOff;               //用来确定层数
    int levels;                 //用来确定最大的非空链表数
    int dSize;                  //用来表示字典的大小
    int level()const;           //用来产生一个随机的level序列
    int maxLevel;               //允许最大的链表层数
    K tailKey;                  //最大的关键字
    skipNode<K,V> *search(const K&)const;
    skipNode<K,V> *headerNode;  //头结点指针
    skipNode<K,V> *tailNode;    //尾节点指针
    skipNode<K,V> **last;       //last[i]表示i层最后节点
                                //这个主要的作用是用来插入的时候保存每一级最接近要插入
                                //节点的节点，然后在后期插入的时候用来去改变链表的指向的
};

template<typename K,typename V> skipList<K,V>::skipList(K largeKey,int maxPairs,float prob){
    cutOff   = prob * RAND_MAX;
    //下边这个表示的是log(1/p)[maxPairs]也就是以1/p为底的maxPairs的对数变换是多少
    //然后ceil是上取整，所以这个表示的就是
    //|log(1/p)[maxPairs]| - 1;
    //--------------------
    maxLevel = (int)ceil(logf((float)maxPairs) / logf(1/prob)) - 1;//表示最大的链表个数(也可以理解为最大的层数)
    levels   = 0;
    dSize    = 0;
    tailKey  = largeKey;

    std::pair<K,V> tailPair;
    tailPair.first = tailKey;

    //其中headerNode必须得包含maxLevel个链表
    headerNode     = new skipNode<K,V> (tailPair,maxLevel + 1);
    tailNode       = new skipNode<K,V> (tailPair,0);
    last           = new skipNode<K,V> *[maxLevel+1];
    //空指针的话，初始化的时候是头节点跟尾节点是指向同一个地方的
    for(int i = 0; i <= maxLevel;i++)
        headerNode->next[i] = tailNode;
}

//查找操作
template<typename K,typename V> std::pair<const K,V> *skipList<K,V>::find(const K &theKey)const{
    if(theKey > tailKey){//如果这个要查找的theKey大于目前最大的关键字的话，直接返回NULL
        return NULL;
    }
    //如果不大于的话，那么就开始从最大的levels开始查找
    auto beforeNode = headerNode;
    for(int i = levels;i >= 0; --i){
        //注意next表示的是一个数组指针，所以next[i]表示的是一个指针
        //然后这个指针表示的是我第i级的指针的一个链表，这个next[i]表示的就是i级的next!!!
        //所以在i级查找的时候，可以使用beforeNode = beforeNode->next[i]表示beforeNode
        //指向这个一级的下一个节点
        //其实next[i]表示的是在第i级链表中的当前节点的下一个节点而已
        //跟next的意义是一样的!!!
        while(beforeNode->next[i]->element.first < theKey)//找到本级中最接近于theKey的一个节点
            beforeNode = beforeNode->next[i];//如果当前的节点还是小于theKey的话，那么移动到本级中的下一个节点继续去查找
    }
    //到最后必定是指向某一个节点，所以只需要判读这个节点是不是要找的就好了
    //如果是要找的话，那就返回该节点，否则返回NULL
    if(beforeNode->next[0]->element.first == theKey)
        return &beforeNode->next[0]->element;//表示在0级找到了该元素
    return NULL;//如果没找到的话，直接返回NULL
}

//产生一个级数用来表示每一个链表是第几级的
template<typename K,typename V> int skipList<K,V>::level()const{
    int lev = 0;
    //因为rand()产生的数是0----RAND_MAX;
    //而cutOff是        prob * RAND_MAX;
    //所以rand() <= cutOff表示的就是产生的数小于cutOff的概率为prob
    //
    while(rand() <= cutOff)
        lev++;
    //下面这一点表示的是，控制最大的链表个数（也就是层数）小于等于maxLevel
    return (lev <= maxLevel) ? lev : maxLevel;
}

//这个是用来查找要插入的theKey是不是已经存在了，如果存在的话，那么直接改变second就好了
//如果不存在的话，我们就需要先找到这个位置，然后给他分一个级别，再插入
template<typename K,typename V> skipNode<K,V> *skipList<K,V>::search(const K &theKey)const{
    skipNode<K,V> *beforeNode = headerNode;
    for(int i = levels; i >= 0;--i){
        while(beforeNode->next[i]->element.first < theKey)
            beforeNode = beforeNode->next[i];
        last[i] = beforeNode;//保存本级中接近的指针，方便后续插入的时候
        //要改变这些指针的指向
    }
    return beforeNode->next[0];
}

template<typename K,typename V> void skipList<K,V>::insert(const std::pair<const K,V> &thePair){
    if(thePair.first >= tailKey){//这个关键字太大的话
        std::ostringstream s;
        s<<"Key = "<<thePair.first<<" must be < "<<tailKey;
        throw illegalValue(s.str());        
    }
    //查看这个Key在不在已有的节点中了
    //返回的是最后的一个节点，这个时候要查看下是不是已经存在的节点
    skipNode<K,V> *theNode = search(thePair.first);
    if(theNode->element.first == thePair.first){
        theNode->element.second = thePair.second;
        return ;
    }
    //如果不存在的话，那么就需要插入了，不过这个时候需要设置级数
    int theLevel = level();
    //levels表示的是当前一共有多少个链表是非空的，也就是现在最大的层数是多少
    //如果随机产生的级数大于当前链表的个数的话，那么我们就给他降级到当前的
    //level+1上去
    if(theLevel > levels){
        theLevel = ++levels;
        last[theLevel] = headerNode;//记住这个细节，这个表示，如果我
        //们分配的级数如果大于当前非空的链表的个数的话，我们需要给它
        //降级到当前levels+1的级数，然后因为当前非空的链表个数最多才
        //levels个，所以我们需要让最顶层的数据链表的last[theLevel] = headerNode
        //这样我们在改变最顶层的数据链表的时候，可以让头节点指向这个节点
        //其实也就是这种情况
        /*
         *
         *      []------------------------->|-->[]|->[]
         *      []------------->[]----------|-->[]|->[]第三层链表
         *      []----->[]----->[]----->[]--|-->[]|->[]第二层链表
         *      []->[]->[]->[]->[]->[]->[]--|-->[]|->[]第一层链表
         *                                    插入的节点
         *这个时候，我们需要让last[theLevel] = headerNode;
         *然后插入的时候还是newNode->next[theLevel] = last[theLevel]->next[theLevel];
         *                  last[theLevel].next[theLevel] = newNode;
         *
         */
    }

    skipNode<K,V> *newNode = new skipNode<K,V>(thePair,theLevel+1);
    //下面的就是将这个节点，插入到0----theLevel中的所有链表中去，
    //一个链表一个链表的插入
    for(int i = 0;i <= theLevel;++i){
        newNode->next[i] = last[i].next[i];
        last[i]->next[i] = newNode;
    }
    dSize++;
    return ;
}
//删除关键字为theKey的节点
template<typename K,typename V> void skipList<K,V>::erase(const K &theKey){
    if(theKey > tailKey){
        return ;//关键字太大了，直接返回
    }
    //如果在范围之内，去查找存不存在该关键字的节点
    //theNode的类型是skipNode<K,V> *
    auto theNode  = search(theKey);
    if(theNode->element.first == NULL)//如果不存在的话
        return;
    if(theNode->element.first == theKey){//如果存在的话，那么就删除
        //注意，for循环中的last[i]->next[i] == theNode;
        //表示的是，我只有在本级链表中有指向该要删除的节点的级中才去改变
        //链表的指向，超过了这个级的话，那么我就不改变了，其实就是在
        //0----i之间改变链表额指向
        for(int i = 0;i <= levels && last[i]->next[i] == theNode;i++)//改变每一个链表的指向
            last[i]->next[i] = theNode->next[i];
    }
    //如果当前这个链表是最高的话，那么需要更新下
    while(levels > 0 && headerNode->next[levels] == tailNode)
        levels--;
    delete theNode;
    dSize--;
    return ;
}
#endif
