#include <iostream>
using namespace std;
size_t min(const size_t lval,const size_t rval){
    return lval < rval ? lval : rval;
}
template <typename T> bool changeLength1D(T * &x,size_t oldLength,size_t newLength){
    try{
        if(newLength <0)
            throw length_error("newLength must >0");
        auto new_space = new T [newLength];
        size_t number = min(oldLength,newLength);
        copy(x,x+number,new_space);
        delete [] x;
        x = new_space;
        return true;
    }catch(bad_alloc){
        cout<<"bad_alloc"<<endl;
        return false;
    }
}
int main()
{
    auto old_array = new char [10]{'a','b'};
    cout<<changeLength1D(old_array,10,20)<<endl;
    for(int i=0;i!= 10;i++)
        cout<<old_array[i]<<",";
    cout<<endl;
    for(int i = 0;i != 20;++i){
        if(i<=1)
            old_array[i]=old_array[i]+1;
        else
            old_array[i]='l';
    }
    for(int i = 0;i != 20;++i)
        cout<<old_array[i]<<",";
    auto old_int_array = new int [10]{0,1,2,3,4,5,6,7,8,9};
    cout<<changeLength1D(old_int_array,10,20);
    for(int i = 0;i != 20;++i)
        cout<<old_int_array[i]+1<<',';
    return 0;
}

