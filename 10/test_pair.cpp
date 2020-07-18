#include <vector>
#include <string>
#include <iostream>
#include <utility>
using namespace std;

int main(){
   vector<pair<const int ,int>> book ;
   auto p = pair<const int,int>(10,10);
   book.push_back(p);
   cout<<"("<<book[0].first<<","<<book[0].second<<")"<<std::endl;
   book.erase(book.begin());
}
