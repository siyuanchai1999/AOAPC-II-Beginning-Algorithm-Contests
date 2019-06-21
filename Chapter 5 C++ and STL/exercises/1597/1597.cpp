/*
This is a challenging and long question. The data structure is straightforward though. 
You need a 2D array of strings to store lines in every document, and you need the data structure explained in the question description (a map from string to DID)
some tricky points that take me a long time to debug:
1. mixture of cin and getline
    cin >> x doesn't get rid of the line feed afterward, typically a call of cin.ignore() or a dummy getline is needed before your real getline. 
    Yet,  note that on windows you get \r\n as line end cin.ignore() gets rid of one character in default, so you really need to push c.ignore to eliminate the annoying \r\n. 
2. set operations in std library helps a lot in doing the AND OR operation. 
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <sstream>

using namespace std;

set<int> setOfPair2setDocNo(set<pair<int, int> > & input){
    set<pair<int, int> >::iterator it = input.begin();
    set<int> result;
    for(; it != input.end(); it++){
        result.insert(it->first);
    }
    return result;
}

void showDocuments(vector<vector<string> >& documents){
    for(unsigned i = 0; i < documents.size(); i++){
        cout << "doc " << i << "----------" <<endl;
        for(unsigned j = 0; j < documents[i].size(); j++){
            cout << documents[i][j] << endl;
        }
    }
}

int main(){
   int N, M, docCnt = 0;
   cin >> N;
   cin.ignore(80, '\n');
   vector<vector<string> > documents;
   unordered_map<string, set<pair<int, int>> > tracker;
   while (docCnt < N)
   {
       vector<string> doc;
       string line;
       int lineCnt = 0;
       while (line[0] != '*' )
       {
            // parse the line, filter out characters that are not alphabetical
            doc.push_back(line);
            string word;
            bool startWord = false;
            for(unsigned  i = 0; i < line.length(); i++){
                if(startWord){
                    if(isalpha(line[i])){
                        word.push_back(tolower(line[i]));
                    }else{
                        tracker[word].insert(make_pair(docCnt, lineCnt));
                        // cout << word << endl;
                        startWord = false;
                        word = "";
                    }
                }else{
                    if(isalpha(line[i])){
                        word.push_back(tolower(line[i]));
                        startWord = true;
                    }else{
                        // skip this character
                    }
                }
            }
            //push the last unfinished word
            if(startWord){
                tracker[word].insert(make_pair(docCnt, lineCnt));
            }
            lineCnt++;
            getline(cin, line);
       }
    
       documents.push_back(doc);
       docCnt++;
    }

    cin >> M;
    cin.ignore(80, '\n');
    int m = 0;
    while(m++ < M){
        string line, w;
        getline(cin, line);
        istringstream liss(line);
        vector<string> command;
       
        while(liss >> w){
            command.push_back(w);
        }
        bool found = false;

        if(command.size() == 1){
            set<pair<int, int>>::iterator it = tracker[command[0]].begin();
            int lastDoc; 

            if(it != tracker[command[0]].end()){
                lastDoc = it->first;
            }

            for(; it != tracker[command[0]].end(); it++){
                if(it->first != lastDoc){
                    cout << "----------" << endl;
                    lastDoc = it->first;
                }
                found = true;
                cout << documents[it->first][it->second] << endl;
            }
        }else if(command.size() == 2){  //not case
            set<int> collection = setOfPair2setDocNo(tracker[command[1]]);

            bool isfirst = true;
            for(unsigned i = 0; i < documents.size(); i++){
                if(collection.find(i) == collection.end()){         //does not contain
                    //output a single doc
                    if(!isfirst) cout << "----------" << endl;
                    isfirst = false;
                    found = true;
                    for(unsigned j = 1; j < documents[i].size(); j++){
                        cout << documents[i][j] << endl;
                    }
                }
            }
        }else{
            set<int> collect0 = setOfPair2setDocNo(tracker[command[0]]);
            set<int> collect1 = setOfPair2setDocNo(tracker[command[2]]);
            set<int> feasible;
            if(command[1] == "AND"){
                set_intersection(collect0.begin(), collect0.end(), collect1.begin(), collect1.end(), inserter(feasible, feasible.begin()));
            }else{
                set_union(collect0.begin(), collect0.end(), collect1.begin(), collect1.end(), inserter(feasible, feasible.begin()));
            }

            set<pair<int, int>> whole;
            set_union(tracker[command[0]].begin(), tracker[command[0]].end(), tracker[command[2]].begin(), tracker[command[2]].end(), inserter(whole, whole.begin()));
            
            set<pair<int, int>>::iterator it = whole.begin();
            bool isfirst = true;
            int lastDoc;
            for(; it != whole.end(); it++){
                if(feasible.find(it->first) != feasible.end()){
                    if(isfirst){
                        lastDoc = it->first;
                        isfirst = false;
                    }else{
                        if(lastDoc != it->first){
                            cout << "----------" << endl; 
                            lastDoc = it->first;
                        }
                    }

                    found = true;
                    cout << documents[it->first][it->second] << endl;
                }
            }
        }

        if(!found) cout << "Sorry, I found nothing." << endl;

        cout << "==========" << endl;
    }

}