/*
recursion to solve the quadtree.
we don't need to generate the entire resultant tree because we only need to figure out how many more pixels are painted black by each leaf.
 
 */

#include <iostream>
#include <vector>
#define W 32
using  namespace std;

vector<vector<bool>> canvas(W, vector<bool>(W, false));

int draw(int r, int c, int w){
    char ch;
    cin >> ch;
    if(ch == 'p'){
        int half = w/2;
        return draw(r, c + half, half) 
        + draw(r, c, half)
        + draw(r + half, c, half )
        + draw(r + half, c + half, half);
    }else if(ch == 'f'){
        int cnt = 0; 
        for(int i = r; i < r + w; i++ ){
            for(int j = c; j < c + w; j++){
                if(!canvas[i][j]){
                    canvas[i][j] = true;
                    cnt++;
                }
            }
        }
        return cnt;
    }else{
        return 0;
    }
    
}

int main(){
    int T;
    cin >> T;
    while (T-- > 0){
        int result = draw(0, 0, W);
        // cout << "first tree: " << result << endl;
        result += draw(0,0,W);
        canvas = vector<vector<bool>>(W, vector<bool>(W, false));
        cout << "There are " << result << " black pixels." << endl;
    }
    
}