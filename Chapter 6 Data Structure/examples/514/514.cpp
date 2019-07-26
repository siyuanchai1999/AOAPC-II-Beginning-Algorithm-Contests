/*
Simple but interesting question. It's obvious that the station in the question implies a stack. 
We have A represent the next incoming coach, and reOrg[B] represent the expected reordered coach.
If the top of the stack is same as the expected reOrg[B] we pop stack and increment B to fit the next.
Otherwise, we can only push a new coach onto the stack. If we have exhausted the teh incoming coaches (A > N), then this must not fulfill the order specified.
 */

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main(){
    int N, first;
    cin >> N;
    while (N != 0)
    {
        vector<int> reOrg(N + 1);
        cin >> first;
        while (first != 0)
        {
            reOrg[1] = first;
            for (size_t i = 2; i <= N; i++)
            {
                cin >> reOrg[i];
            }
            int A = 1, B = 1;
            bool doAble = true;
            stack<int> s;
            while (B <= N)
            {
                if(!s.empty() && s.top() == reOrg[B]){
                    s.pop();
                    B++;
                }else if(A <= N){
                    s.push(A);
                    A++;
                }else{
                    doAble = false;
                    break;
                }
            }
            cout << (doAble ? "Yes" : "No") << endl;

            cin >> first;
        }
        cin >> N;
        cout << endl;
    }
    
}