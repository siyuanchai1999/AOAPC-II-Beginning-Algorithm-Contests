#include <iostream>
#include <vector>

using namespace std;

void getDiscard(vector<int> &mv){
    int numdis = 0;
    while(mv.size() > 1){
        vector<int> newMV;
        if(mv.size() % 2 == 1){
            newMV.push_back(mv.back());
            mv.pop_back();
        }
        for(int i = 0; i < mv.size(); i++){
            if(i%2 == 1){
                newMV.push_back(mv[i]);
            }else{
                if(numdis++) cout << ',';
                cout << ' ';
                cout  << mv[i];
            }
        }
        mv = newMV;
    }
    cout << endl;
    cout << "Remaining card: " << mv[0] << endl;
        
}

int main(){
    int num;
    scanf("%d",&num);
    while(num != 0){
        vector<int> mv;
        for(int i = 1; i <= num; i++){
            mv.push_back(i);
        }
        cout << "Discarded cards:";
        getDiscard(mv);
        scanf("%d",&num);
    }
}