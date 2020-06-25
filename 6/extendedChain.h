#pragma once
#ifndef __EXTENDEDCHAIN__H
#define __EXTENDEDCHAIN__H


//注意，在模板类的继承过程中，你在派生类中使用模板基类的成员的时候，一定要加上、
//这个模板类的类型的比如说我想使用listSize，那么就只能使用mychain<T>::listSize才可以
#include "mychain.h"
template<typename T> class extendedChain :public extendedLinearList<T>, public mychain<T>{
//这个C是有别于T的，所以是一对多的友元关系
template<typename C>friend bool operator==(const extendedChain<C> &left,const extendedChain<C> &right);
template<typename C>friend bool operator<(const extendedChain<C> &left,const extendedChain<C> &right);
template<typename C>friend void meld(const extendedChain<C> &a,const extendedChain<C> &b,extendedChain<C> &c);
template<typename C>friend void merge(const extendedChain<C> &a,const extendedChain<C> &b,extendedChain<C> &c);
template<typename C>friend void split(extendedChain<C> &a,extendedChain<C> &b,const extendedChain<C> &c);
public:
    //using mychain<T>::get;方法2
    extendedChain(int initialCapacity=10):mychain<T>(initialCapacity),lastNode(NULL){}
    extendedChain(const extendedChain<T> &theChain):mychain<T>(theChain){}//拷贝构造函数直接将派生类放到基类的拷贝构造函数中，可以将
    //派生类中的基类对象拷贝到基类中去.
    ~extendedChain(){}
    bool empty()const override{return this->listSize==0;}
    int size()const override{return this->listSize;}
    T &get(int theIndex) override{
        //return this->get(theIndex);这句话报错了
        //分析下上述操作报错的原因：Segmentation fault (core dumped)
        //因为在这里你使用的是this->get(theIndex)，而你是在get(theIndex)中使用的这个函数
        //那么就会因为递归调用这个函数而产生错误!!!也就是上述的报错信息。
        //方法2使用using，在你的public中首先声明
        //using mychain<T>::get;
        return mychain<T>::get(theIndex);
        //方法2是可以的。
        //方法3，直接调用mychain<T>::get(theIndex);
        //但是请注意，不用方法2，3直接调用get(theIndex)是错误的!!!为什么是这样的
        /*
        这里分析一下:
1.Parsing of a template. This phase occurs when a template definition is first seen 
by a compiler (point of definition [3]). During this phase, the lookup is completed
only for nondependent names.
2.Template instantiation. It happens when a template is instantiated, with template 
parameters substituted by the actual template arguments (point of instantiation). 
It is during this phase when the dependent names are looked up. 
上述是关于模板类的两阶段查找名字的过程。用中文描述就是:
1.模板定义阶段:刚被定义时，只有模板中独立的名字（可以理解为和模板参数无关的名字）参加查找
2.模板实例化阶段：实例化模板代码时，非独立的名字才参加查找
这个举个例子来说明一下:
#include<iostream>
using namespace std;

template<typename T>
class A
{
     public:    
	 void f() {   
	 	cout << "A::f()" << endl;    
	 }
};
template<typename T>
class B:public A<T>
{
    public:   
	void  g()
      { 
           f();//报错，这样写的话
           this->f();//A::f()
		   A<T>::f();//A::f()
      } 
};
int main(){
	B<int> b;
	b.g();
}
首先进入B的模板定义阶段，此时B的基类A<T>依赖于模板参数T，所以是一个非
独立的名字。所以在这个阶段，对于B来说A<T>这个名字是不存在的，于是A<T>::f()
也不存在。但此时这段代码仍旧是合法的，因为此时编译器可以认为f是一个非成员函数。
当稍晚些时候进入B的模板实例化时，编译器已经坚持认为f是非成员函数，纵使此时
已经可以查到A<T>::f()，编译器也不会去这么做。编译器会认为查找非成员函数没必要
去基类里面查找，所以这个时候就会找不到f了。于是就会报错。找不到f(no delcaration)。
那我们回过头来看this->f():
1.模板定义阶段:尽管没法查到A<T>::f()，但明晃晃的this->告诉编译器，f是一个成员函数
不是B类里，就是在B类的基类里，于是编译器记住了。
2.模板实例化阶段：此时编译器查找的对象是一个成员函数，首先在B中查找，没有找到
；然后在基类里查找，于是成功找到A<T>::f()。所以不会报错了
此分析来自:https://www.zhihu.com/question/31797003


         *
         */
    }
    int indexOf(const T& theElememt)const override{return mychain<T>::indexOf(theElememt);}
    void erase(int theIndex) override;
    void insert(int theIndex,const T &theElememt)override;//
    void clear()override;
    void push_back(const T& theElememt)override;
    void output(std::ostream &out)const override;

    //实例化抽象类的extendedLinearList
    //练习题新增加的功能
    void setSize(int newSize);
    void set(int theIndex,const T &theElememt);
    //这个的工作区间是[);前闭后开区间
    void removeRange(int frontIndex,int lastIndex);
    int lastIndexOf(const T& theElememt)const;
    T &operator[](int theIndex);
    void swap(extendedChain<T> &theChain);
    void leftShift(int numbers);
    void reverse();
    void meld(extendedChain<T> &a,extendedChain<T> &b);//这个函数的形式也可以写成这种形式void meld(extendedChain &a,extendedChain &b);
    void merge(extendedChain<T> &a,extendedChain<T> &b);
    void splitByIndex(extendedChain<T> &a,extendedChain<T> &b,int size);
    void circularShift(int i);
    //排序的方法
    void insertSort();//插入排序
    void bubbleSort();//冒泡排序
    void selectionSort();//选择排序
    void countingSort();//计数排序

    //因为在类的作用域内，可以不用写T
protected:
    mychainNode<T> *lastNode;
};

