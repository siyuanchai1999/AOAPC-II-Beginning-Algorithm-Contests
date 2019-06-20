#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main(){
    vector<int> v{1,2,3};
    vector<int> p{1,2,3};
    set<vector<int> > tracker;
    tracker.insert(v);
    v[1] = 10;
    cout << v[2] << endl;
    cout << (2 + 1)% v.size();
}