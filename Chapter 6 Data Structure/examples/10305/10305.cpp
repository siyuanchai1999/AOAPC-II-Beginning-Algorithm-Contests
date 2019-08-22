/*
practice for topological sort, the input is garanteed to be ACG no worry

*/

#include <iostream>
#include <stack>
#include <vector>

using namespace std;
vector<vector<int>> graph;
stack<int> result;
vector<int> status;


/*
status[v] == 1 when already sorted and pushed onto the stck
status[v] == 0 when never been explored
status[v] == -1 when it is being explored
*/
bool topSort(int v){
    if(status[v] == 1) return true;
    if(status[v] == -1) return false;
    
    status[v] = -1;
    for(unsigned i = 0; i < graph[v].size(); i++){
        bool r = topSort(graph[v][i]);
        if(!r) return false;
    }

    result.push(v);
    status[v] = 1;
    return true;
}

void output(bool noCycle){
    if(!noCycle){
        cout << "contains cycle!!! no possible topological sort" << endl;
        return; 
    }
    cout << result.top();
    result.pop();
    while (!result.empty()){
        cout << ' ' << result.top();
        result.pop();
    }
    cout << endl;
}

int main(){
    int n, m, x, y;
    cin >> n >> m;
    while (n != 0){
        result = stack<int>();
        graph = vector<vector<int>>(n + 1, vector<int>());
        status = vector<int>(n + 1, 0);
        while(m-- > 0){
            cin >> x >> y;
            graph[x].push_back(y);
        }
        bool noCycle = true;
        for(int i = 1; i <= n; i++){
            noCycle = topSort(i);
            if(!noCycle) break;
        }

        output(noCycle);
        cin >> n >> m;    

    }
    
}   
