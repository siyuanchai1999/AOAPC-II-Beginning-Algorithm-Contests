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
    vector<string> compounds;
    while(cin >> input){
        if(finder[input] != empty) compounds.push_back(finder[input]);
        for(int i = 1; i < input.size(); i++){
            string substring = input.substr(0,i);
            if(database.find(substring) != database.end()){     //have overlapped substring
                string latterpart = input.substr(i,input.size() - i);
                finder[latterpart] = input;
                if(database.find(latterpart) != database.end()) compounds.push_back(input);
            }
        }
        database.insert(input);
    }
    sort(compounds.begin(), compounds.end());
    for(vector<string>::iterator it = compounds.begin(); it != compounds.end(); it++){
        cout << *it << endl;
    }
}
