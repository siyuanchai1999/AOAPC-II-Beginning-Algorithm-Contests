#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;


bool isZero(vector<int> &tp){
    for(int i = 0; i < tp.size(); i++){
        if(tp[i] != 0) return false;
    }
    return true;
}

// return true if tp is periodic, false if it can reach zero
bool judge(vector<int> &tp){
    set<vector<int> > tracker;
    tracker.insert(tp);
    bool iszero = isZero(tp);
    while(!iszero){
        iszero = true;
        int temp = tp[0];
        for(int i = 0; i < tp.size(); i++){
            int nextval = (i + 1 == tp.size() ? temp : tp[i+1]);
            tp[i] = abs(tp[i] - nextval);
            if(tp[i] != 0) iszero = false;
        }
        if(tracker.find(tp) != tracker.end()) return true;
        tracker.insert(tp);
    }
    return false;
}

int main(){
    int caseNum, tuplelen;
    cin >> caseNum;
    while(caseNum-- > 0){
        cin >> tuplelen;
        vector<int> tp;
        int temp;
        for(int i = 0; i < tuplelen; i++){
            cin >> temp;
            tp.push_back(temp);
        }
        if(judge(tp)){
            cout << "LOOP" << endl;
        }else{
            cout << "ZERO" << endl;
        }
    }
}