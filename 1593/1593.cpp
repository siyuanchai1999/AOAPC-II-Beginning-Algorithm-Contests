#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;


void printSpaces(int n){
    while(n-- > 0){
        cout << ' ';
    }
}
int main(){
    vector<vector <string> > table;
    vector<int> lengthTracker;
    string line, word;
    while(getline(cin, line)){
        vector<string> entry;
        istringstream iss(line);
        int pos = 0;
        while(iss >> word){
            entry.push_back(word);
            if(pos < lengthTracker.size()){
                // lengthTracker[pos] = max(lengthTracker[pos], word.length());
                lengthTracker[pos] = lengthTracker[pos] > word.length() ?  lengthTracker[pos] : word.length();
            }else{
                lengthTracker.push_back(word.length());
            }
            pos++;
        }
        table.push_back(entry);
    }

    for(int i = 0; i < table.size(); i++){
        vector<string> entry = table[i];
        for(int j = 0; j < entry.size(); j++){
            cout << entry[j];
            if(j < entry.size() - 1) printSpaces(lengthTracker[j] - entry[j].length() + 1);
        }
        cout << endl;
    }
}