#include "listMap.h"

template<typename T> void listMap<T>::insert(int i,int index,const T &theElement){    
    int size = last[i]-front[i];//计算出该线性表有多少个元素
    bool rightFullFlag=0,leftFullFlag=0;
    /*
     1.先检查下标是不是正确的；
     2.判断这个线性表还有没有空间
     */
    if(index > size)//下标不符合选项
        throw illeagleParameter("index must be right");
    if(last[i] != front[i+1]){//如果数组还有空间的话
        //把index后面的元素拷贝到index+1后的位置
        std::copy(element+front[i]+index+1,element+last[i],element+front[i]+index+2);
        element[front[i]+index] = theElement;
        last[i]++;//将元素的长度加1。
    }
    else{//如果内存满了，那么首先查找右边有没有内存空间
        int j = i+1;
        while(last[j] == front[j+1]){//如果右边的第n个列表内存空间满了
            if(last[j] == length-1){//到末尾了
                rightFullFlag = 1;
                break;
            }
            j++;
        }
        if(rightFullFlag == 1){//如果右边满了
            j = i-1;
            while(last[j] == front[j+1]){
                if(j == 0){//到最左边了
                    leftFullFlag = 1;
                }
                j--;
            }
            if(leftFullFlag==1){
                std::cout<<"all full\n";
            }else{//如果左边没有满
                std::copy(element+front[i],element+front[i]+index,element+front[j+1]-1);
                element[front[i]+index] = theElement;
                for(int k = i;k != j;--k){//修改各个序列的索引起始下标
                    front[k]--;//i的起始下标要减一，因为左移了
                    last[k]--;
                }
                
            }
        }else{
        //如果右边没有满
            std::copy(element+front[i]+index+1,element+last[j],element+front[i]+index+2);
            element[front[i]+index] = theElement;
            for(int k = i;k != j;++k){
                last[k]++;//第一个last要加一；
                front[k+1]++;//第二个front肯定要加一
            }
        }
    }
}
template<typename T> T listMap<T>::get(int i,int index)const{
    return element[front[i]+index];
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
int main()
{
    listMap<int>a(5,5);
    for(int i = 1; i != 6;i++){
        std::cout<<"the front["<<i<<"] is "<<a.getFront(i)
        <<" and the last[i] is "<<a.getLast(i)<<std::endl;
    }
    std::cout<<"the length is "<<a.capacity()<<std::endl;
    for(std::size_t i = 0; i != 5; ++i){
        a.insert(2,i,i*10);
        a.insert(3,i,i*10+1);
        a.insert(4,i,i*10+2);
    }
    a.insert(3,5,500);
    std::cout<<"a[3] is ";
    for(int i = 0; i != 6; ++i){
        std::cout<<a.get(3,i)<<",";
    }
    for(int i = 1; i != 6;i++){
        std::cout<<"the front["<<i<<"] is "<<a.getFront(i)
        <<" and the last[i] is "<<a.getLast(i)<<std::endl;
    }
    return 0;
}

