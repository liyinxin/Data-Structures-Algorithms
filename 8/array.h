#pragma once
#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <iostream>
#include <sstream>//注意:ostringstream是在sstream中的
#include <iterator>
#include <typeinfo>
#include <cxxabi.h>
#include <string>
#include <algorithm>

//这是一个抽象基类
/*
   抽象数据类型linearList{
    实例:
        有限个元素的有序集合
    操作:
        empty();若表空，返回true了；否则返回false
        size():返回线性表的大小（表的元素个数）
        get(index):返回线性表中索引为index的元素
        indexOf(x):返回线性表中第一次出现的x的索引。若x不存在，则返回-1
        erase(index):删除索引为index的元素，索引大于index的元素其索引减一
        insert(index,x):将x插入线性表中索引为index的位置上，索引大于index的元素其索引加一
        output(cout):从左到右输出表元素
   }
 */
extern const std::string getClearName(const char  *name);
template<typename T> class linearList{
public:
    virtual ~linearList(){}
    virtual bool empty()const =0;
    virtual int size()const =0;
    virtual T& get(int theIndex)const =0;
    virtual int indexOf(const T& theElement)const =0;
    virtual void erase(int theIndex) =0;
    virtual void insert(int theIndex,const T& theElement)=0;
    virtual void output(std::ostream &out)const =0;

};
template<typename T>class arrayList : public linearList<T>{
public:
    //构造函数，拷贝构造函数和析构函数
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T> &);

    ~arrayList(){}

    //ADT的纯虚函数方法
    bool empty()const override{return listSize == 0;}
    int size()const{return listSize;}
    T &get(int theIndex)const;
    int indexOf(const T& theElement)const override;
    void erase(int theIndex);
    void insert(int theIndex,const T &theElement);
    void output(std::ostream &out)const;

    //新增的方法
    int capacity()const{
        return arrayLength;
    }
    /*
     首先说明一下，在类(A)中嵌套类(B)的定义。两个类都是相互独立的。类A
     和类B是相互独立的。类A是不能访问类B的，同理类B也是不能访问类A的。
     所以两者之间的桥梁就是将类A的成员传递给类B，然后类B使用类A
     传进来的成员进行二次的开发使用。
     接下来就能看到类arrayList<T>是如何被iterator访问的。我们发现在类
     arrayList<T>中定义了两个成员函数begin()和end()。但是注意这两个成员
     的返回类型是iterator也就是类的对象。所以我们可以继续使用这个对象的
     方法去进行一些操作。比如说*(array3.begin())就是表示的是array3[0]
     *
     *
     *
     */
    class iterator{
    public:
        //用C++的typedef语句实现双向迭代器
        //typedef type anothername
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        //构造函数
        iterator(T *thePosition = 0):position(thePosition){}

        //解引用操作符
        T &operator*()const{return *position;}
        T *operator->()const{return &*position;}

        //迭代器的值增加
        iterator &operator++(){//前增加
            ++position;
            return *this;
        }
        iterator &operator++(int){//后加
            iterator old = *this;
            ++position;
            return old;
        }
        //迭代器的减少
        iterator &operator--(){//前减
            --position;
            return *this;
        }
        iterator &operator--(int){//后减
            iterator old = *this;
            --position;
            return old;//其实后加/减都增加或至少了迭代器，只不过返回的结果是
                      //原先的对象而已，
        }
        //测试是否相等
        bool operator!=(const iterator &right)const{
            return position != right.position;
        }
        bool operator==(const iterator &right)const{
            return position == right.position;
        }
    protected:
        T *position;
    };
    iterator begin(){
        return iterator(element);
    }
    iterator end(){
        return iterator(element + listSize);
    }

    //习题新增加的功能
    void trimToSize();//将arrayLength - listSize之间的空间给删掉
    void setSize(int newLength);
    T &operator[](int index);
    const T &operator[](int index)const;//常量对象的返回的是常量的变量
    void push_back(const T &theElement);//在线性表右端插入一个元素
    void pop_back();//输出最后一个元素
    void swap(arrayList<T> &theList);//跟theList进行交换
    //void changArrayLength(int newArrayLength);
    //void changListSize(int newListSize);
    //T *&getElement();
    T set(int theIndex,const T &theElement);//用元素theElement替换索引为theIndex的元素
    void reserve(int theCapacity);//把数组的容量改变为当前容量和theCapacity中
    //较大者
    void clear();//清楚element指向的元素空间也被删除了
    void removeRange(int start,int end);//将start--end这个序列从element指向的序列中删除
    int lastIndexOf(const T &theElement)const;//返回theElement在该序列中的最后一个位置，如果不存在则返回-1
    void reverse();//原地倒序翻转
    void leftShift(int index);//仅仅是把左边部分给移除去
    void circularShift(int index);//循环移位，
    void half();//将线性表的元素隔一个删除一个
    void meld(const arrayList<T> &a,const arrayList<T> &b);
    void merge(const arrayList<T> &a,const arrayList<T> &b);
    void split(arrayList<T> &a,arrayList<T> &b);

