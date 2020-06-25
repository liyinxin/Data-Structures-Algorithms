#include "mychain.h"
int main()
{
    mychain<std::string> node;
    node.insert(0,"a");
    node.insert(1,"b");
    node.insert(0,"c");
    std::cout<<node<<std::endl<<node.size()<<std::endl;
    node.erase(0);
    std::cout<<node<<std::endl;
    node.insert(0,"e");
    std::cout<<node<<"\nsize is "<<node.size();
    std::cout<<std::endl;
    std::copy(node.begin(),node.end(),std::ostream_iterator<std::string>(std::cout,","));
    std::cout<<std::endl;
    auto p = node.begin();
    for(int i = 0;p != node.end();++p,++i)
        std::cout<<node.get(i)<<" ";

    return 0;
}

