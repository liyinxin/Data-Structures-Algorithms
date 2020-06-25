#include <iostream>
template<typename T>void rank(T *a,int n,int res[]){
    for(int i =0;i != n;++i)
        res[i] = 0;
    for(int i = 0; i != n;++i )
        for(int j = i+1;j != n; ++j){
            if(a[i]>=a[j])
                res[i]++;
            else
                res[j]++;
        }
}
template<typename T>void addressOfElements(T *a,int n,int res[]){
    T *temp = new T [n];//创建一个临时数组
    
    for(int i = 0;i != n; ++i)
        temp[res[i]] = a[i];//把这个位置的元素放到它对应的名次位置中
    for(int i = 0;i != n; ++i)
        a[i] = temp[i];
    delete [] temp;
}
template<typename T>void rearrange(T *a,int n,int res[]){
    for(int i = 0; i != n; ++i){
        while(res[i] != i){//如果位置对应不一致的话，就把其放到它本应该到的位置中
            std::swap(a[res[i]],a[i]);//把它应该对应的位置的数据，与现在其本身的数值进行交换
            std::swap(res[i],res[res[i]]);
            //注意，你不能只交换相应的元素，你也还要把相应的元素的名次一并
            //交换过去，因为名次和元素是一体的，不能拆分谁
        }
    }
}
int main()
{
    int a[]={3,2,6,5,9,4,8};
    int b[7];
    rank(a,7,b);
    for(auto temp : b)
        std::cout<<temp<<",";
    std::cout<<std::endl;
    //addressOfElements(a,7,b);
    rearrange(a,7,b);
    for(auto item : a)
        std::cout<<item<<",";
    return 0;
}

