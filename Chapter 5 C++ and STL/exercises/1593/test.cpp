#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> x;
    x.push_back(100);
    cout << x[0] << endl;
    cout << x[10] << endl;
    cout << max(x[0], 20);
}