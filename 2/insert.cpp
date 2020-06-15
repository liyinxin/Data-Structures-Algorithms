#include <iostream>
template<typename T> void insert(T a[],int n,T x){
    int i = 0;
    for(i = n-1;i >= 0 && x < a[i];--i)//i>=0是为了可以插入i+1=0
        a[i+1] = a[i];//如果没有大于的话，那么就给该x元素腾出一个空的位置来
    a[i+1] = x;
}
template<typename T> void insertSort(T a[],int n){
    //利用插入排序，其实就是首先取出一个元素作为开始的一个数组
    //然后，以这个元素为有序数组，开始插入元素，这样就得到一个
    //完整的有序数组了
    for(int i = 1;i < n;++i){
        insert(a,i,a[i]);//这个开始从第位置开始插入到数组中
        //其中第一个参数表示的是你要插入到的数组，第二个参数是
        //数组目前有值的长度，第三个表示的是要插入的元素。
    }
}
int main()
{
    int a[] = {3,2,6,5,9,4,8};
    insertSort(a,7);
    for(auto elment : a)
        std::cout<<elment<<",";
    return 0;
}

