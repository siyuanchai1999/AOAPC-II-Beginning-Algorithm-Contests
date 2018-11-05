#include <iostream>

using namespace std;
int main(){
    int R, C;
    string str_R, str_C;
    getline(cin, str_R, ' ');
    getline(cin, str_C);
    R = stoi(str_R);
    C = stoi(str_C);
    string str;
    char sperate = ',';
    cout << "R = " << R << "    C = " <<  C << endl;
    for(int r = 1; r <= R; r++){
        for(int c =1; c <= C ; c++){
            if(c != C){
                getline(cin,str, sperate);
            }else{
                getline(cin,str);
            }
            printf("%d\n",str.length());
            cout << str << endl;
        }
        
    }
}