#include <iostream>
using namespace std;
template <typename T>bool make2Array(T ** &x,int numberOfRows,int rowSize[]){//注意第一个形参，这个必须是
    //指针的引用，如果单纯的是指针的话，那么在下面第一个过程中，x就指向其他地址了，所以被传进来的参数
    //就没有被它使用了。所以当程序中需要使用传进来的指针进行地址的改变的时候，必须得传指针的引用，或者
    //指针的指针。
    try{
        x = new T *[numberOfRows];//这是一个数组，数组的成员是指向T的指针，必须得这样，因为x是个char的二级指针
        for(int i = 0;i != numberOfRows;i++){
            x[i] = new T [rowSize[i]];
            for(int j=0;j!=rowSize[i];j++){
                x[i][j]='1';
            }
         }
        return true;
    }catch(bad_alloc){
        return false;
    }
}

int main()
{
    char **a;
    int size[2]={4,5};
    cout<<"sizeof(string)"<<sizeof(string)<<endl;
    cout<<"sizeof(char *)"<<sizeof(char *)<<endl;//指针的大小是8个字节
    cout<<"sizeof(char **)"<<sizeof(char **)<<endl;//指针的字节是8个字节
    cout<<"sizeof(char)"<<sizeof(char)<<endl;//char类型的字节是1个字节
    cout<<make2Array(a,2,size)<<endl;
    cout<<"sizeof(decltype(size))"<<sizeof(decltype(size))<<endl;//注意decltype得到的类型是int *，所以是一个
                                                                //指针的大小为8字节
    cout<<"sizeof(size)"<<sizeof(size)<<endl;//size的大小是size这个数组所占的内存的大小，是两个int,为4*2字节
    cout<<"sizeof(size[0])"<<sizeof(size[0])<<endl;//size[0]其实返回的是int的类型的大小,4字节
    cout<<"sizeof(int)"<<sizeof(int)<<endl;//
    for(int i=0;i!=sizeof(size)/sizeof(decltype(size[0]));i++)//decltype(size[0])返回的是size[0]这个对象的类型，为int
                                                            //其实这个for循环的第二部分也可以写成
                                                            //sizeof(size)/sizeof(size[0])
    {
        for(int j=0;j!=size[i];j++)
            cout<<a[i][j]<<',';
        cout<<endl;
    }
    return 0;
}

