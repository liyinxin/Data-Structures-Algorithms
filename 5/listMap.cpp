#include "listMap.h"

template<typename T> void listMap<T>::insert(int i,int index,const T &theElement){
    bool rightFullFlag = 0,leftFullFlag = 0;
    int listSize = last[i] - front[i];//首先得到数组的大小
    //判读索引是不是有效的
    if(index < 0 || index > listSize)//你要插入的元素的索引不能小于0也不能超过当前数组的大小
        throw illeagleParameter("the index must be right");
    //判断完索引以后，我们需要去插入数据了
    /*
    1.第一步首先判断本线性列表的空间有没有满
    */
    if(last[i] != front[i+1]){//如果当前这个数组还有空间
        //copy_back是将(first,last)元素拷贝到第三个迭代器指向的位置以及前边的位置，详情请看源码
        //所以这样可以很好的避免-1这个下标的处理(-1,last[i]]的元素拷贝
        //注意，这个copy_backward算法中的last表示的是尾后指针。所以需要last[i]+1;
        std::copy_backward(element+front[i]+index,element+last[i]+1,element+(last[i]+2));//从last[i]+1这个位置开始倒叙拷贝
        //拷贝完以后，我们需要插入数据，以及更改尾部指针的索引值
        element[front[i]+index+1] = theElement;
        last[i]++;
    }else{//如果内存空间已经被利用完了的话，那么先搜索右边的空间有没有有剩余的
        int j = i+1;//现在j为i的右边的第一个数组
        while(last[j] == front[j+1]){//如果右边的数组空间也被利用完了
            //那么就继续向右边开始搜索,但是搜索之前要注意一点，先判断有没有到最右边的终点
            if(last[j] == length-1)//如果到了终点，好的，退出，然后往左查找
            {
                rightFullFlag = 1;
                break;//退出，开始从i的左端搜索
            }
            j++;//如果没有达到终点的话，我们继续向右查找
        }
        if(rightFullFlag == 0){//如果右边有空间，
            std::copy_backward(element+front[i]+index,element+last[j]+1,element+last[j]+2);
            //接下来需要把转移的数组进行下标的一个变换，因为位置发生变换了
            //首先i的尾元素的指针的索引值要加1
            element[front[i]+index+1] = theElement;
            last[i]++;
            //剩下的他们的首前和尾部指针的索引值都加1就好了，也就是顺移
            for(int k = i+1;k <= j;k++){
                front[k]++;last[k]++;
            }
        }else{//如果右边满了的话，那好，去左边找新的内存空间
            j = i-1;//j为i左边第一个数组
            while(last[j] == front[j+1]){
                if(last[j] == -1){
                    leftFullFlag=1;//左边也满了，这个时候报错就好了
                    std::cout<<"\nthere is no space to insert"<<std::endl;
                }
                j--;//往左边找数组
            }
            if(leftFullFlag==0){
                std::copy(element+front[j]+1,element+front[i]+index+2,element+front[j+1]);
                //改变一些front和last的值
                //首先改变front[i]的值
                front[i]--;
                //接着顺移一些front和last的值
                for(int k = i-1;k != j;--k){
                    last[k]--;//往左移动一下
                    front[k]--;//往左移动一下
                }
            }
        }
    }
}
template<typename T> T listMap<T>::get(int i,int index)const{
    return element[front[i]+index+1];//因为front[i]表示的第一个元素的
    //前一个位置，所以查找元素的时候需要加1。

}
template<typename T> int listMap<T>::capacity()const{
    return length;
}

template<typename T> int listMap<T>::getFront(int i)const{
    return front[i];
}

template<typename T> int listMap<T>::getLast(int i)const{
    return last[i];
}
template<typename T> void listMap<T>::printAllMemeber()const{
    for(int i = 0; i != length; ++i)
        std::cout<<element[i]<<",";
}
int main()
{
    listMap<int> a(5,5);
    /*
    std::cout<<"the inist is\n";
    for(int i = 1; i <= 5;++i)
        std::cout<<"font["<<i<<"] is "<<a.getFront(i)<<" and last["
        <<i<<"]"<<" is "<<a.getLast(i)<<std::endl;
    std::cout<<std::endl;
    */
    for(int i = 0;i != 5;++i){
        a.insert(1,i,i*10+1);
        a.insert(2,i,i*10+2);
        a.insert(3,i,i*10+3);
        a.insert(4,i,i*10+4);
    }   
    for(int i = 1; i <= 5;++i)
        std::cout<<"font["<<i<<"] is "<<a.getFront(i)<<" and last["
        <<i<<"]"<<" is "<<a.getLast(i)<<std::endl;
    for(int i = 0;i != 5;++i)
        std::cout<<"get(1,"<<i<<") is "<<a.get(1,i)<<std::endl;
    std::cout<<std::endl;
    for(int i = 0;i != 5;++i){
        std::cout<<"get(2,"<<i<<") is "<<a.get(2,i)<<std::endl;
    }
    std::cout<<"\nafter the operator a.insert(1,0,100) the a is\n";
    a.insert(3,0,100);
    for(int i = 1; i <= 5;++i)
        std::cout<<"font["<<i<<"] is "<<a.getFront(i)<<" and last["
        <<i<<"]"<<" is "<<a.getLast(i)<<std::endl;
    a.printAllMemeber();
    for(int i = 0;i != 5;++i)
        std::cout<<"get(1,"<<i<<") is "<<a.get(1,i)<<std::endl;
    std::cout<<std::endl;
    for(int i = 0;i != 5;++i){
        std::cout<<"get(2,"<<i<<") is "<<a.get(2,i)<<std::endl;
    }

    return 0;
}

