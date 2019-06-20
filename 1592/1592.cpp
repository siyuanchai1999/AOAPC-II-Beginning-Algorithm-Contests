#include <iostream>
#include <unordered_map>
#include <string>
#include <map>
#include <vector>

using namespace std;

// unordered_map<string, pair<int, int> > m;
// map<pair<int, int>, int> cols2rows;

void print_map(unordered_map<string, pair<int, int> > m){
    cout << endl;
    unordered_map<string, pair<int, int> >:: iterator it = m.begin();
    for(;it != m.end(); it++){
        cout << it->first << " => " << '(' << (it->second).first << ' ' << (it->second).second << ')' << endl;
    }
    cout << endl;
}

// int main(){
//     int R, C;
//     char sperate = ',';
//     string str_R, str_C;
//     string str;
//     bool redundant = false;
//     while(getline(cin, str_R, ' ') && getline(cin, str_C)){
//         R = stoi(str_R);
//         C = stoi(str_C);
//         for(int r = 1; r <= R; r++){
//             for(int cnt =1; cnt <= C ; cnt++){
//                 if(cnt!= C){
//                     getline(cin,str, sperate);
//                 }else{
//                     getline(cin,str);
//                 }
//                 // cout << str << endl;
                
//                 if(m.find(str) != m.end()){
//                     // cout << "overlap with"<< m[str].first << '\t' << m[str].second << endl;
//                     if(m[str].second  == cnt){
//                         pair<int, int> p = make_pair(m[str].first, r);
//                         cout << str << "  appear in same col" << '\t' << "row: " << m[str].first << '\t' << r << endl;
//                         if(cols2rows.find(p) != cols2rows.end() ){                         //already 
//                             cout << "already appear" << endl;
//                             if(!redundant){
//                                printf("NO\n");
//                                printf("%d %d\n", p.first, p.second);
//                                printf("%d %d\n", cols2rows[p], cnt); 
//                             } 
//                             redundant = true;
//                         }else{
//                             cols2rows[p] = cnt;
//                         }
//                     }
//                 }else{
//                     m[str] = make_pair(r,cnt);
//                 }
//             }
            
//         }
//         m.clear();
//         cols2rows.clear();
//         if(!redundant) printf("YES\n");
//         redundant = false;
//     }
    
    
//     return 0;
    
// }

unordered_map<string, vector<pair<int, int> > > m;
map<pair<int, int>, int> cols2rows;

int main(){
    int R, C;
    char sperate = ',';
    string str_R, str_C;
    string str;
    bool redundant = false;
    while(getline(cin, str_R, ' ') && getline(cin, str_C)){
        R = stoi(str_R);
        C = stoi(str_C);
        for(int r = 1; r <= R; r++){
            for(int cnt =1; cnt <= C ; cnt++){
                if(cnt!= C){
                    getline(cin,str, sperate);
                }else{
                    getline(cin,str);
                }
                // cout << str << endl;
                
                for(int i = 0; i < m[str].size(); i++){
                    pair<int ,int> pre_loc = m[str][i];
                    if(pre_loc.second == cnt){          //in same column
                        pair<int, int> row_pair = make_pair(pre_loc.first, r);
                        if(cols2rows[row_pair] != 0){
                            if(!redundant){
                                cout << "NO" << endl;
                                cout << row_pair.first << ' ' << row_pair.second << endl;
                                cout << cols2rows[row_pair]  << ' ' << cnt << endl;
                            }
                            redundant = true;
                        }
                        cols2rows[row_pair] = cnt;
                    }
                }
                m[str].push_back(make_pair(r, cnt));
            }
            
        }
        m.clear();
        cols2rows.clear();
        if(!redundant) printf("YES\n");
        redundant = false;
    }
    
    
    return 0;
    
}