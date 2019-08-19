/*similar logic with uva 839 recusively find out the val of next subtree
The values can be stored in array, but it seems like more intuitive and automatically sorted if it's stored in a map

*/

#include <iostream>
#include <map>

using namespace std;
map<int, int> accumulate;

//return postive number if the tree doesn't start with -1
int getSubTree(int p){
    // cout << "reading pos " <<p << endl;
    int t;
    cin >> t;
    if(t == -1){
        return 0;
    }else{
        if(accumulate.find(p) == accumulate.end()){
            accumulate[p] = t;
        }else{
            accumulate[p] += t;
        }
        return t + getSubTree(p-1) + getSubTree(p+1);
    }
}

int main(){
    int c = 1;

    while(getSubTree(0)){
        cout << "Case " << c++ << ':' <<endl;

        map<int, int>::iterator it = accumulate.begin();
        cout << it->second;
        it++;
        for(; it != accumulate.end(); it++){
            cout << ' ' << it->second ;
        }
        cout << endl << endl;
        accumulate.clear();
    }
    
}