private:
    int listSize;//线性表的元素个数
    int arrayLength;//一维数组的容量
    void checkIndex(int theIndex)const;//如果索引无效的话，则抛出异常
    T *element;//存储线性表示元素的一维数组

};


const std::string getClearName(const char  *name){
    int status = 1;
    char *clearName = abi::__cxa_demangle(name,NULL,NULL,&status);
    const char *const demangledName = (status == 0) ? clearName : name;
    std::string ret_val(demangledName);
    free(clearName);
    return ret_val;
}
class illegalParameterValues : public std::length_error{
public:
    explicit illegalParameterValues(const std::string &s):length_error(s){}
    
};
template<typename T>void changeLength1D(T* &a,int oldLength,int newLength){
    //第一个参数必须是引用，这样才可能使a可以去修改实参的指向的地址
    if(newLength <0 )
        throw illegalParameterValues("new length must be >= 0");
    T* temp = new T[newLength];  
    //这个changeLength的作用是，比方以前我的数组大小是5,现在新的长度
    //是10，那好，我直接复制原先的动态数组给新的动态数组就好了，注意
    //这个时候的number是小的，也就是oldLength
    //如果我的新的长度是3，那么我就得将原先的动态数组的前三个复制到
    //新的动态数组中，这个时候我的number也是小的。所以我们必须取小的
    //长度来进行复制拷贝。主要是为了防止我在拷贝原先的动态数组的时候
    //出现访问位置的越界。
    int number = std::min(oldLength,newLength);
    std::copy(a,a+number,temp);//copy函数将一个序列的范围拷贝给第三个参数代表的序列中
    delete []a;//释放掉原先的内存
    a = temp;//将a指向新的内存中去
}
template<typename T> void changeLength2D(T** &a,int oldRows,int copyRows,int copyColumns,int newRows,int newColumns){
    //注意，第一个参数必须是引用!!!
    //这个表示的是改变二维数组的大小的程序,
    //newRows表示的是新的是多少行，而newColumns是新二维数组是多少列
    //copyRows表示的是要复制多少行，copyCloumns表示的是复制多少列
    if(copyRows > newRows || copyColumns > newColumns)
         throw illegalParameterValues("new dimensions are too small");
    T **tmp = new T*[newRows];//T指向的是一个数组的指针（也就是一个而为指针)
    //表示的是数组的大小是newRows,也就是表示有多少行
    for(int i = 0; i != newRows; ++i){
        tmp[i] = new T[newColumns];
    }
    //copy from old space to new spacemm,delete old space
    for(int i = 0; i != copyRows;++i){
        std::copy(a[i],a[i]+copyColumns,tmp[i]);
        delete [] a[i];
    }
    //delete remaining rows of a
    for(int i = copyRows; i != oldRows;++i){
        delete [] a[i];
    }
    delete [] a;
    a = tmp;
}
template<typename T>void arrayList<T>::checkIndex(int theIndex)const{
    if(theIndex<0 || theIndex >= listSize)//这个判断条件是保证theIndex在有元素的范围之内
        throw illegalParameterValues("the index must be >=0 and < listSize");
}
template<typename T> T& arrayList<T>::get(int theIndex)const{
    checkIndex(theIndex);//先检查下下标是否在索引范围之内
    return element[theIndex];
}
template<typename T> int arrayList<T>::indexOf(const T& theElement)const{
    //返回元素theElement第一次出现时的索引
    //若该元素不存在，则返回-1
    //查找元素theElement
    /*
     *template <class InputIterator, class T> InputIterator find (InputIterator first, InputIterator last, const T& val);
     *find是从[first,last)之间查找你想要查找的参数的。也就是说，如果
     *没有查找到的话，那么就会返回last这个迭代器的位置。
     */
    //std::cout<<"the element type is"<<getClearName(typeid(element).name())
    //<<std::endl;
    //注意,使用标准库的函数，一定要写#include，我在这个吃了个大亏。
    //比如，你要使用find函数，你就得包含algorithm头文件才可以，要不然会报错
    int theIndex = (int)(std::find(element,element+listSize,theElement)-element);
    if(theIndex == listSize)
        return -1;
    return theIndex;
}
//构造函数的实现部分
template<typename T> arrayList<T>::arrayList(int initialCapacity):arrayLength(initialCapacity),listSize(0){
    //注意，当你的成员函数在类内有默认实参的时候，那么在类外实现的时候，一定不要再写上默认实参的值了
    if(initialCapacity<1){
        std::ostringstream s;
        s << "Initial capacity = "<<initialCapacity << "Must be > 0";
        throw illegalParameterValues(s.str());
    }
    element = new T[arrayLength];
}
template<typename T> arrayList<T>::arrayList(const arrayList<T> &theList){
    //拷贝构造函数
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    delete []element;//删除原先的内存空间
    element = new T[arrayLength];
    std::copy(theList.element,theList.element+listSize,element);
}
//erase的下标是真正想要删除的动态数组的下标的
template<typename T> void arrayList<T>::erase(int theIndex){
    checkIndex(theIndex);//首先判断该索引是否有效
    std::copy(element+theIndex+1,element+listSize,element+theIndex);
    element[--listSize].~T();//析构一个存放元素的内存,并且改变
    //数组中元素的个数.这个的原理是将要删除的元素拷贝到当前的位置
    //然后把最后一个位置的元素删除掉就好了，因为最后一个位置的元素
    //没有了。
}
template<typename T> void arrayList<T>::insert(int theIndex,const T& theElement){
    //在索引theIndex处插入元素theElement
    if(theIndex < 0 || theIndex > listSize){
        //无效索引
        std::ostringstream s;
        s << "index = " <<theIndex<<" size = "<<listSize;
        throw illegalParameterValues(s.str());
    }
    //有效索引，确定数组是否已满
    if(listSize == arrayLength){
        changeLength1D(element,arrayLength,2*arrayLength);
        arrayLength *= 2;//改变你的数组的长度大小
    }
    //把元素向右移动一个位置
    std::copy_backward(element+theIndex,element+listSize,element+listSize+1);
    //倒叙拷贝
    element[theIndex] = theElement;//插入到相应的位置
    listSize++;
}
template<typename T> void arrayList<T>::output(std::ostream &out)const{
    std::copy(element,element+listSize,std::ostream_iterator<T>(out,", "));
    //注意,这个ostream_iterator是包含在iterator中的，需要包含这个头文件
}
template<typename T> std::ostream &operator<<(std::ostream &out,const arrayList<T> &x){
    x.output(out);
    return out;
}
//这些功能是习题中新增加的


