#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <functional>


using namespace std;

vector<int> large_prime;

bool is_ugly(int num){
    for(vector<int>::iterator it = large_prime.begin(); it != large_prime.end(); it++){
        if(*it > num/2) break;
        if(num % *it == 0) return false;
    }
    if(num % 2 != 0 && num %3 != 0 && num%5 != 0){ //itself is a prime
        // cout << num <<"added" << endl;
        large_prime.push_back(num);
        return false;
    }
    return true;
}
int main(){
    std::ios::sync_with_stdio(false);
    // priority_queue<in, vector<int>, greater<int> > pq;
    
    vector<int> ugly;
    
    ugly.push_back(1);
    int index = 2;
    while(ugly.size() < 1500){
        if(is_ugly(index)){
            ugly.push_back(index);
        }
        // cout << ugly.size() << endl;
        index++;
    }
    
    for(index = 0; index < large_prime.size(); index++){
        cout << large_prime[index] << '\t';
    }
    cout << endl;
    for(index = 0; index < ugly.size(); index++){
        cout << ugly[index] << '\t';
    }
    
}