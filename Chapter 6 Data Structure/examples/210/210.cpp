#include <iostream>
#include <queue>
#include <vector>

using namespace std;

enum cmd{
    assign,
    print,
    lock,
    unlock,
    stop
};

struct statement
{
    cmd type;
    char var;
    int val;

    string toString(){
        return to_string(type) + " " + var + " " + to_string(val);
       
    }
};


int main(){
    int caseCnt, progCnt, quantum, i = 0;
    cin >> caseCnt;
    while (i++ < caseCnt)
    {
        vector<int> truthTable(26, 0);
        
        int timeTable[5];
        cin >> progCnt >> timeTable[0] >> timeTable[1] >>timeTable[2] >> timeTable[3] >>timeTable[4] >> quantum;
        int p = 0;
        deque<int> readyQ;
        queue<int> blockedQ;
        vector<queue<statement>> programs;

        while (p < progCnt){
            queue<statement> q;
            while (1){
                statement s;
                string in;
                cin >> in;

                if(in == "print"){
                    cin >> s.var;
                    s.type = print;
                }else if(in == "lock"){
                    s.type = lock;
                }else if(in == "unlock"){
                    s.type = unlock;
                }else if(in == "end"){
                    s.type = stop;
                }else{
                    s.type = assign;
                    s.var = in[0];
                    cin >> in;
                    cin >> s.val;
                }
                q.push(s);
                if(s.type == stop){
                    break;
                }
            }
            programs.push_back(q);
            readyQ.push_back(p++);
        }

        int lockedBy= -1;
        bool thrown = false;
        while (!readyQ.empty()){
            int curProg = readyQ.front();
            readyQ.pop_front();
            int t = 0;
            thrown = false;

            while (t < quantum && !programs[curProg].empty())
            {
                statement s = programs[curProg].front();
                // cout << curProg + 1 << '\t' <<  s.toString() << endl;
                if(s.type == assign){
                    // if(lockedBy == -1 || lockedBy == curProg){
                        truthTable[s.var - 'a'] = s.val;
                    
                    
                }else if(s.type == print){
                    cout << curProg + 1 << ": " << truthTable[s.var - 'a'] << endl;
                }else if(s.type == lock){
                    if(lockedBy != -1){
                        blockedQ.push(curProg);
                        thrown = true;
                        break;
                    }else{
                        lockedBy = curProg;
                    }
                }else if(s.type == unlock){
                    lockedBy = -1;
                    if(!blockedQ.empty()){
                        readyQ.push_front(blockedQ.front());
                        blockedQ.pop();
                    }
                }else if(s.type == stop){

                }

                programs[curProg].pop();
                t += timeTable[s.type];
            }
            if(!programs[curProg].empty() && !thrown){
                readyQ.push_back(curProg);
            }
            
        }
        if(i < caseCnt) cout << endl;

    }

    
}