template<typename T> void extendedChain<T>::erase(int theIndex){
    //注意，因为加入了新的lastNode指针，所以我们在删除的时候，要记得把尾指针给移动一下
    //查看索引是不是在有效范围之内
    //下面这句话等价于this->checkIndex(theIndex);
    //extendedChain::checkIndex(theIndex);
    this->checkIndex(theIndex);
    //上面的那句话等价于mychain<T>::checkIndex(theIndex);
    mychainNode<T> *deletedNode = NULL;

    //如果有效的话，
    if(theIndex == 0){//如果是在第一个位置删除的话，那么需要
        deletedNode = this->firstNode;
        //等价于deletedNode = mychain<T>->firstNode;
        //等价于mychain<T>::firstNode = deletedNode->next;
        this->firstNode = deletedNode->next;
    }
    else{

        mychainNode<T> *p = this->firstNode;
        for(int i = 0; i != theIndex -1; ++i)
            p = p->next;
        deletedNode = p->next;
        p->next = deletedNode->next;
        if(deletedNode == lastNode)
            lastNode = p;
    }
    this->listSize--;
    delete deletedNode;
}

template<typename T> void extendedChain<T>::insert(int theIndex,const T &theElement){
    //首先检查一下你要插入的索引是不是有效的
    if(theIndex < 0 || theIndex > this->listSize){
        std::ostringstream s;
        s<<" theIndex is "<<theIndex<<" and the listSize is "<<this->listSize;
        throw illegalParameterValue(s.str());
    }
    //如果要是索引有效的话，就继续插入
    if(theIndex == 0){
        this->firstNode = new mychainNode<T>(theElement,this->firstNode);
        if(this->listSize == 0)
            lastNode = this->firstNode;//现在firstNode指向的是第一个节点，所以你的lastNode也指向该节点
        //如果不等于0的话，此时lastNode已经指向尾节点了，所以不需要改变
    }
    else{//如果索引不是等于0的话
        mychainNode<T> *p = this->firstNode;
        for(int i = 0; i != theIndex-1;++i)
            p = p->next;
        //现在p指向你要插入位置的前一个位置了
        p->next = new mychainNode<T>(theElement,p->next);
        if(this->listSize == theIndex)
            lastNode = p->next;//如果是在尾后插入的话，你需要把尾后lastNode转移一下。往后移动一下
    }
    this->listSize++;
}

template<typename T> void extendedChain<T>::clear(){
    mychainNode<T> *p = NULL;
    while(this->firstNode != NULL){
        p = this->firstNode->next;//指向firstNode的下一个节点
        delete this->firstNode;//删除firstNode指向的节点
        this->firstNode = p;//将firstNode指向原先的firstNode的下一个节点
    }
    this->listSize=0;
    lastNode = NULL;
}

