#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(){
    string n;
    char c;
    set<string> dict;
    
    while((c = getchar())!= EOF){
        if(isalpha(c)){
            n.push_back(tolower(c));
        }else if(n.length() != 0){
            dict.insert(n);
            n.clear();
        }
    }
    for(set<string>::iterator it = dict.begin(); it != dict.end(); it++){
        cout << *it << endl;
    }
}