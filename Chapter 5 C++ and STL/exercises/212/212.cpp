/*
This problem has somewhat complication but its main diffculty falls in its blurred requirement and unspecified output format.
It's intuitive that you can have a priority queue (opRooms) that keeps track of of a pairof <availableTime, opRoom>. The top choice is the operation room that is going to be assigned for the next patient. 
Note that as long as we know the time that a patient enters surgery room, we know their time they finish surgery, begin recovery and finish recovery. The only thing remain the bed number.
To keep track of a list of pairs of bed available time and bed numbers. We also a priority queue of pairs (the time when patient leaves op room, his op room number). For every patient, they always pick the bed with lowest number.
Note that the input is garanteed to eliminate the waiting time for recovery beds.
Several tips for the question:
1. It is the time when patient leaves operation room that we choose a recovery bed.
2. The second factor to consider when two patients leave their room simulatanenously is their operation room number but not roster number.
3. The ouput format plays well with setw function. Referred to the code if needs further instruction about the format. 
 */

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <unordered_map>

using namespace std;

struct patient
{
    string name;
    int surTime, recTime;
    int room, opBegin, opEnd;
    int bed,recBegin, recEnd;
};

void printTime(int startHour, int time){
    int hour = startHour + time/60;
    cout << std::right << setw(2) << hour << ':';
    int minute = time %60;
    if(minute < 10) cout << '0';
    cout << minute;
}

void printTable(vector<patient> & patientVec, int startHour){
    cout << " Patient          Operating Room          Recovery Room" << endl;
    cout << " #  Name     Room#  Begin   End      Bed#  Begin    End" << endl;
    cout << " ------------------------------------------------------" << endl;


    for (unsigned i = 0; i < patientVec.size(); i++)
    {
        cout << std::right << setw(2) << i + 1 << "  ";
        cout << std::left  << setw(8) << patientVec[i].name;
        cout << std::right << setw(4) << patientVec[i].room << "   ";
        printTime(startHour, patientVec[i].opBegin);
        cout << "   ";
        printTime(startHour, patientVec[i].opEnd);
        cout << std::right << setw(7)<< patientVec[i].bed << "   ";
        printTime(startHour, patientVec[i].recBegin);
        cout << "   ";
        printTime(startHour, patientVec[i].recEnd);
        cout << endl;
    }
    
}

int main(){
    int opNum, recNum, startTime, transTime, opPrepTime, recPrepTime, patientNum;
    while(cin >> opNum >> recNum >> startTime >> transTime >> opPrepTime >> recPrepTime >> patientNum){
    
    vector<patient> patientVec;

    for (int i = 0; i < patientNum; i++)
    {
        patient p;
        cin >> p.name >> p.surTime >> p.recTime;
        patientVec.push_back(p);
    }

    //records the time duration that each room is in use; helpful for the second table output
    vector<int> room2time(opNum + 1, 0);

    //priority queue of pairs (roomAvailableTime, roomId)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> opRooms;
    for(int i = 1; i <= opNum; i++){
        opRooms.push(make_pair(0, i));
    }

    //records the time duration that each bed is in use; helpful for the second table output
    vector<int> bed2time(recNum + 1, 0);
    
    vector<pair<int, int>> recBeds;  // <available time, bedId>
    // priority_queue<pair<int, int>, , greater<pair<int, int>>> recBeds;
    for(int i = 1; i <= recNum; i++){
        recBeds.push_back(make_pair(0, i));
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> recPatients;
    unordered_map<int, queue<int>> room2id;
    int maxTime = 0;
    int t = 0, pid = 0; 
    while (pid < patientNum)
    {
        if(opRooms.top().first <= t){
            pair<int, int> topRoom = opRooms.top();
            opRooms.pop();
            patientVec[pid].room = topRoom.second;
            room2id[topRoom.second].push(pid);
            room2time[topRoom.second] += patientVec[pid].surTime;
            maxTime = max(maxTime, room2time[topRoom.second]);

            patientVec[pid].opBegin = t;
            patientVec[pid].opEnd = t + patientVec[pid].surTime;
            topRoom.first = patientVec[pid].opEnd + opPrepTime;
            patientVec[pid].recBegin = patientVec[pid].opEnd + transTime;
            patientVec[pid].recEnd = patientVec[pid].recBegin + patientVec[pid].recTime;
            opRooms.push(topRoom);
            recPatients.push(make_pair(patientVec[pid].opEnd, patientVec[pid].room));
            pid++;
        }
        t = opRooms.top().first;
    }

    int totalTime = 0;
    while (!recPatients.empty())
    {
        pair<int, int> firstPatient = recPatients.top();
        recPatients.pop();
        for(unsigned i = 0; i < recBeds.size(); i++){
            if(recBeds[i].first <= firstPatient.first){
                int pos = room2id[firstPatient.second].front();
                room2id[firstPatient.second].pop();
                patientVec[pos].bed = recBeds[i].second;
                recBeds[i].first =  patientVec[pos].recEnd + recPrepTime;
                
                totalTime = max(totalTime, patientVec[pos].recEnd);
                bed2time[patientVec[pos].bed] += patientVec[pos].recTime;

                maxTime = max(maxTime, bed2time[patientVec[pos].bed]);
                break;
            }
        }
    }
    printTable(patientVec, startTime);
    cout << endl;
    
    cout << "Facility Utilization" << endl;
    cout << "Type  # Minutes  % Used" << endl;
    cout << "-------------------------" << endl;
    double tTime = double(totalTime);
    for (size_t i = 1; i < room2time.size(); i++)
    {
        cout << "Room " << std::right <<setw(2) << i;
        cout << std::right << setw(8) <<  room2time[i];
        cout << std::right << std::fixed  << setw(8) << setprecision(2) <<  double(room2time[i])/tTime * 100 << endl;
    }

    for (size_t i = 1; i < bed2time.size(); i++)
    {
        cout << "Bed  " << std::right << setw(2) << i ;
        cout << std::right << setw(8) << bed2time[i] ;
        cout  <<  std::right << setw(8) << double(bed2time[i])/tTime * 100 << endl;
    }
    cout << endl;
    }
}