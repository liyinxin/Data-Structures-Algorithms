#include <iostream>

template<typename T>void rank(T a[],int n,int r[]){
    for(int i = 0; i != n;++i)
        r[i] = 0;       //将名词的数组初始化为0
    for(int i = 0;i != n; ++i)
        for(int j = i+1;j != n;++j){
            if(a[i] >= a[j])
                r[i]++;//如果左边的大，那么就把该下标对应的顺序名词加1
            else
                r[j]++;//反之，则右边的加1
        }//这个算法的核心思想就是从左边第一个位置与后边的逐个比较，然后得到
        //相应的顺序名词
}
int main()
{
    int a[9]={3,2,6,5,9,4,7,1,8};
    int b[9];
    rank(a,9,b);
    for(auto item : b)//注意，这个是范围for循环的使用，
        //expression 必须是序列，数组,vector或string之类的，
        //它们有一个共同点就是可以返回begin和end的迭代器
        std::cout<<item<<",";
    return 0;
}

