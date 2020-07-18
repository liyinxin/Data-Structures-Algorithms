#include <iostream>
#include <set>
#include <unordered_set>
#include <string>


int main()
{
    std::string s;
    std::cout<<"please input the string\n";
    std::cin>>s;

    std::unordered_set<char> unorderedSet;
    for(auto it  = s.begin();it != s.end();++it){

        auto ret = unorderedSet.insert(*it);
        if(ret.second == false){
            std::cout<<"\n**********************************\n";
            for(auto it1 = unorderedSet.begin();it1 != ret.first;++it1)
                std::cout<<*it1<<",";
            std::cout<<"\n**********************************\n";
        }
    }
    for(auto it = unorderedSet.begin();it != unorderedSet.end();++it)
        std::cout<<*it<<" ";
    std::cout<<std::endl;
    return 0;
}

