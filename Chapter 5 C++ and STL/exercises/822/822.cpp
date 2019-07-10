#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#define INTMAX INT32_MAX  
using namespace std;

struct task
{
    int tid, duration;
    queue<int> sequence;
    bool isDone(){
        return sequence.empty();
    }
    int getNext(){
        if(!isDone()){
            return sequence.front();
        }
        return INTMAX;
    }
};

struct staff
{
    int sid, avTime, last, earlyJobTime, earlyJobId, topJobId;
    vector<int> skills;

    bool operator < (const staff & rhs){
        if(avTime != rhs.avTime ){
            return avTime < rhs.avTime;
        }else if(last != rhs.last){
            return last < rhs.last;
        }else{
            return sid < rhs.sid;
        }
    }

    void setEarliestJob(unordered_map<int, task> &id2task){
        int eJob = id2task[skills[0]].getNext(), curJob;
        int eJobId = skills[0];

        for(unsigned i = 0; i < skills.size(); i++){
            curJob = id2task[skills[i]].getNext();
            if(curJob < eJob){
                eJob = curJob;
                eJobId = skills[i];
            }
        }
        earlyJobTime = eJob;
        earlyJobId = eJobId;
    }
    void setPiriority(unordered_map<int, task> &id2task){
        int topJobTime;
        for (unsigned i = 0; i < skills.size(); i++)
        {
            topJobTime = id2task[skills[i]].getNext();
            if(topJobTime != INTMAX && topJobTime <= avTime){
                topJobId = skills[i];
                break;
            }
        }
        
    }
};


int main(){
    int TaskNum, staffNum, scenarioCnt = 0;
    
    while (cin >> TaskNum && TaskNum)
    {
        int t = 0, s = 0;
        unordered_map<int, task> id2task;
        vector<staff> workers;
        while (t++ < TaskNum)   
        {
            task t;
            int id, num, offset, duration, gap;
            cin >> id >> num >> offset >> duration >> gap;
            t.tid = id;
            t.duration = duration;
            for(int i = 0; i < num; i++){
                t.sequence.push(offset + gap * i);
            }
            id2task[id] = t;
        }

        cin >> staffNum;
        while (s++ < staffNum )
        {
            staff s;
            cin >> s.sid;
            s.avTime = 0; s.last = -1;
            int skillCnt, sk;
            cin >> skillCnt;
            for(int i = 0; i < skillCnt; i++){
                cin >> sk;
                s.skills.push_back(sk);
            }
            if(skillCnt > 0){
                s.setEarliestJob(id2task);
                workers.push_back(s);
                // cout << s.sid <<  " has earliest job " << s.earlyJobId<< " at " << s.earlyJobTime << endl;
            }
            
            // pq.push(s);
        }

        int totalTime = 0; 
        while (workers.size() > 0 )
        {
            sort(workers.begin(), workers.end());
            staff *topStaff = &workers[0];
            // pq.pop();
            if(topStaff->earlyJobTime > topStaff->avTime) // no job is coming
            {
                topStaff->avTime = topStaff->earlyJobTime;
            }else
            {
                // handle this job
                topStaff->setPiriority(id2task);
                // cout << topStaff->sid;
                // cout << " Handling " << topStaff->topJobId << " at " << topStaff->avTime << endl;

                topStaff->last = topStaff->avTime;
                int duration = id2task[topStaff->topJobId].duration;
                topStaff->avTime = topStaff->avTime + duration;
                id2task[topStaff->topJobId].sequence.pop();
                
                totalTime = max(totalTime, topStaff->avTime);

                for(unsigned i = 0; i < workers.size(); i++){
                    workers[i].setEarliestJob(id2task);
                    // cout << "staff " << workers[i].sid << " has earlyjobtime " << workers[i].earlyJobTime <<  " available at " << workers[i].avTime <<  endl; 
                    if(workers[i].earlyJobTime == INTMAX){
                        // cout << "Remove " << workers[i].sid << " from list" << endl;
                        
                        workers.erase(workers.begin() + i);
                         //remove elements in vector in the loop needs to handle the iterator correctly
                        i--;

                    }
                }
                
            }
            
        }

        cout << "Scenario " << ++scenarioCnt << ": All requests are serviced within ";
        cout << totalTime << " minutes." << endl;
       
    }
    return 0;

}