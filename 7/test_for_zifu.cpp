#include <iostream>
#include <string>
using namespace std;
class Solution {
public:
    char firstUniqChar(string s) {
        char kong = ' ';
        int numbers = 0;
        for(auto it = s.begin();it != s.end();it = s.begin()){//从第一个数开始查找
            //s.find(*it)返回出现的位置的下标
            char C = *it;
            int pos = 0;
            while((pos = s.find(C)) != string::npos){
                s.erase(pos,pos+1);//把它删掉
                numbers++;//flag如果为1表示已经有一个了
            }
            if(numbers==1)
                return C;
            numbers=0;
        }
        return kong;
    }
};
int main()
{
    string s = "acaadcad";
    Solution t;
    std::cout<<t.firstUniqChar(s);
    return 0;
}

