#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

int main(){
    unordered_map<int, vector<int> > mapper;
    mapper[1].push_back(1);
    mapper[1].push_back(10);

    vector<int> x = mapper[1];
    x[0] = 10000;
    cout << mapper[1][0];
}