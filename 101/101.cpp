#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
// #include <pair>

using namespace std;

vector<vector<int>> container;
unordered_map<int, pair<int, int>> finder;

void show(int n){
    // cout << "-----------------" << endl;
    for(int i = 0; i < n; i++){
        cout << i << ':';
        for(int j = 0; j < container[i].size(); j++){
            cout << ' ' << container[i][j];
        }
        cout << endl;
    }
    // cout << "-----------------" << endl;
}

void clear_above(int block_num){
    int stack_num = finder[block_num].first;
    int pos = finder[block_num].second + 1;
    int stack_len = container[stack_num].size();
    
    for(;pos < stack_len; pos++){
       int val  = container[stack_num].back();
       finder[val].first = val;         //update finder
       finder[val].second  = container[val].size();
       container[val].push_back(val);
       container[stack_num].pop_back();
    }
}

void pile(int a, int b){
    int b_pile = finder[b].first;
    int a_pile = finder[a].first;
    int a_pos  = finder[a].second;
    int temp = a_pos;
    
    for(;a_pos < container[a_pile].size(); a_pos++){
        int val = container[a_pile][a_pos];
        container[b_pile].push_back(val);
        finder[val].first = b_pile;
        finder[val].second = container[b_pile].size() - 1;
    }
    container[a_pile].resize(temp);
}
int main(){
    int n, a, b;
    string input1, input2;
    
    std::ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++){
        vector<int> temp{i};
        container.push_back(temp);
        finder[i] = make_pair(i,0);
    }
    
    cin >> input1;
    while(input1 != "quit"){
        cin >> a >>input2 >> b;
        if(!(a == b || finder[a].first == finder[b].first)){
           if(input2 == "onto") clear_above(b);
           if(input1 == "move") clear_above(a);
           pile(a,b);
           
        }
        cin >> input1;
        
    }
    
    show(n);
    
    
}