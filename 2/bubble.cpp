#include <iostream>
template<typename T> void bubble(T *a,int n){
    bool isSorted = false;
    for(int i = n; i > 1 && !isSorted;--i){
        isSorted = true;//这个必须放在外面的for循环
        //因为，你的有序无序是针对某一个序列的，而不是某两个
        //元素的。所以你在外面的for循环中设置isSorted
        //这个for循环是用来改变每一次数组的大小的
        for(int j = 0; j != i-1;++j){//这个循环是用来比较当前大小数组的元素的
        //这个for循环其实就是一次冒泡的过程
            if(a[j] > a[j+1]){
                isSorted = false;//如果左边的大于右边的了，那么这个
                //肯定不是有序的了，那我就可以交换了。
                std::swap(a[j],a[j+1]);
            }
        }
    }
}
int main()
{
    int a[] = {3,2,8,9,6,2,5};
    bubble(a,7);
    for(auto item : a)
        std::cout<<item<<",";
    return 0;
}