template<typename T> void arrayList<T>::trimToSize(){
    if(listSize == arrayLength)
        return;//如果数组被填满了，那么就不用精简数组了

    int newlength = std::max(1,listSize);
    changeLength1D(element,listSize,newlength);
    arrayLength = newlength;

}

template<typename T> void arrayList<T>::setSize(int newLength){
    //如果设置的新的数组的长度大于原先的数组的长度的话，我们直接保留
    //原先数组中的元素，只是让数组的长度增加就好了
    if(arrayLength <= newLength){
        changeLength1D(element,arrayLength,newLength);
        arrayLength = newLength;
        //不需要改变动态数组的listSize
    }
    else{
        changeLength1D(element,arrayLength,newLength);
        arrayLength = listSize = newLength;
    }
}

template<typename T> T &arrayList<T>::operator[](int index){
    checkIndex(index);
    return element[index];
}

template<typename T> const T &arrayList<T>::operator[](int index)const{
    checkIndex(index);
    return element[index];
}

template<typename T> bool operator==(const arrayList<T> &lhs,const arrayList<T> &rhs){
    int index = 0;
    if(lhs.size() != rhs.size())
        return false;
    for(;index != lhs.size();++index)
        if(lhs[index] != rhs[index])
            return false;
    return true;
}

template<typename T> bool operator!=(const arrayList<T> &lhs,const arrayList<T> &rhs){
    return !(lhs == rhs);
}

template<typename T> bool operator<(const arrayList<T> &lhs,const arrayList<T> &rhs){
    int index = 0;
    if(lhs.size() < rhs.size())//如果左边的listSize小于右边的listSize
        return true;
    else if(lhs.size() > rhs.size())//如果左边的listSzie大于右边的listSize
        return false;
    else{//如果两个的listSize一样的话，我们要按照字典顺序去比较了
        for(;index != lhs.size();++index){
            if(lhs[index] < rhs[index])
                return true;
        }
    }
    return false;
}
template<typename T> void arrayList<T>::push_back(const T &theElement){
    //注意，在任何插入数据的时候，都需要首先判断下listSize和arrayLength是否一样
    //如果一样的话，说明这次分配的内存空间已经被使用完了，需要改变下内存了
    if(listSize == arrayLength){
        changeLength1D(element,arrayLength,arrayLength * 2);
        arrayLength *= 2;
    }//分配完空间以后，直接在listSize上插入一个元素即可
    element[listSize++] = theElement;
}

