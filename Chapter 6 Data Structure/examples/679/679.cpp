#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int main(){
    int l, maxD = 0, maxI = 0, curD, curI;
    cin >> l;
    vector<pair<int, int>> testCases;
    while (l-- > 0){
        cin >> curD >> curI;
        testCases.push_back(make_pair(curD, curI));
        maxD = max(maxD, curD);
        maxI = max(maxI, curI);
    }
    cin >> l;
    // cout << "maxD = " << maxD << endl;
    // cout << "maxI = " << maxI << endl;
     
    vector<bool> tree(pow(2, maxD + 1), false);
    vector<vector<int>> lookup(maxI + 1, vector<int>(maxD + 1) );
    for(unsigned i = 1; i < lookup.size(); i++){
        int pos = 1;
        for(unsigned d = 1; d < lookup[0].size(); d++){
            lookup[i][d] = pos;
            // cout << "assign " << i << '\t' << d << " to " << pos << endl;
            //update pos for next layer
            tree[pos]  = !tree[pos];
            pos = (tree[pos] ? pos*2 : pos *2 + 1);
            
        } 
    }

    for(unsigned i = 0; i < testCases.size(); i++){
        cout << lookup[testCases[i].second][testCases[i].first] << endl;
    }
}