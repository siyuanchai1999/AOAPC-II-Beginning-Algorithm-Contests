#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

const int MAXTEAM = 1000;

int main(){
    int team_num, team_len, val, cnt = 0;
    std::ios::sync_with_stdio(false);
    string command;
    cin >> team_num;
    while(team_num != 0){
        cout << "Scenario #" << ++cnt << endl;
        
        queue<int> container[MAXTEAM];
        queue<int> pop_tracker;
        unordered_map<int, int> teamFinder;

        for(int i = 0; i < team_num; i++){
            cin >> team_len;
            while(team_len-- > 0){
                cin >> val;
                teamFinder[val] = i;
            }
        }
        
        cin >> command;
        while(command[0] != 'S'){
            if(command[0] == 'E'){
                cin >> val;
                if(container[teamFinder[val]].empty()) pop_tracker.push(teamFinder[val]);
                container[teamFinder[val]].push(val);
            }else if(command[0] == 'D'){
                int pos = pop_tracker.front();
                cout << container[pos].front() << endl;
                container[pos].pop();
                if(container[pos].empty()) pop_tracker.pop();
            }
            cin >> command;
        }
        cout << endl;
        cin >>team_num;
    }
    
}