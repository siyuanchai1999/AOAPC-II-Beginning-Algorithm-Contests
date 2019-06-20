#include <iostream>
#include <vector>

using namespace std;

int main(){
    string line;
    while( getline(cin,line)){
        cout << line ;
        cout << int(line[line.length() - 1]) << endl;
    }
}