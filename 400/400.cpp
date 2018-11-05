#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include <functional>
#include <set>

using namespace std;

void print_str(string str, int len){
    cout << str;
    for(int i = 0; i < len - str.length(); i++){
        cout << ' ';
    }
}
int main(){
    const int COLMAX = 60;
    int n, M = 0, C, R;
    set<string> setStr;
    string str;
    while(cin >> n){
        while(n--> 0){
            cin >> str;
            setStr.insert(str);
            M = str.length() > M ? str.length() : M;
        }
        n = setStr.size();
        C = (COLMAX - M)/(M + 2) + 1;
        R = (n + C - 1)/ C;
        // cout << n << '\t' << C << '\t' << M << '\t' << R << '\t' << endl;
        cout << "------------------------------------------------------------" << endl;
        set<string>::iterator it = setStr.begin();
        set<string>::iterator start = it;
        for(int i = 0; i < R; i++){
            for(int j = 0; j < C; j++){
                if(j*R +i >= n) break;
                string s = *(std::next(it,j*R +i ));
                print_str(s, j == C -1 ? M: M+2);
            }
            cout << endl;
        }
        M = 0;
        setStr.clear();
    }
    
    
}