template<typename T> void extendedChain<T>::push_back(const T& theElement){
    mychainNode<T> *newNode = new mychainNode<T>(theElement,NULL);
    if(this->firstNode == NULL){//也就是本来这个链表是空的话，listSize==0的时候
        this->firstNode = lastNode = newNode;
    }
    else{
        lastNode->next = newNode;
        lastNode = newNode;
    }
    this->listSize++;
}

template<typename T> void extendedChain<T>::output(std::ostream &out)const{
    mychain<T>::output(out);
    //this->output();//会发生内存溢出，因为会递归调用
}


template<typename T> std::ostream &operator<<(std::ostream &out,const extendedChain<T> &x){
    x.output(out);
    return out;
}

template<typename T> void extendedChain<T>::setSize(int newSize){
    if(newSize < this->listSize){//如果新的大小小于原先的大小
        //则删除多余的元素
        while(this->listSize != newSize)
            this->erase(newSize);//lastNode已经在erase中处理了
    }
    //如果大于listSize，那么不改变
}

template<typename T> void extendedChain<T>::set(int theIndex,const T& theElememt){
    this->checkIndex(theIndex);
    mychainNode<T> *p = this->firstNode;
    for(int i = 0; i != theIndex;++i)
        p = p->next;
    p->element = theElememt;
}

template<typename T> void extendedChain<T>::removeRange(int frontIndex,int lastIndex){
    if(frontIndex <0 || frontIndex>=this->listSize || frontIndex >= lastIndex){
        std::ostringstream s;
        s<<"the range is wrong"<<std::endl;
        throw illegalParameterValue(s.str());
    }
    //如果范围正确的话，那就开始删除
    int deletedIndex = frontIndex;
    while(frontIndex++ != lastIndex){
        this->erase(deletedIndex);//lastNode已经在erase中被处理了
    }
}

template<typename T> int extendedChain<T>::lastIndexOf(const T &theElememt)const{
    int index=0,i=0;
    bool flag=0;
    mychainNode<T> * p = this->firstNode;
    while( p != NULL ){
        if(p->element == theElememt){
            index = i;
            flag=1;
        }
        i++;p = p->next;
    }
    return flag==0 ? -1 : index;
}

template<typename T> T& extendedChain<T>::operator[](int theIndex){
    //通过这个方法的重写，可以看出，在vector以及list中[]仅仅是改变现有的元素的
    //值的。但是不能用其新建一个元素，包括数组都是一样的，[]仅仅是用来改变和
    //查找元素的，但是不能用来新建一个元素的
    mychainNode<T> *p = this->firstNode;
    for(int i = 0;i != theIndex;i++)
        p = p->next;
    return p->element;
}

template<typename T> bool operator==(const extendedChain<T> &left,const extendedChain<T> &right){
    mychainNode<T> *pLeft = left.mychain<T>::firstNode,*pRight = right.mychain<T>::firstNode;
    if(left.size() != right.size())//这个可以解决如果两个很长的链表他们有很大一部分相同，那么我们就要查好久，这样会浪费很多时间
    //所以加一个长度比较可以防止出现这种极端的情况。
        return false;
    //left.mychain<T>::begin(); 
    //std::cout<<"the left is "<<left<<"\nand the right is "<<right<<std::endl;
    while(pLeft != NULL && pRight != NULL){
        if(pLeft->element != pRight->element)//如果有一个不相等直接返回false
            return false;
        else{//如果到目前为止，元素一直相等，那么我们就继续比较
            pLeft = pLeft->next;pRight = pRight->next;
            //std::cout<<"left is "<<left.get(i)<<" and right is "<<right.get(i)<<std::endl;
        }
    }
    if(pLeft == NULL && pRight == NULL)
        return true;
    else
        return false;
}

template<typename T> bool operator!=(const extendedChain<T> &left,const extendedChain<T> &right){
    return !(left==right);
}

template<typename T> bool operator<(const extendedChain<T> &left,const extendedChain<T> &right){
    mychainNode<T> *pLeft = left.mychain<T>::firstNode,*pRight = right.mychain<T>::firstNode;

    int iShortLength = std::min(left.size(),right.size());
    int i = 0;
    //如果相等的话，我就直接返回false
    if(left == right)
        return false;
    //如果不相等的话，我就判断是不是小于或者大于了
    while(i < iShortLength){
        if(pLeft->element > pRight->element)//因为不相等了，所以一旦遇见一个>我们就直接返回false
            return false;
        else if(pLeft->element <= pRight->element){//如果到目前为止，元素一直小于等于，那么我们就继续比较
            pLeft = pLeft->next;pRight = pRight->next;
            i++;
        }
    }
    //运行到这一步的是，就说明短的那个是比长的那个链表小了
    return (( left.size() <= right.size() ) ? true : false);

}

