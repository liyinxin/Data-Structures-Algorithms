#include "chain.h"

int main()
{
    chain<std::string> node;
    node.insert(0,"a");
    node.insert(1,"b");
    node.insert(0,"c");
    std::cout<<node<<std::endl<<node.size()<<std::endl;
    node.erase(0);
    std::cout<<node<<std::endl;
    node.insert(0,"e");
    std::cout<<node<<"\nsize is "<<node.size();
    return 0;
}
