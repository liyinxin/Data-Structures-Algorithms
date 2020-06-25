#pragma once
#ifndef __MYCHAIN__H
#define __MYCHAIN__H

#include <iostream>
#include <sstream>
#include <iterator>


class illegalParameterValue : public std::length_error{
public:
    explicit illegalParameterValue(const std::string &s):length_error(s){}
};

template<typename T> class linearList{
public:
    virtual ~linearList(){}
    virtual bool empty()const =0;
    virtual int size()const =0;
    virtual T &get(int theIndex) =0;
    virtual int indexOf(const T& theElement)const =0;
    virtual void erase(int theIndex) =0;
    virtual void insert(int theIndex,const T &theElement) =0;
    virtual void output(std::ostream &out)const =0;
};


template<typename T> class extendedLinearList : public linearList<T>{
public:
   virtual ~extendedLinearList(){} 
   virtual void clear() =0;
   virtual void push_back(const T& theElememt) =0;
};
template<typename T> class mychainNode{
public:
    T element;//数据
    mychainNode<T> *next;//指针域，指针链

    mychainNode():next(NULL){}//普通的构造函数，默认构造
    //根据theElement创建一个node节点
    mychainNode(const T& theElement):next(NULL){
        this->element = theElement;
    }
    //这个是为了创建一个element是theElement的节点，然后这个节点
    //的下一个节点是传进来的next指向的节点
    mychainNode(const T &theElement,mychainNode<T> *next){
        this->element = theElement;
        //新创建的节点的next指针指向的是传进来的指针所指向的节点
        //也就是我传进来的指针是firstNode的时候，我新创建的这个节点的
        //next指针指向的就是头结点了（因为firstNode的值就是头节点的地址)
        this->next = next;
    }
    ~mychainNode(){}
};
template<typename T>  class mychain : public linearList<T>
{
public:
    mychain(int initialCapacity = 10);
    mychain(const mychain<T> &theChain);
    bool empty()const override{return listSize==0;}
    int size()const override{return listSize;}
    T &get(int theIndex);
    int indexOf(const T &theElement)const;
    void erase(int theIndex);
    void insert(int theIndex,const T &theElement);
    void output(std::ostream &out)const;

    ~mychain();
    class iterator{
    public:
        //前向迭代器所需要的typedef语句
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        //构造函数
        iterator(mychainNode<T> *theNode = NULL):node(theNode){}
        
        //解引用操作符
        T &operator*()const{return node->element;}
        T *operator->()const{return &node->element;}

        //迭代器加法操作
        iterator &operator++(){//前加
            node=node->next;
            return *this;
        }
        iterator operator++(int){//后加
            auto oldnode = *this;
            node = node->next;
            return oldnode;

        }
        //注意,this是一个指针而不是一个对象，所以需要使用->或* 
        //相等检验
        bool operator==(const iterator right)const{
            return this->node == right.node;
        }
        bool operator!=(const iterator right)const{
            return this->node != right.node;
        }

    protected:
        mychainNode<T> *node;
    };
    //返回firstNode指向的节点，
    iterator begin(){
        return iterator(firstNode);
    }
    iterator end(){
        return iterator(NULL);//因为mychainNode<T>的尾部节点的next指向的是NULL
    }
protected:
    bool checkIndex(int theIndex)const;
    mychainNode<T> *firstNode;//这个是头结点的指针而已，它只是一个指针而已，它的值是一个地址而已，
    //所以它不会有element这些成员的，也没有构造函数之类的!!!它仅仅是里边保存着一个mychainNode
    //对象的地址。但是它可以访问这个对象里边的成员以及函数的！！！
    //也就是保存了第一个节点的地址信息，我可以通过这个指针去访问我的节点
    int listSize;
};
template<typename T> mychain<T>::~mychain(){
    mychainNode<T> *currentNode = firstNode;
    while(currentNode!=NULL){
        delete currentNode;
        currentNode = currentNode->next;
    }
}
template<typename T> mychain<T>::mychain(int initialCapacity){
    if(initialCapacity<1){
        std::ostringstream s;
        s<<" the size must > 0";
        throw illegalParameterValue(s.str());
    }
    firstNode = NULL;//指针指向的为空
    listSize = 0;
}

