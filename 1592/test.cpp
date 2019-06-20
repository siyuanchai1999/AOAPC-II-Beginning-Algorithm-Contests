#include <iostream>
#include <map>
using namespace std;
int main(){
   int i = 10;
   for(i = 10; i< 5;i++){
       cout << "hello world";
   }
   map<pair<string, string>, int> finder;
   cout << finder[make_pair("hello ", "world")] << endl;
}