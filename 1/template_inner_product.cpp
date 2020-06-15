#include <iostream>
using namespace std;
template <typename T,size_t N> T inner_product(const T (&a)[N],const T (&b)[N]){
    T sum = 0;
    for(size_t i = 0; i != N; ++i)
        sum += a[i] * b[i];
    return sum;
}
int main()
{
    int a[5] = {1,2,3,4,5};
    int b[5] = {1,2,3,4,5};
    cout<<inner_product(a,b)<<endl;
    double c[5] = {1.1,2.2,3.3,4.4,5.5};
    double d[5] = {1.1,2.2,3.3,4.4,5.5};
    cout<<inner_product(c,d)<<endl;
    return 0;
}

