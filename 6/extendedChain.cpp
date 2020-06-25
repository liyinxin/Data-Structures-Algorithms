#include "extendedChain.h"

int main()
{
    extendedChain<int> a;
    a.insert(0,1);
    a.insert(1,2);
    std::cout<<a.size()<<std::endl;
    std::cout<<"this is the a.get(0) "<<a.get(0)<<std::endl;
    a.output(std::cout);
    a.erase(0);
    std::cout<<"\nthe listSize is now "<<a.size()<<std::endl;
    a.push_back(2);
    std::cout<<a<<std::endl;
    extendedChain<int> b(a);
    std::cout<<"\nthis is the b"<<b<<std::endl;
    return 0;
}
