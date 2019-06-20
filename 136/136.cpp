#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <functional>

using namespace std;

unordered_map<long long, bool> tracker;
priority_queue<long long, vector<long long>, greater<long long> > pq;

int main(){
    // std::ios::sync_with_stdio(false);
    // priority_queue<in, vector<int>, greater<int> > pq;
    pq.push(1);
    int count = 0;
    long long val;
    while(count < 1500){
        val = pq.top();
        count++;
        if(tracker.find(2*val) == tracker.end()){
            pq.push(2*val);
            tracker[2*val] = true;
        }   
        if(tracker.find(3*val) == tracker.end()){
            pq.push(3*val);
            tracker[3*val] = true;
        }   
        if(tracker.find(5*val) == tracker.end()){
            pq.push(5*val);
            tracker[5*val] = true;
        }   
        pq.pop();
    }
    cout << "The 1500'th ugly number is " << val << '.' << endl;    
    
}