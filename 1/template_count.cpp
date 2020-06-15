#include <iostream>
using namespace std;

template <typename T,size_t N> size_t count(const T value,const T (&a)[N]){
    size_t i = 0,sum=0;
    for(;i != N;++i)
    {
        if(value == a[i])
            ++sum;
    }
    return sum;
}
int main()
{
    int a[10]={0,1,2,3,4,5,1,2,3,4};
    char b[]="hello,are you ok";
    cout<<count('o',b)<<endl;
    cout<<count(1,a);
    return 0;
}

