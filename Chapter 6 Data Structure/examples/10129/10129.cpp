/*
Question on Euler's path. Each word is a directed edge that points from the first character to the last one. 
If the graphs is connected, We should node that the path only exists when every node has same number of in degrees and out degrees or only two of them have different degrees (one should be one more in in degrees and another should be one more in out degrees)
Thus, we frist count out how many nodes have different in-out degrees. The order exists only if there are two nodes with diffrent two or zero in-out degrees.
If there are two nodes with different in-out degress, we select with one with one more in degree as starting ponit and use DFS to check connectivity.
If there are no  node with different in-out degress, we select a random one as starting ponit and use DFS to check connectivity.

*/


#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;
vector<vector<int>> graph;
unordered_set<int> nodes;
void DFS(int start){
    nodes.erase(start);
    for(unsigned i = 0; i < graph[start].size(); i++){
        //not yet explored
        if(nodes.find(graph[start][i]) != nodes.end()){
            DFS(graph[start][i]);
        }
    }

}

int main(){
    int T, N;
    cin >> T;
    while (T-- > 0)
    {
        cin >> N;
        string input;
        vector<int> inOutCnt(26, 0);
        graph = vector<vector<int>>(26, vector<int>());
        nodes = unordered_set<int>();
        while(N-- > 0){
            cin >> input;
            int from = input.front() - 'a';
            int to   = input.back() - 'a';
            inOutCnt[from]++;
            inOutCnt[to]--;
            nodes.insert(from);
            nodes.insert(to);
            graph[from].push_back(to);
        }

        bool result = false;
        int start = -1;
        unordered_set<int> diffpos;
        for(int i = 0; i < 26; i++){
            if(inOutCnt[i] != 0){
                diffpos.insert(i);
            }
        }
        // cout << "diffpos.size() = " << diffpos.size() << endl;
        if(diffpos.size() == 0 && nodes.size() > 0 ){
            start = *nodes.begin();
        }

        if(diffpos.size() == 2){
            unordered_set<int>::iterator it = diffpos.begin();
            int first = *it++;
            int second = *it;
            if(inOutCnt[first] == 1 && inOutCnt[second] == -1) start = first;
            if(inOutCnt[first] ==-1 && inOutCnt[second] ==  1) start = second;
        }
        // cout << "start = " << start << endl;
        if(start >= 0){
            DFS(start);
            result = (nodes.size() == 0);
        }
        
        cout << (result ? "Ordering is possible." : "The door cannot be opened.") << endl;

    }
    
}