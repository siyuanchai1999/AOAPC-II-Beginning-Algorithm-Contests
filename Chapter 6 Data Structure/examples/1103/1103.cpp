/*
pretty interesting problem. We have to first figure out how to differentiate different diagrams. We can notice that different diagrams encompass different number of white space.
Thus, we first use DFS to find the black connected blocks and mark them. Then, we use BFS on the white blocks to find connected white blocks. The returned result is the id of encompassed black blocks or -1(borders).
Then we count the number of white blocks inside each black block, so that we can tell which character each black block represents.
We use BFS to find the white blocks because DFS has the danger of overflow.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>

using namespace std;

int H, W;
vector<vector<int>> matrix;
vector<vector<int>> id;
vector<vector<bool>> whiteSearched;

void display(vector<vector<int>>& matrix){
    for(unsigned i = 0; i < matrix.size(); i++){
        for(unsigned j = 0; j < matrix[0].size(); j++){
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

void fillMatrix(char input, int r, int c){
    int intInput = (input > '9' ? input - 'a' + 10 : input - '0');
    while (intInput > 0){
        matrix[r][--c] = intInput % 2;
        intInput = intInput / 2;
    }
}

void DFS(int r, int c, int curid){
    if(r < 0 || c < 0 || r >= H || c >= W*4) return;
    if(id[r][c] > 0 || matrix[r][c] == 0) return;
    id[r][c] = curid;
    DFS(r    , c + 1, curid);
    DFS(r    , c - 1, curid);
    DFS(r + 1, c    , curid);
    DFS(r - 1, c    , curid);
}


int whiteBFS(int r, int c){
    queue<pair<int, int>> q;
    q.push(make_pair(r, c));
    bool neg = false;
    int result;
    while (!q.empty()){
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        if(r < 0 || c < 0 || r >= H || c >= W*4){
            neg = true; continue;
        } 
        if(whiteSearched[r][c]){
            continue;
        } 
        if(id[r][c] > 0 ){
            result = id[r][c]; continue;
        } 
        
        whiteSearched[r][c] = true;
        q.push(make_pair(r    , c + 1));
        q.push(make_pair(r    , c - 1));
        q.push(make_pair(r + 1, c));
        q.push(make_pair(r - 1, c));
    }
    return (neg? -1: result);
}
int whiteDFS(int r, int c){
    // cout << "searching " << r << '\t' << c << endl;
    if(r < 0 || c < 0 || r >= H || c >= W*4) return -1;
    if(whiteSearched[r][c] ) return 0;
    if(id[r][c] > 0) return id[r][c];
    whiteSearched[r][c] = true;
    int A = whiteDFS(r, c + 1);
    int B = whiteDFS(r, c - 1);
    int C = whiteDFS(r + 1, c);
    int D = whiteDFS(r - 1, c);

    if(A < 0 || B < 0 || C < 0 || D < 0) return -1;
    return max(A, max(B, max(C, D)));
}

void initFigureCnt(map<char, int>& figureCnt){
    figureCnt['A'] = 0;
    figureCnt['J'] = 0;
    figureCnt['D'] = 0;
    figureCnt['S'] = 0;
    figureCnt['W'] = 0;
    figureCnt['K'] = 0;
}

void displayMap(map<char, int>& figureCnt){
    for(map<char, int>::iterator it =figureCnt.begin(); it != figureCnt.end(); it++ ){
        int cnt = it->second;
        for(int i = 0; i < cnt; i++){
            cout << it->first;
        }
    }
    cout << endl;
}

int main(){
    unordered_map<int, char> numWhites2figure;
    numWhites2figure[1] = 'A';
    numWhites2figure[3] = 'J';
    numWhites2figure[5] = 'D';
    numWhites2figure[4] = 'S';
    numWhites2figure[0] = 'W';
    numWhites2figure[2] = 'K';
    map<char, int> figureCnt;
    cin >> H >> W;
    char c;
    int kase = 0;
    while (H != 0){
        matrix = vector<vector<int>>(H, vector<int>(W*4, 0));
        id     = vector<vector<int>>(H, vector<int>(W*4, 0));
        whiteSearched = vector<vector<bool>>(H, vector<bool>(W*4, false));
        initFigureCnt(figureCnt);

        for(int i = 0; i < H; i++){
            for(int j = 0; j < W; j++){
                cin >> c;
                if(c != '0') fillMatrix(c, i, (j + 1) * 4);
            }
        }

        int curid = 1;
        for(int r = 0; r < H; r++){
            for(int c = 0; c < W*4; c++){
                if(matrix[r][c] == 1 && id[r][c] == 0) DFS(r, c, curid++);
            }
        }
        // display(matrix);

        vector<int> icons(curid, 0);
        // cout << "curid = " << curid << endl;
        for(int r = 0; r < H; r++){
            for(int c = 0; c < W*4; c++){
                if(matrix[r][c] == 0 &&  !whiteSearched[r][c]){
                    int circled = whiteBFS(r, c);
                    // cout <<"circle = " << circled << '\t';
                    if(circled > 0){
                        icons[circled] += 1;
                    }
                } 
            }
        }
        // cout << endl;
        
        for(int i = 1; i < curid; i++){
            // cout << icons[i] << '\t';
            char figure = numWhites2figure[icons[i]];
            figureCnt[figure] += 1;
        }
        // cout << endl;

        cout << "Case " << ++kase << ": ";
        displayMap(figureCnt);

        cin >> H >> W;
    }
    
}