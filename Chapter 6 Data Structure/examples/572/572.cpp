/*
use DFS and BFS to exhuast each connection. The number of time we call DFS/BFS is the number of connection blocks we have.
*/


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<char>> matrix;
vector<vector<bool> > searched;
int m, n;

void DFS(int r, int c){
    if(r>= m || c >= n || r < 0 || c < 0) return; //out of boundary
    if(searched[r][c]) return;
    if(matrix[r][c] == '@'){
        searched[r][c] = true;
    }else{
        return;
    }

    DFS(r + 1, c + 1);
    DFS(r + 1, c    );
    DFS(r + 1, c - 1);
    DFS(r    , c + 1);
    DFS(r    , c - 1);
    DFS(r - 1, c + 1);
    DFS(r - 1, c    );
    DFS(r - 1, c - 1);
}

void BFS(int r, int c){
    queue<pair<int, int>> q;
    q.push(make_pair(r, c));

    while (!q.empty()){
        r = q.front().first;
        c = q.front().second;
        q.pop();
        if(r>= m || c >= n || r < 0 || c < 0) continue;
        if(searched[r][c]) continue;
        if(matrix[r][c] == '*') continue;

        searched[r][c] = true;
        q.push(make_pair(r + 1, c + 1));
        q.push(make_pair(r + 1, c    ));
        q.push(make_pair(r + 1, c - 1));
        q.push(make_pair(r    , c + 1));
        q.push(make_pair(r    , c - 1));
        q.push(make_pair(r - 1, c + 1));
        q.push(make_pair(r - 1, c    ));
        q.push(make_pair(r - 1, c - 1));
    }
    
}


int main(){
    cin.sync_with_stdio(false);
    cin >> m >> n;
    while(m != 0){
        matrix = vector<vector<char>>(m,vector<char>(n));
        searched = vector<vector<bool>>(m, vector<bool>(n, false));
        int cnt = 0;
        for(int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                cin >> matrix[i][j];
            }
        }

        for(int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                if(!searched[i][j] && matrix[i][j] == '@'){
                    BFS(i, j);
                    cnt++;
                }
            }
            
        }
        cout << cnt <<endl;
        cin >> m >> n;
    }

}