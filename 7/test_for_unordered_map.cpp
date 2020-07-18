#include <iostream>
#include <unordered_map>
#include <string>
#include <hash_map>
using namespace std;
using namespace __gnu_cxx;
int main()
{
    string s = "dacfesaf";
    hash_map<char,int> alphat;
    for(auto it = s.begin();it != s.end();++it)
        alphat[*it]++;
    for(auto it = alphat.begin();it != alphat.end();++it)
        std::cout<<it->first<<" ";
    return 0;
}

