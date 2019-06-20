#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include <set>

using namespace std;
int main(){
    std::ios::sync_with_stdio(false);
    set<string> dict;
    unordered_map<string, int> cnt;
    string s, lowerS;
    vector<string> storage, normal;
    char c;
    while((c = getchar()) != '#'){
        if(isalpha(c)){
            s.push_back(c);
            lowerS.push_back(tolower(c));
        }else if(s.length()!= 0){
            sort(lowerS.begin(), lowerS.end());
            if(cnt.count(lowerS) == 0) cnt[lowerS] = 0;
            cnt[lowerS]++;
            
            storage.push_back(s);
            normal.push_back(lowerS);
            lowerS.clear();
            s.clear();
        }
    }
    
    set<string> ans;
    int len = storage.size();
    for(int i = 0; i < len ; i++){
        if(cnt[normal[i]] == 1 || normal[i].length() == 1){
           ans.insert(storage[i]); 
        }  
    }
    for(set<string>::iterator it = ans.begin(); it != ans.end(); it++){
        cout << *it << endl;
    }
}