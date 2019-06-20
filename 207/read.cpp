#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;

int main(){
    string x;
    int c;
    x.resize(20);
    int i = 0;
    while(c = getchar() && i < 19){
        cout << "in loop";
        putchar(c);
        x[i++] = c;
    }
    x[i] = '\0';
    cout << "finish code" << endl;
    cout << x.length() << endl;
    for(int j = 0; j < 20; j++){
        printf("%d\t",x[j]);
    }
}