template<typename T> void arrayList<T>::pop_back(){
    element[--listSize].~T();
}

/*
template<typename T> void arrayList<T>::changArrayLength(int newArrayLength){
    arrayLength = newArrayLength;
}
template<typename T> void arrayList<T>::changListSize(int newListSize){
    listSize = newListSize;
}
template<typename T> T *&arrayList<T>::getElement(){
    return element;
}
*/


template<typename T> void arrayList<T>::swap(arrayList<T> &theList){
    //注意，在类的作用域中（可以是成员函数中），可以通过类的不同对象去访问
    //类的私有成员以及保护成员的。但是在类外的作用域中，是无法通过类的对象
    //去访问类的私有成员的!!!这个跟友元一样。只要是在类的作用域内，我就可以
    //通过不同的对象去访问类的私有成员和保护成员的。但是一定要注意，一定是在
    //类的作用域之内才可以!!!
    std::swap(arrayLength,theList.arrayLength);
    std::swap(listSize,theList.listSize);
    std::swap(element,theList.element);
    std::cout<<"in the class's function member we can use the protected member "<<theList.listSize<<std::endl;
    /*
    int tempArrayLength = arrayLength;
    arrayLength = theList.capacity();
    theList.changArrayLength(tempArrayLength);//交换了两者的数据的总长度
    
    int tempListSize = listSize;
    listSize = theList.size();
    theList.changListSize(tempListSize);//交换了两者的数据的元素的长度
    
    T *temp = element;
    element = theList.getElement();
    theList.getElement() = temp;
    */
}
template<typename T> void arrayList<T>::reserve(int theCapacity){
    int newArrayLength =std::max(theCapacity,arrayLength);
    changeLength1D(element,arrayLength,newArrayLength);
    arrayLength = newArrayLength;

}
template<typename T> T arrayList<T>::set(int theIndex,const T& theElement){
    checkIndex(theIndex);
    T tmp = element[theIndex];
    element[theIndex] = theElement;
    return tmp;
}

template<typename T> void arrayList<T>::clear(){
    //for(int i = 0; i != listSize;++i)注意不能这样写，因为listSize也会被erase
    //改变的，所以我们必须建立一个临时的变量去把最开始的listSize接受一下，用它
    //来进行循环控制
    int oldListSize = listSize;
    for(int i = 0; i != oldListSize; ++i)
        erase(0);//把第一个一直删除listSize就好了
}
//这个删除的范围是[a,b)
template<typename T> void arrayList<T>::removeRange(int start,int end){
    if(start >= end)//首先检查一下start和end的关系是不是一样的
        throw illegalParameterValues("the start must <= the end");
    checkIndex(start);//再去查看两个索引是不是符合要求的
    checkIndex(end);

    //如果符合要求了，我们进行删除相应的数据
    for(int i = start;i != end;++i)
        erase(start);
    /*下面这个是本书的作者提供的代码
     if(start < 0 || end > listSize)
        throw illegalParameterValues("index must invalid_argument")
     if(start >= end)
        return;
     //将相应的end后面的数据拷贝到start开始的位置
     copy(element+end,element+listSize,element+start);
     int newSize = listSize - end +start;
     for(int i = newSize;i < listSize; i++)//把newSize--listSize之间的元素析构掉
        element[i].~T();
     listSize = newSize;
    */
}

template<typename T> int arrayList<T>::lastIndexOf(const T& theElement)const{
    int index = 0;
    for(int i = 0; i != listSize; ++i){
        if(element[i] == theElement)
            index = i;
    }
    return (index==0)? -1 : index;
}
//这个函数的作用是倒叙排列数组
//直接使用交换的方法就可以实现倒叙排列
template<typename T> void arrayList<T>::reverse(){
    //使用swap交换函数，交换位置
    for(int i = 0,midIndex = listSize/2;i != midIndex;++i)
        std::swap(element[i],element[listSize-i-1]);
}

template<typename T> void arrayList<T>::leftShift(int index){
    if(index <= 0)
        return;
    std::copy(element+index,element+listSize,element);//将我要移动的元素
    //都拷贝到最开始的地方，然后把后面的部分给删掉就好了
    int oldListSize = listSize;
    for(;listSize != oldListSize-index;--listSize)
         element[listSize-1].~T();
}

