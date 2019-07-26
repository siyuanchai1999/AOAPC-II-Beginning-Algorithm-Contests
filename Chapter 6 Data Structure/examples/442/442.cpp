/*
The question that involves operation ordering usually has some thing to do with the stack.
The input is always legal; thus, we use push stack whenever we encounter a matrix ("A", "B" ...), and pop stack whenever we encounter a ')'.
Shouldn't be that hard.
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(){
    int N, n = 0;
    cin >> N;
    char c;
    int p ,q;
    vector<pair<int,int>> matrixLib(26);
    while (n++ < N)
    {
        cin >> c >> p >> q;
        matrixLib[c - 'A'] = make_pair(p, q);
    }
    string expression;
    while (cin >> expression)
    {
        int cnt = 0;
        stack<pair<int, int>> s;
        for(unsigned i = 0; i < expression.length(); i++){
            if(isalpha(expression[i])){
                s.push(matrixLib[expression[i] - 'A']);
            }else if(expression[i] == ')'){
                pair<int, int> rhs = s.top();
                s.pop();
                pair<int, int> lhs = s.top();
                s.pop();
                if(lhs.second != rhs.first){
                    cnt =  -1;
                    break;
                }else{
                    cnt += lhs.first * lhs.second * rhs.second;
                }

                s.push(make_pair(lhs.first, rhs.second));
            }
        }

        if(cnt == -1){
            cout << "error" << endl;
        }else{
            cout << cnt << endl;
        }
        
    }
}