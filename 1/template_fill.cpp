#include <iostream>
using namespace std;
template <typename T,size_t N> void fill(const T &value,T (&a)[N]){
    for(size_t i=0;i != N; ++i){
        a[i] = value;
    }
}
int main()
{
    int a[]= {0,1,2,3,4,5};
    char b[] = "abcdefg";
    for(int i =0;i<6;i++)
        cout<<a[i]<<endl;
    cout<<b<<endl;
    fill(10,a);
    fill('h',b);
    for(int i = 0;i<6;i++)
        cout<<a[i]<<endl;
    cout<<b<<endl;
    return 0;
}