template<typename T> void arrayList<T>::circularShift(int index){
    //循环转移利用三次倒序翻转就可以实现循环shift
    //第一次是对整个序列进行翻转；第二个是对前部分进行倒叙翻转；第三次是对
    //右边进行倒序翻转，这个左边和右边主要就是根据你要移动的个数的。
    //比如说要移动三个，那么左边就是前三个，右边就是listSize-3了
    //但是要注意在转换的时候保留原始的信息，然后再将指针指向头位置
    //以及listSize要变回原先的listSize
    reverse();//第一次reverse全部
    int leftSize = listSize - index,rightSize = index;
    auto oldElement = element;
    listSize = leftSize;//将左边的翻转
    reverse();
    element = element+leftSize;
    listSize = rightSize;
    reverse();
    listSize = leftSize + rightSize;
    element = oldElement;
}

template<typename T> void arrayList<T>::half(){
    if(listSize==0)
        return;//如果现在listSize是空的，我就直接返回不用删除
    //下面这句话可以被没被注释的一句话给替换掉
    //(listSize % 2 == 0) ? (newListSize = listSize / 2) : (newListSize = listSize / 2 + 1);
    //以后遇到这奇偶性的东西，我们可以采用+1/2的情况，因为奇数的话+1变成偶数
    //再去除2是可以等价于这个奇数除2再加1的；然后偶数的话加1是奇数，然后除2还是等价于
    //偶数除2所以这个小技巧就挺好的。
    for(int i = 1,newListSize=(listSize+1)/2;i != newListSize; ++i)
        erase(i);
    /*下面的程序是书本上的代码，可以借鉴
     * 这个算法的思想是将偶数部分的数据替换为奇数部分（也就是将紧挨的，左边的
     * 替换为右边的，然后最后把剩下的其他元素删掉，但是注意这个时候是加2走的
     for(int i = 2; i < listSize; i + 2)
       element[i/2] = element[i];
     //删除多余的空间
     int newSize = (listSize+1)/2;
     for(int i = newSize;i < listSize;++i)
        element[i].~T();
     listSize = newSize;
     */
}

//注意，这个方法使用的时候，必须本身的元素是为空的。或者小于a+b的元素
template<typename T> void arrayList<T>::meld(const arrayList<T> &a,const arrayList<T> &b){
    //因为listSize变大了，首先要去考虑下，我们的序列的长度是否可以达到装下所有的元素
    delete []element;//清空
    arrayLength = a.listSize + b.listSize;
    element = new T[arrayLength];


    int index = 1,newSize = std::min(a.listSize,b.listSize);
    std::copy(a.begin(),a.end(),element);//把左边的序列拷贝到当前数组中
    listSize = a.listSize;
    for(int i = 0;i != newSize; ++i){//第一个循环控制插入的元素的个数
        insert(index,b[i]);
        index+=2;
    }
    std::copy(b.element+newSize,(b.element+b.listSize),element+listSize);
    listSize = a.listSize + b.listSize;
}

template<typename T> void arrayList<T>::merge(const arrayList<T> &a,const arrayList<T> &b){
    int ca = 0;//a的索引
    int cb = 0;//b的索引
    int ct = 0;//本身的索引

    delete []element;//把本身的所有元素都清空
    arrayLength = a.listSize + b.listSize;//arrayLength改变成两个序列的大小
    element = new T[arrayLength];

    while((ca < a.listSize) && (cb < b.listSize)){
        if(a[ca] <= b[cb])
            element[ct++]=a[ca++];
        else
            element[ct++]=b[cb++];
    }
    //处理剩下的部分
    //也不管谁还有元素了，直接全部拷贝，没有元素的肯定拷贝的是空的
    //剩下的那个就是剩下的元素被拷贝了
    std::copy(a.element + ca,a.element+a.listSize,element+ct);
    ct += a.listSize - ca;
    std::copy(b.element + cb,b.element+b.listSize,element+ct);
    ct += b.listSize - cb;
    listSize = ct;
}

template<typename T> void arrayList<T>::split(arrayList<T> &a,arrayList<T> &b){
    int ca = 0;//a的索引
    int cb = 0;//b的索引

    delete []a.element;//把a的元素清空掉
    delete []b.element;//把b的元素清空掉
    a.arrayLength = listSize / 2;
    b.arrayLength = (listSize+1) / 2;
    a.element = new T[a.arrayLength];
    b.element = new T[b.arrayLength];

    //开始切分
    for(int i = 0; i != listSize;++i){
        if(i % 2 == 0)
            a.element[ca++] = element[i];
        else
            b.element[cb++] = element[i];
    }
    a.listSize = ca;
    b.listSize = cb;
}
#endif