template<typename T> void extendedChain<T>::swap(extendedChain<T> &theChain){
    mychainNode<T> *tmp = this->firstNode;//保留该链表的头结点
    //上面的语句等价于mychainNode *tmp = this->firstNode
    //在类的作用域内类名可以不用加<T>
    this->firstNode = theChain.mychain<T>::firstNode;//将本地的头节点指针转换到传入的链表的头结点中去
    theChain.mychain<T>::firstNode = tmp;//交换
    int length = this->listSize;
    this->listSize = theChain.mychain<T>::listSize;
    theChain.mychain<T>::listSize = length;
}

template<typename T> void extendedChain<T>::leftShift(int numbers){
    for(int i = 0; i != numbers;++i)
        erase(0);//lastNode已经在erase中被处理了
}

template<typename T> void extendedChain<T>::reverse(){
    //原地进行翻转，其实就是两个元素进行交换
    int midIndex = (this->listSize + 1)/2;
    T tmp;
    for(int i = 0; i != midIndex; ++i){
        std::swap(get(i),get(this->listSize-1-i));
        /*
        tmp = get(i);
        set(i,get(this->listSize-1-i));
        set(this->listSize-i-1,tmp);//这个没有涉及node节点的倒置，只是
        */
        //节点中的element被倒置，所以不需要处理lastNode;
    }
}

template<typename T> void reverseNoMember(extendedChain<T> &a){
    a.reverse();
}

template<typename T> void meld(const extendedChain<T> &a,const extendedChain<T> &b,extendedChain<T> &c){
    c.clear();//如果c是非空的，我们首先需要把所有的原先的节点给删除掉
    int iShortLength = std::min(a.size(),b.size()),i = 0;
    c.mychain<T>::firstNode = new mychainNode<T>(a.mychain<T>::firstNode->element);
    mychainNode<T> *pa = a.mychain<T>::firstNode->next;
    mychainNode<T> *pb = b.mychain<T>::firstNode->next;

    mychainNode<T> *p = c.mychain<T>::firstNode;
    p->next = new  mychainNode<T>(b.mychain<T>::firstNode->element);
    p = p->next;//已经添加了两个节点了
    while(i++ != iShortLength-1){
        p->next = new mychainNode<T>(pa->element);
        p = p->next;
        p->next = new mychainNode<T>(pb->element);
        p = p->next;
        pa = pa->next;
        pb = pb->next;
    }
    while(pa != NULL){
        p->next = new mychainNode<T>(pa->element);
        p = p->next;
        pa = pa->next;
    }
    while(pb != NULL){
        p->next = new mychainNode<T>(pb->element);
        p = p->next;
        pb = pb->next;
    }
    //注意，上面的写法还有一种就是类似我在下面的meld中写的一样的!!!
    c.lastNode = p;//处理下尾指针
    p->next = NULL;
    c.mychain<T>::listSize = a.size() + b.size();
}