template<typename T> mychain<T>::mychain(const mychain<T> &theChain){
    mychainNode<T> *p = theChain.firstNode;
    if(theChain.listSize == 0){
        this->firstNode = NULL;//如果要拷贝的是一个空对象，那么让其firstNode指向一个NULL对象
        listSize = 0;
    }
    else{
        //如果不是空的话，先让firstNode指向一个新创建的头节点，内容是拷贝的
        //theChian的头结点的内容
        this->firstNode = new mychainNode<T>(theChain.firstNode->element);
        p = p->next;//p指向头结点的下一个位置了
        mychainNode<T> *currentNode = this->firstNode;//用一个临时变量去遍历本对象的链表
        while(p!=NULL){
            currentNode->next = new mychainNode<T>(p->element);
            currentNode = currentNode->next;
            p = p->next;
        }
        currentNode->next = NULL;
        listSize = theChain.listSize;
    }
}

template<typename T> bool mychain<T>::checkIndex(int theIndex)const{
    if(theIndex < 0 || theIndex >= listSize){
        std::ostringstream s;
        s<<"index = "<<theIndex<<" listSize "<<listSize<<" ";
    }
}

template<typename T> void mychain<T>::output(std::ostream &out)const{
    mychainNode<T> *currentNode = firstNode;
    int index = 0;
    while(index++ != listSize){
        out<<currentNode->element<<" ";
        currentNode = currentNode->next;
    }
}
template<typename T> std::ostream &operator<<(std::ostream &out,mychain<T> &x){
    x.output(out);
    return out;
}

template<typename T> T &mychain<T>::get(int theIndex){
    checkIndex(theIndex);//先检查索引是不是有效
    auto currentNode = firstNode;//获得头指针
    for(int i = 0;i != theIndex;++i){//到theIndex
        currentNode = currentNode->next;
    }
    return currentNode->element;
}

template<typename T> int mychain<T>::indexOf(const T &theElememt)const{
    auto currentNode = firstNode;
    int index = 0;
    while((currentNode != NULL) && (currentNode->element != theElememt)){//这个是第一个节点的指针
        index++;
        currentNode = currentNode->next;
    }
    if(index == listSize)
        return -1;
    else
        return index;
}

template<typename T> void mychain<T>::erase(int theIndex){
    //在删除之前要检查下索引是不是有效的
    checkIndex(theIndex);
    mychainNode<T> *deletedNode=NULL;
    //索引没有问题的话，进行删除。删除的话，要判断下是不是要在头上插入
    if(theIndex == 0){//处理第一个节点的时候要注意一点它跟别的不一样
        deletedNode = firstNode;//指向要删除的地址
        firstNode = deletedNode->next;
    }
    else{//如果不是首节点的话，
        mychainNode<T> *currentNode = firstNode;
        for(int i = 0; i != theIndex - 1;++i)
            currentNode = currentNode->next;//最后一次currentNode会是要删除的节点
        //的前一个节点
        deletedNode = currentNode->next;
        currentNode->next = deletedNode->next;//最后一个元素也是这样的处理方法
    }
    delete deletedNode;
    listSize--;
}

template<typename T> void mychain<T>::insert(int theIndex,const T& theElement){
    //在插入节点之前，我们需要去查看一下索引是不是有效的
    //记住，指针只是一个变量而已，它的值是一个地址，它没有成员之类的，
    //但是它指向的对象是可以有成员的，请记住，指针是没有成员的!!!!
    if(theIndex < 0 || theIndex > listSize){//注意，这个和一般的check不一样
        //因为可以直接在尾后插入，所以theIndex可以是listSize索引 
        std::ostringstream s;
        s<<" theIndex = "<<theIndex<<" and the listSize is "<<listSize;
        throw illegalParameterValue(s.str());
    }

    //如果有效
    if(theIndex == 0){//处理头结点和别的节点有点不一样
        //其实在头结点上插入节点也很简单，因为firstNode指向的就是头结点
        //所以我们直接让新创建的节点指向头结点，然后firstNode指向这个新创建的节点就好了
        firstNode = new mychainNode<T>(theElement,firstNode);
    }
    else{//如果不是在头结点上插入节点
        auto currentNode = firstNode;//currentNode指向头结点
        for(int i = 0;i != theIndex -1;++i)
            currentNode = currentNode->next;//找到要插入的节点的前一个位置
        //这个其实也是一样的，我插入的时候，先扎到了一个要插入节点位置的前一个节点位置（currentNode)
        //然后我创建一个节点，该节点的next指针是指向本来在theIndex位置的节点，然后我让
        //currentNode->next指向这个新的节点就好了。
        currentNode->next = new mychainNode<T>(theElement,currentNode->next);  
    }
    listSize++;
}
#endif
