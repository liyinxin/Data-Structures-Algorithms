#include "sortedChain.h"

int main()
{
    sortedChain<std::string,std::string> book;
    book.insert(std::pair<std::string,std::string>("老人与海","海明威"));
    book.insert(std::pair<std::string,std::string>("圣墟","辰东"));
    book.insert(std::pair<std::string,std::string>("斗破苍穹","天蚕土豆"));
    book.output(std::cout);
    book.erase("圣墟");
    book.output(std::cout);
    return 0;
}

