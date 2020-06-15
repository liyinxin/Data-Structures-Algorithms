#include <iostream>
#include <algorithm>
template<typename T>  void permulations(T list[],int k,int m){
    do{
        std::copy(list,list+m+1,std::ostreambuf_iterator<T>(" "));
        //std::copy(start,end,thdestination)其中end是指的尾元素的下一个位置（也即是
        //[start,end)。然后thedestination是你要将上面[start,end)拷贝到的目的位置的
        //开始位置（也就是头指针或者头迭代器)
        //
    }while(std::next_permutation(list,list+m+1));//next_permutation(start,end)
    //这个算法是对[start:end)(注意end是开区间的)按照字典顺序产生一个下一个更大的排列
    //所以如果list中没有重复的元素的话，那么循环调用这个方法可以产生n!个不同的排列
    //next_permutation(start,end,compare)是next_permutation的更普通的版本
    //函数compare用来判定一个排列是否比另一个排列要小。而在仅有两个参数的版本中
    //比较操作是由操作符<来执行的
    //这里还要说一个函数的使用方法:accumulate
    //accumulate(start,end,initialValue)这个方法是把[start,end)的元素累加到
    //initialValue中。
    //accumulate(start,end,initialValue,operator)其中operator
    //是一个函数，用来表示如何将[start,end)中元素放到累积到initialValue的
    //比如说可以使用muliples<T>()函数(乘法函数)去将[start,end)累乘到initialValue中
}
int main()
{
    
    return 0;
}