template<typename T> void extendedChain<T>::meld(extendedChain<T> &a,extendedChain<T> &b){
    int iShortLength = std::min(a.size(),b.size()),i=0;
    this->clear();//先把原先所有的节点给清除掉
    /*
    this->firstNode = a.mychain<T>::firstNode;
    mychainNode<T> *p = this->firstNode;//让p指向本对象的firstNode
    //然后让本地的firstNode指向a的第一个节点
    //pa和pb都指向a和b的头结点的下一个位置，为的是让可以让别人找到这个节点
    mychainNode<T> *pa = a.mychain<T>::firstNode->next;
    mychainNode<T> *pb = b.mychain<T>::firstNode->next;
    p->next = b.mychain<T>::firstNode;//到这一步，已经进行了两个节点的合并了
    p = p->next;//合并完了
    while(i++ != (iShortLength-1)){
        std::cout<<"\n 进入了while循环中";
        a.mychain<T>::firstNode = pa;//得到最新的头结点
        b.mychain<T>::firstNode = pb;
        
        pa = pa->next;//保留好下一个节点的位置
        pb = pb->next;

        //将两个链表当前的头结点进行合并
        p ->next = a.mychain<T>::firstNode;
        p = p->next;
        p->next = b.mychain<T>::firstNode;
        p = p->next;
    }
    */
    //这是第二种方法
    int index = 0;
    this->firstNode    = a.mychain<T>::firstNode;
    mychainNode<T> *p  = this->firstNode;

    mychainNode<T> *pa = a.mychain<T>::firstNode->next;
    mychainNode<T> *pb = b.mychain<T>::firstNode;

    while(pa != NULL && pb != NULL){
        if(index % 2 == 0){//用来表示每次插入的位置
            p->next = pb;
            p = p->next;
            pb = pb->next;
        }
        else{
            p->next = pa;
            p = p->next;
            pa = pa->next;
        }
        index++;
    }
    if(pa != NULL){//如果链表a还有元素的话
        p->next = pa;
        lastNode = a.lastNode;
    }else if(pb != NULL){
        p->next = pb;
        lastNode = b.lastNode;
    }
    this->listSize = a.size() + b.size();
    a.mychain<T>::firstNode = NULL;
    b.mychain<T>::firstNode = NULL;
    a.mychain<T>::listSize = b.mychain<T>::listSize = 0;
}

template<typename T> void merge(const extendedChain<T> &a,const extendedChain<T> &b,extendedChain<T> &c){
    //注意a和b都是有序的链表
    //先c本身所拥有的全部节点给删除掉
    c.clear();
    mychainNode<T> *pa = a.mychain<T>::firstNode;
    mychainNode<T> *pb = b.mychain<T>::firstNode;
    //注意，对于空的firstNode，千万不能写成这样的
    //mychainNode<T> *p = this->firstNode;因为这样的话，p仅仅是和
    //firstNode指向的位置一样，但是p->next = otherP;那么我的firstNode是没改变的
    //只有firstNode是有值的时候，才是可以的，也就是对于这种合并的，我们
    //必须先确保this->firstNode是有值的才可以。
    if(pa->element <= pb->element){
        c.mychain<T>::firstNode = new mychainNode<T>(pa->element);
        pa = pa->next;
    }
    else{
        c.mychain<T>::firstNode = new mychainNode<T>(pb->element);
        pb = pb->next;
    }
    mychainNode<T> *p  = c.mychain<T>::firstNode;
    while(pa != NULL && pb != NULL){
        if(pa->element <= pb->element){
            p->next = new mychainNode<T>(pa->element);
            p = p->next;
            pa = pa->next;
        }
        else{
            p->next = new mychainNode<T>(pb->element);
            p = p->next;
            pb = pb->next;
        }
    }
    /*
    while(pa != NULL && pb != NULL){
        //前插法
        //c.mychain<T>::firstNode = new mychainNode<T>(pa->element,c.mychain<T>::firstNode);
        if(pa->element <= pb->element){//前插法,所以需要到最后倒转一下
            c.mychain<T>::firstNode = new mychainNode<T>(pa->element,c.mychain<T>::firstNode);            
            pa = pa->next;
        }
        else{
            c.mychain<T>::firstNode = new mychainNode<T>(pb->element,c.mychain<T>::firstNode);
            pb = pb->next;
         }
    }
    
    注意使用本方法的时候需要在结尾加个翻转的工作，因为这是使用前插法的方法去插入元素的
    */


    //如果一个链表的元素都取完了，那么剩下的就是把没有遍历完的给合并了
    while(pa != NULL){
        p->next = new mychainNode<T>(pa->element);
        p = p->next;
        pa = pa->next;
    }
    while(pb != NULL){
        p->next = new mychainNode<T>(pb->element);
        p = p->next;
        pb = pb->next;
    }
    c.lastNode = p;
    c.mychain<T>::listSize = a.size() + b.size();
}

