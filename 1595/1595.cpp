/*
Hint: find whether or not each line is symmetric first
    Compare result of each lines


*/


#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;

bool isGoodline(vector<double> &xPos, double &mid){
    sort(xPos.begin(), xPos.end());
    double median = (xPos.size()%2 == 1 ? xPos[xPos.size()/2] : (xPos[xPos.size()/2 - 1] + xPos[xPos.size()/2])/2);
    double curMid;
    for(unsigned int i = 0; i < xPos.size()/2; i++){
        curMid = (xPos[i] + xPos[xPos.size() - i - 1])/2;
        if(median != curMid) return false;
    }
    mid = median;
    return true;
}


int main(){
    int T, N;
    scanf("%d", &T);
    while(T-- > 0){
        int x, y;
        scanf("%d", &N);
        unordered_map<int, vector<double> > lines;
        for(int i = 0; i < N; i++){
            scanf("%d %d", &x , &y);
            lines[y].push_back(x);
        }

        unordered_map<int, vector<double> >::iterator it;
        unordered_set<double> tracker;
        bool symmetric = true;

        for(it = lines.begin(); it != lines.end(); it++){
            double midpoint;
            if(isGoodline(it->second, midpoint)){
                tracker.insert(midpoint);
                if(tracker.size() != 1){
                    symmetric = false;
                    break;
                }
            }else{
                symmetric = false;
                break;
            }
        }
        cout << (symmetric? "YES" : "NO") << endl;
    }
}