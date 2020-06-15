#include <iostream>
template<typename T> int indexofMax(T *a,int n){
    int indexofmax = 0;
    for(int i = 1; i != n;++i){//注意，这个就是拿着目前找到的
        //最大的元素去跟后面的元素进行比较，如果找到比目前还
        //大的元素，那么把这个下标记下来，然后用这个数继续去
        //比较
        if(a[indexofmax]<a[i])
            indexofmax = i;
    }
    return indexofmax;
}
template<typename T> void selectSort(T *a,int n){
    for(int i = n; i >0; --i){//注意，要排除对有序的数组进行排序
        //的情况。
        std::swap(a[indexofMax(a,i)],a[i-1]);//将最大的与目前该元素的最后一个位置
        //进行交换
    }
}
template<typename T> void selectSortNo(T *a,int n){
    bool isSorted = false;
    int indexOfMax;
    for(int i = n; i > 0 && !isSorted; --i){
        isSorted = true;
        indexOfMax = 0;
        for(int j = 1; j != i; j++){
            if(a[indexOfMax] < a[j]){//如果是有序的话，那么会一直
                //进入这个程序，所以你的isSorted = true;直接在外层就退出了
                indexOfMax = j;
            }
            else
                isSorted = false;
        }
        std::swap(a[indexOfMax],a[i-1]);//首先不管是不是有序的，交换一次
        //如果是有序的也就只交换一次。
    }
}
int main()
{
    int a[] = {3,2,6,5,9,4,8};
    selectSortNo(a,7);
    for(auto item : a)
        std::cout<<item<<",";
    return 0;
}

