#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
int main(){
    set<int> a = {1,2,45,7};
    set<int> b = {2,10, 100, 45};
    set<int> c;
    set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(c, c.begin()));
    for(set<int>::iterator it = c.begin(); it != c.end(); it++){
        cout << *it << endl;
    }
 }