template<typename T> void extendedChain<T>::merge(extendedChain<T> &a,extendedChain<T> &b){
    this->clear();//先把原先的成员的节点给删除掉
    //这个需要我们不去单独创建新的节点，而是利用a和b的节点去做
    //先让pa和pb分别指向a和b的头结点
    mychainNode<T> *pa = a.mychain<T>::firstNode,*pb = b.mychain<T>::firstNode;
    //然后让c的第一个指针指向两个链表的最小的那个
    if(a.mychain<T>::firstNode->element <= b.mychain<T>::firstNode->element){
        this->firstNode = a.mychain<T>::firstNode;
        pa = pa->next;   
    }else {
        this->firstNode = b.mychain<T>::firstNode;
        pb = pb->next;
    }   
    mychainNode<T> *p  = this->firstNode;
    while(pa != NULL && pb != NULL){
        if(pa->element <= pb->element){
            p->next = pa;
            p = p->next;
            pa = pa->next;
        }else{
            p->next = pb;
            p = p->next;
            pb = pb->next;
        }
    }
    if(pa != NULL ){
        p->next = pa;
        lastNode = a.lastNode;
    }else{
        p->next = pb;
        lastNode = b.lastNode;
    }
    this->listSize = a.size() + b.size();
    a.mychain<T>::firstNode = NULL;
    b.mychain<T>::firstNode = NULL;
    a.mychain<T>::listSize = b.mychain<T>::listSize = 0;
}

template<typename T> void split(extendedChain<T> &a,extendedChain<T> &b,const extendedChain<T> &c){
    a.clear();b.clear();//首先不管a和b是不是空，我们都要给它清空
    mychainNode<T> *p  = c.mychain<T>::firstNode;
    a.mychain<T>::firstNode = new mychainNode<T>(p->element);
    p = p->next;
    mychainNode<T> *pa = a.mychain<T>::firstNode;//a是奇数项

    b.mychain<T>::firstNode = new mychainNode<T>(p->element);
    p = p->next;
    mychainNode<T> *pb = b.mychain<T>::firstNode;
    
    int index = 0;
    while(p != NULL){
        if(index % 2 == 0){
            pa->next = new mychainNode<T>(p->element);
            pa = pa->next;
            p = p->next;
        }else{
            pb->next = new mychainNode<T>(p->element);
            pb = pb->next;
            p = p->next;
        }
        index++;
    }
    a.lastNode = pa;
    b.lastNode = pb;
    a.mychain<T>::listSize = (c.mychain<T>::listSize + 1)/2;//奇数项
    b.mychain<T>::listSize = (c.mychain<T>::listSize + 1)/2;//偶数项
}

template<typename T> void extendedChain<T>::splitByIndex(extendedChain<T> &a,extendedChain<T> &b,int size){
    a.clear();b.clear();//不管a和b是不是空的，都给清空
    a.mychain<T>::firstNode = new mychainNode<T>(this->firstNode->element);

    mychainNode<T> *pa = a.mychain<T>::firstNode;
    mychainNode<T> *p  = this->firstNode->next;
    int index = 0;
    while(index++ != size-1){
        pa->next = new mychainNode<T>(p->element);
        p = p->next;
        pa = pa->next;
    }//到了这一步，已经把前size个元素分配给a了
    b.mychain<T>::firstNode = new mychainNode<T>(p->element);
    p = p->next;
    mychainNode<T> *pb = b.mychain<T>::firstNode;
    while(p != NULL){
        pb->next = new mychainNode<T>(p->element);
        p = p->next;
        pb = pb->next;
    }

    a.lastNode = pa;b.lastNode = pb;
    a.mychain<T>::listSize = size;b.mychain<T>::listSize = this->mychain<T>::listSize - size;
}

