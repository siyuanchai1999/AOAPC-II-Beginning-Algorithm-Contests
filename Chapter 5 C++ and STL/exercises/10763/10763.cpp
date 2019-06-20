#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    int stuNum;
    int src, target;
    scanf("%d", &stuNum);
    while(stuNum > 0){
        map<pair<int, int>, int> tracker;
        int nonzeroCnt = 0;
        for(int i = 0; i < stuNum; i++){
            scanf("%d %d", &src, &target);
            pair<int, int> ask = src < target ? make_pair(src, target) : make_pair(target, src);
            int temp = tracker[ask];
            tracker[ask] = temp + target - src;
            if(temp + target - src == 0){       //decrease one when suitable pairs between target and src are found 
                nonzeroCnt--;
            }else if(temp + target - src != 0 && temp == 0){       //increase one when new exchange info entered
                nonzeroCnt++;
            }
        }
        if(nonzeroCnt == 0){
            cout << "YES" << endl;
        }else{
            // cout << nonzeroCnt << '\t';
            cout << "NO" << endl;
        }
        scanf("%d", &stuNum);
    }
}