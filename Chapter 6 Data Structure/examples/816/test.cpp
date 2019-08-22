#include <iostream>
#define MAXSIZE 10

using namespace std;

int main(){
    bool searched[MAXSIZE][MAXSIZE] = {false};
    for(int i = 0; i < MAXSIZE; i++){
        for(int j = 0; j < MAXSIZE; j++){
            cout << searched[i][j] << '\t';
        }
        cout << endl;
    }
}