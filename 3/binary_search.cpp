#include <iostream>
//这个算法是在[left,right]之间搜索的，包括两端的，所以
//如果知道了端点不是相应的元素的话，那么我们可以将其端点往
//前移动一下
//还要注意一下，这个算法是基于有序序列的，所以a必须是一个有序的，如果
//不是有序的，需要利用第二章学习的算法去将其排下序
template<typename T> int binarySearch(T a[],int n,T &x){
    int left = 0,right = n-1;
    while(left<=right){
        int middle = (left + right) / 2;
        if(x == a[middle])return middle;
        else if(x < a[middle])right = middle - 1;//其实就是如果x在middle的左边
        //则把right放在middle的上一个元素上，因为middle已经不是要查找的元素了
        else if(x > a[middle])left = middle + 1;//其实就是如果x在middle的右边，
        //那么需要把left换成middle的下一个元素，因为middle也已经不是要查找的元素了
    }
    return -1;//如果没有找到的话，则返回-1；
}
template<typename T> void squareMatrixMultiply(T (*a)[2],T (*b)[2],T (*c)[2],int n){
    T sum = 0;
    for(int i = 0;i != n; ++i){
        for(int j = 0;j != n;++j){
            sum = 0;
            for(int k = 0; k != n;k++){
                sum += a[i][k] * b[k][j];//列表示的是第二维空间不变，第一维在变
                //行表示的是第一维不变，第二维变化。
            }
            c[i][j] = sum;
        }
    }
}
int main()
{
    int a[2][2] = {1,2,3,4};
    int b[2][2] = {1,2,3,4};
    int c[2][2];
    int x;
    /*
     while(std::cin>>x)
        std::cout<<binarySearch(a,6,x)<<std::endl;
    */
    squareMatrixMultiply(a,b,c,2);
    for(auto eletem : c)
        std::cout<<eletem[0]<<",";
    return 0;
}

