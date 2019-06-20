#include <bits/stdc++.h> 

using namespace std;

string parseEmail(string emailadd){
    istringstream iss(emailadd);
    string result;
    while(getline(iss,result, '@'))
        ;
    return result;
}

int main(){
    // unordered_map<string, unordered_set<string> > database;
    unordered_set<string> database;
    string next, MTAsite, username;
    int userNum;
    cin >> next;
    while(next == "MTA"){
        cin >> MTAsite;
        cin >> userNum;
        while(userNum-- > 0){
            cin >> username;
            username.push_back('@');
            username = username + MTAsite;
            database.insert(username);
        }
        cin >> next;
    }

    cin >> next;
    string sender;

    while(next[0] != '*'){
        vector<string> MTAlists;
        unordered_map<string, vector<string> > receiverlib;
        unordered_set<string> receiverTracker;
        vector<string> messages;

        sender = next;
        string senderSite = parseEmail(sender);

        cin >> next;
        while(next[0] != '*'){
            string sitename = parseEmail(next);
            if(receiverlib[sitename].size() == 0){
                MTAlists.push_back(sitename);
            }
            if(receiverTracker.find(next) == receiverTracker.end()){
                receiverlib[sitename].push_back(next);
            }
            receiverTracker.insert(next);
            
            cin >> next;
            // cout << next << endl;
        }

        getline(cin, next);
        getline(cin, next);
        while(next[0] != '*'){
            // cout << "msg is ";
            // cout << next << endl;
            messages.push_back(next);
            getline(cin, next);
        } 

        cin >> next;

        //output session
        for(int i = 0; i < MTAlists.size(); i++){
            cout << "Connection between " << senderSite << " and " << MTAlists[i] << endl;
            cout << "     " << "HELO " << senderSite << endl;
            cout << "     " << "250" << endl;
            cout << "     " << "MAIL FROM:<" << sender << ">" << endl;
            cout << "     " << "250" << endl;

            vector<string> localReceivers = receiverlib[MTAlists[i]];
            bool validreceive = false;
            for(int j = 0; j < localReceivers.size(); j++){
                cout << "     " << "RCPT TO:<" << localReceivers[j] << ">" << endl;
                if(database.find(localReceivers[j]) == database.end()){
                    cout << "     " << "550" << endl;
                }else{
                    validreceive = true;
                    cout << "     " << "250" << endl;
                }
            }

            if(validreceive){
                // cout << messages.size() << endl;
                cout << "     " << "DATA" << endl;
                cout << "     " << "354" << endl;
                for(int i = 0; i < messages.size(); i++){
                    cout << "     " << messages[i] << endl;
                }
                cout << "     " << '.' << endl;
                cout << "     " << "250" << endl;
            }

            cout << "     " << "QUIT" << endl;
            cout << "     " << "221" << endl;
            
        }

    }

    
}