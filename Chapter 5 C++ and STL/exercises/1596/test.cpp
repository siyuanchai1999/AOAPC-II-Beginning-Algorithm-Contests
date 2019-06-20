#include <iostream>
#include <unordered_map>

using namespace std;

struct mystructure{
    int size;
    float val;
};
int main(){
    unordered_map<int, mystructure> x;
    mystructure ms = {100, 23.4};
    x[100] = ms;
    cout << x[100].val;
}