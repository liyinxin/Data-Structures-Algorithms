#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;
int main()
{
    std::string s;
    std::cout<<"the length of s is "<<s.length()<<"\n";
    std::cin>>s;
    std::string temp;
    int maxLength=0;
    for(auto it2 = s.begin();it2 != s.end();++it2)
        std::cout<<*it2<<",";
    std::cout<<"\n";
    for(auto it = s.begin();it != s.end();++it){
        if(temp.find(*it)>temp.length()){//如果没有在string中找到这个字符
            temp+=*it;
        }else{//如果找到了
            std::cout<<*it<<" is already in the string\n";
            std::cout<<*it<<" is in the position of the string "<<temp.find(*it)<<std::endl;
            if(maxLength < temp.length())
                maxLength = temp.length();
            temp.erase(temp.begin(),temp.find(*it)+1+temp.begin());
            temp+=*it;
            std::cout<<"\nthe temp is \n";
            for(auto it1 = temp.begin();it1 != temp.end();++it1)
                std::cout<<*it1<<" ";
            std::cout<<"\n";
        }
    }    
    std::cout<<((maxLength >temp.length() ? maxLength : temp.length()));//如果剩余的元素是大于原先的maxLength的话，就返回剩余的元素的长度
    //这个就是处理类似""a这种形式的。最后剩下的是"a但是maxLength是1。所以要return 大的length()
    return 0;
}

