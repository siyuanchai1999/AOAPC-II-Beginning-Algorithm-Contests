#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int main(){
    string input;
    string empty;
    unordered_set<string> database;
    unordered_map<string, string> finder; 
    vector<string> wordArray;
    while(cin >> input){
        database.insert(input);
        wordArray.push_back(input);
    }
    sort(wordArray.begin(), wordArray.end());

    for(vector<string>::iterator it = wordArray.begin(); it != wordArray.end(); it++){
        for(unsigned int i = 1; i < it->size(); i++){
            if(database.find(it->substr(0, i)) != database.end()){
                if(database.find(it->substr(i,it->size() - i )) != database.end()){
                    cout << *it << endl;
                    break;
                }
            } 
        }
    }
}
