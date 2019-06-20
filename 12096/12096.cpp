#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <utility>
#include <vector>
#include <string>
#include <stack>
#include <set>

#define INS(x) inserter(x, x.begin())
using namespace std;

map<set<int>, int> IDfinder;        //unordered_map from Set to pos
vector<set<int>> setArr;
stack<int> IDstack;

int getID(set<int> input){
    if(IDfinder.count(input) != 0){
        return IDfinder[input];
    }else{
        setArr.push_back(input);
        return IDfinder[input] = setArr.size() - 1;
    }
}


int main(){ 
    std::ios::sync_with_stdio(false);
    int T, N;
    string instr;
    cin >> T;
    
    
    while(T-- > 0){
        cin >> N;
        while(N-- > 0){
            cin >> instr;
            if(instr[0] == 'P'){
                IDstack.push(getID(set<int> () ));
            }else if(instr[0] == 'D'){
                IDstack.push(IDstack.top());
            }else{
                set<int> first = setArr[IDstack.top()];
                IDstack.pop();
                set<int> second = setArr[IDstack.top()];
                IDstack.pop();
                set<int> newSet;
                
                if(instr[0] == 'U'){
                    set_union(first.begin(), first.end(), second.begin(), second.end(), INS(newSet) );
                }else if(instr[0] == 'I'){
                    set_intersection(first.begin(), first.end(), second.begin(), second.end(), INS(newSet) );
                }else{
                    newSet = second;
                    newSet.insert(getID(first));
                    // cout << "inserted" << getID(first) << endl;
                }
                IDstack.push(getID(newSet));
                
            }
            cout << setArr[IDstack.top()].size() << endl;
        }
        cout << "***" << endl;
    }
}