#include "sortedArray.h"
#include <string>
int main()
{
    sortedArray<std::string,std::string> book;
    book.insert(std::pair<const std::string,std::string>("圣墟","辰东"));
    book.insert(std::pair<const std::string,std::string>("斗破苍穹","天蚕土豆"));
    book.insert(std::pair<const std::string,std::string>("老人与海","海明威"));
    book.output(std::cout);
    std::cout<<"book size is "<<book.size()<<"\n";
    if(book.find("老人") != NULL)
        std::cout<<"老人 find it";
    if(book.find("老人与海") != NULL)
        std::cout<<"老人与海 find it\n";
    return 0;
}

