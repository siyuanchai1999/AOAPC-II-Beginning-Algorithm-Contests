/*
Hints and explanation:
use a queue to simulate the behavior of the printing queue
use a vector to hold all values of priority number

we know that jobs with higher priority number must be printed earlier
the sorted vector indicates the sequence of priority number of printed jobs
v[i] represents the priority number that should be printed in the next

A event at the front of the queue is printed only if it has same the priority number with v[i]

Whenever we find a job has the same priority number with v[i] and time == m
We finish our job
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

struct event{
    int time;
    int priority;
    bool operator < (const event &rhs) const{
        return priority > rhs.priority || (priority == rhs.priority && time < rhs.time);       
    }
};

void showvector(vector<int> &v){
    for(unsigned int i = 0; i < v.size(); i++){
        cout << v[i] << '\t';
    }
    cout << endl;
}
int main(){
    int T;
    int n, m;
    scanf("%d", &T);
    while(T-- > 0){
        scanf("%d %d", &n, &m);
        vector<int> sequence;
        queue<event> printQueue;

        for(int i = 0; i < n; i++){
            event newEvent = {};
            newEvent.time = i;
            scanf("%d", &newEvent.priority);
            sequence.push_back(newEvent.priority);
            printQueue.push(newEvent);
        }

        sort(sequence.begin(), sequence.end());         //sort in descending order
        reverse(sequence.begin(), sequence.end());

        //showvector(sequence);
        int i = 0;
        while(!printQueue.empty()){
            int t = printQueue.front().time;
            int p = printQueue.front().priority;
            printQueue.pop();

            if(p == sequence[i]){           //front job is printed
                i++;
                if(t == m) break;           //front printed job is our target job
            }else{
                event e = {t, p};
                printQueue.push(e);
            }
        }
        cout << i << endl;
        
    }
}