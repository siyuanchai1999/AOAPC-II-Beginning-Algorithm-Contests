/*recursively call figureOut function to find the weight of the submobiel
it is -1 when the submobile is imbalanced */

#include <iostream>

using namespace std;
//return total weight of substree, -1 if imbalanced
int figureOut(){
    int W1, D1, W2, D2;
    cin >> W1 >> D1 >> W2 >> D2;
    if(W1 == 0) W1 = figureOut();
    if(W2 == 0) W2 = figureOut();
    
    // cout << W1 << '\t' << W2 <<endl;
    if(W1 == -1 || W2 == -1) return -1;
    if(W1 * D1 != W2 * D2) return -1;
    return W1 + W2;
}

int main(){
    int T;
    cin >> T;
    while (T-- > 0){
        if(figureOut() != -1){
            cout << "YES" << endl; 
        }else{
            cout << "NO" << endl;
        }
        if(T) cout << endl;
    }
    
}