#include <iostream>
#include <map>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main(){
    int R, C;
    string str_R, str_C;
    string database[10001][11];
    string input;
    char sperate = ',';
    while(getline(cin, str_R, ' ') && getline(cin, str_C)){
        R = stoi(str_R);
        C = stoi(str_C);
        // map<pair<string, string>, int> finder;
        bool notFound = true;
        for(int r = 1; r <= R; r++){
            for(int c = 1; c <= C; c++){
                if(c != C ){
                    getline(cin,input, sperate);
                }else{
                    getline(cin,input);
                }
                database[r][c] = input;
            }
        }
        int c1 = 1, c2;
        for(; c1 <= C && notFound; c1++){
            for(c2 = c1 + 1; c2 <= C && notFound; c2++){
                map<pair<string, string>, int> finder;
                for(int r = 1; r <= R && notFound; r++){
                    pair<string, string> curPair = make_pair(database[r][c1], database[r][c2]);
                    if(finder[curPair] != 0){
                        cout << "NO" << endl;
                        cout << finder[curPair] << ' ' << r << endl;
                        cout << c1 << ' ' << c2 << endl;
                        notFound = false; 
                    }
                    finder[curPair] = r;
                }
            }
        }

        if(notFound) cout << "YES" << endl;
    }
}