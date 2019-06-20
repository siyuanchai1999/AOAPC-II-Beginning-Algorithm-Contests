#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

void output(vector<string> &input){
    cout << input[0];
    for(int i = 1; i < input.size(); i++){
        cout << ',' << input[i];    
    }
    cout << endl;
}

int main(){
    int T, t = 0;
    cin >> T;
    cin.ignore();
    while(t++ < T){
        string lineA, lineB;
        map<string, string> mapA, mapB;

        cin >> lineA;
        cin >> lineB;
        lineA.erase(lineA.begin());
        lineA.pop_back();
        lineB.erase(lineB.begin());
        lineB.pop_back();

        istringstream Aiss(lineA);
        istringstream Biss(lineB);

        string key, value;
        while (getline(Aiss, key, ':'))
        {
            getline(Aiss, value, ',');
            mapA[key] = value;
            // cout << key << '\t' << value << '\t';
        }

        while (getline(Biss, key, ':'))
        {
            getline(Biss, value, ',');
            mapB[key] = value;
            // cout << key << '\t' << value << '\t';
        }
        
        map<string, string>::iterator itA = mapA.begin();
        map<string, string>::iterator itB = mapB.begin();

        vector<string> added, changed, removed;

        for(; itA != mapA.end(); itA++){
            string keyA = itA->first;
            string valA = itA->second;
            if(mapB.find(keyA) != mapB.end()){
                if(mapB[keyA] != valA){
                    changed.push_back(keyA);
                }
            }else{
                removed.push_back(keyA);
            }
        }

        for(; itB != mapB.end(); itB++){
            if(mapA.find(itB->first) == mapA.end()){
                added.push_back(itB->first);
            }
        }
        
        if(!added.empty()){
            cout << '+';
            output(added);
        } 
        if(!removed.empty()){
            cout << '-';
            output(removed);
        } 
        if(!changed.empty()){
            cout << '*';
            output(changed);
        }

        if(added.empty() && removed.empty() && changed.empty()){
            cout << "No changes" << endl;
        }
        
        cout << endl;
        
    }
}