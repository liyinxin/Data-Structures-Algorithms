#include <iostream>
#include "stl.h"
#include <algorithm>
template<typename input_type,typename output_type> output_type 
stl::accumulate(input_type start,input_type end,output_type initialValue)const{
    //注意在模板中形参如果为引用的话，那么数组的隐式转换将被不存在，所以
    //不要在模板中使用引用，因为这样在处理数组的时候会出错
    for(;start != end;++start)
        initialValue+=*start;
    return initialValue;
}
template<typename input_type,typename output_type,typename functionType> 
output_type stl::accumulate(input_type start,input_type end,output_type initialValue,functionType operatorData)const{
    for(;start != end;++start)
        initialValue=operatorData(initialValue,*start);
    return initialValue;
}
char  addChar(const unsigned char left,const unsigned char right){
    std::cout<<(left+right)%256<<std::endl;
    return  (left+right)%256;
}
template<typename inputType,typename outputType> outputType stl::copy(inputType start,inputType end,outputType outstart)const{
    while(start != end){
        *outstart = *start;
        outstart++;start++;
    }
    return outstart;
}
template<typename T>void stl::permutations(T start,T end)const{
    std::sort(start,end);//先排序，然后把相同的元素去除
    //如果想使用next_permutations来进行产生相应的全排列的话，就必须
    //得使用这个排列中最小的数组来做为输入的数组。
    T tmp = start,tmpFirst = start;
    while(start != end){
        if(start + 1 == end)
            break;
        else if(*start != *(start + 1))
            *(++tmp) = *(start + 1);
        ++start;
    }
    do{
        std::copy(tmpFirst,tmp+1,std::ostreambuf_iterator<char>(std::cout<<" "));
    }while(std::next_permutation(tmpFirst,tmp+1));
}
/*
template<typename T> void stl::anotherPermutations(T start,T end)const{

}*/
int main()
{
    int a[10]={0,1,2,3,4,5,6,7,8,9};
    unsigned char b[10]={'0','1','2','3','4','5','6','7','8','9'};
    unsigned char cb=0;
    int length = 0;
    stl g;
    std::cout<<g.accumulate(a,a+9,length)<<std::endl;
    //std::cout<<b[0]+b[1]<<std::endl;
    std::cout<<g.accumulate(b,b+2,cb,addChar)<<std::endl;//这个时候就需要自己
    //写第四个参数operator函数了。用来处理相应的数组或类型的加法了。
    g.permutations(b,b+5);
    std::cout<<std::endl;
    /*
    do{
        g.copy(b,b+5,std::ostreambuf_iterator<char>(std::cout<<" "));
    }while(std::next_permutation(b,b+5));
    这里介绍一下next_permutation，它是用来求当前排列的下一个排列（也就是
    说比方当前数组的排列是123，那么经过next_permutations(b,b+3)以后得到的
    结果是132（其中132是所有排列中第一个大于123的排列）。如果能找到这个排列
    那么返回结果是1，否则返回结果是false。其中first和last表示的是你要排列的
    元素的长度。如果上面的123的first和last分别是b,b+2。那么也就是对12进行排列。
    得到的数组也就是123，213了。同理，prev_permutation表示的就是
    把你的输入的数组改变成比当前数组第一个小的数组。如果没有则返回
    false。
    */
    do{
        g.copy(b,b+3,std::ostreambuf_iterator<char>(std::cout<<" "));
    }while(std::prev_permutation(b,b+3));
    std::cout<<std::endl;
    std::cout<<std::count(a,a+10,0);
    /*template <class InputIterator, class T>
    typename iterator_traits<InputIterator>::difference_type
    count (InputIterator first, InputIterator last, const T& val)
    库函数中的count有三个参数，前两个参数用来表示你的数组（或容器）
    的范围，第三个参数是你要查找的数值。
    */
    
    return 0; 
}