template<typename T> void extendedChain<T>::circularShift(int i){
    //circularShift其实就是三次倒置而已
    //先把本对象分成两个，然后各自倒置，再合并一下就好了
    extendedChain<T> a;extendedChain<T> b;
    this->reverse();//先倒置
    this->splitByIndex(a,b,this->size()-i);
    a.reverse();b.reverse();//把a和b倒置
    std::cout<<"a is "<<a<<" and b is "<<b<<std::endl;
    mychainNode<T> *pa = a.mychain<T>::firstNode;
    mychainNode<T> *pb = b.mychain<T>::firstNode;
    mychainNode<T> *p = this->firstNode;
    while(pa != NULL){
        p->element  = pa->element;
        p = p->next;
        pa = pa->next;
    }
    while(pb != NULL){
        p->element = pb->element;
        p = p->next;
        pb = pb->next;
    }
    //因为我们只是改的值，没有动节点，所以不需要改变大小和lastNode节点

}
//插入排序的时间复杂度是O(n2) = 3*(n+1)*n/2
//其实就是插入到有序的链表中去就是普通的插入排序的思路
//插入排序的时间复杂度
template<typename T> void extendedChain<T>::insertSort(){
    mychainNode<T> *insertElement = this->firstNode->next;//这个表示用来插入的节点的
    while(insertElement != NULL){
        mychainNode<T> *p = this->firstNode;
        while(p->element <= insertElement->element && p != insertElement){
            p = p->next;//如果小于的了的话，那么就一直往右查找
        }//已经找到了要改变的元素的位置了
        //第一个while循环是用来查找要插入的位置的 
        //第二个while循环是用来改变当前链表中的元素的值的
        while(p != insertElement){
            /*
            //自己写的swap功能
            T tmp;
            //通过将当前的位置节点的元素的值与最后一个位置进行
            //交换，就是把最后一个节点当做是一个中转的，然后让
            //所有的元素都与这个进行交换
            tmp = p->element;
            p->element = insertElement->element;
            insertElement->element = tmp;
            */
            std::swap(p->element,insertElement->element);//利用标准库函数的swap函数
            p = p->next;
        }    
        insertElement = insertElement->next;
    }
}
//冒泡排序的时间复杂度是O(n2) = 3*(n+1)*(n)/2
template<typename T> void extendedChain<T>::bubbleSort(){
    //冒泡的话，我们就直接找两个尾节点就好了
    mychainNode<T> *lastNodeOfChain = lastNode;
    mychainNode<T> *tmp=NULL;
    while(this->firstNode != lastNodeOfChain){//这个是表示的是我从最长的链表到最小的链表
        mychainNode<T> *p = this->firstNode;//这个是用来从头到尾去遍历当前的链表的
        while(p != lastNodeOfChain){//去遍历当前这个链表
            if(p->element > p->next->element){
                std::swap(p->element,p->next->element);//如果左边的大，那么我们就交换
            }
            if(p->next == lastNodeOfChain){
                tmp = p;//保留当前尾节点的前一个位置，用来作为下一次遍历的链表的尾节点
            }
            p = p->next;
        }
        lastNodeOfChain = tmp;
    }
}
//选择排序算法
//算法思想主要是先找出本链表中最大的一个节点，然后放到最后
//依次缩短链表就可以得出
//时间复杂度为O(n2)
template<typename T> void extendedChain<T>::selectionSort(){
    mychainNode<T> *lastNodeOfChain = lastNode;
    mychainNode<T> *tmp=NULL;
    while(this->firstNode != lastNodeOfChain){//这个是表示的是我从最长的链表到最小的链表
        mychainNode<T> *p = this->firstNode;//这个是用来从头到尾去遍历当前的链表的
        mychainNode<T> *Max = this->firstNode;//这个是用来保存当前链表中最大的元素
        while(p != lastNodeOfChain){//去遍历当前这个链表
            if(p->element > Max->element){
                Max = p;//保留较大的成员
            }
            if(p->next == lastNodeOfChain){
                tmp = p;//保留当前尾节点的前一个位置，用来作为下一次遍历的链表的尾节点
            }
            p = p->next;
        }
        std::swap(Max->element,lastNodeOfChain->element);
        lastNodeOfChain = tmp;
    }
}

template<typename T> void extendedChain<T>::countingSort(){
    //首先需要借助一个数组去存储相应的名次信息
    //分两步去实现，第一步是先建立好相应的元素的名称信息
    int *res = new int[this->listSize];//res是用来保存各个元素的名次信息的
    int currentIndex = 0;
    for(int i = 0; i != this->listSize; i++)
        res[i] = 0;
    mychainNode<T> *currentHead = this->firstNode;
    mychainNode<T> *lastNodeOfChain = lastNode;
    mychainNode<T> *tmp = NULL;
    int index = 0;
    while(currentHead != lastNodeOfChain){//控制链表的长度
        mychainNode<T> *p = currentHead;
        currentIndex = index+1;
        while(p != lastNodeOfChain){//遍历当前的链表
            if(currentHead->element >= p->next->element)
                res[index]++;
            else
                res[currentIndex]++;
            currentIndex++;
            p = p->next;
        }
        currentHead = currentHead->next;
        index++;
    }
    //通过上面的步骤已经得到了各个节点元素对应的名次的位置信息了
    for(int i = 0; i != this->listSize;++i){
        while(res[i] != i){//加这个判读可以避免相等的时候重复进行swap操作
            std::swap(get(i),get(res[i]));
            std::swap(res[i],res[res[i]]);        
        }    
    }

} 
#endif
