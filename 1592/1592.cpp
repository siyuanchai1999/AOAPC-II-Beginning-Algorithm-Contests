#include <iostream>
#include <unordered_map>
#include <string>
#include <map>

using namespace std;

unordered_map<string, pair<int, int> > m;
map<pair<int, int>, int> cols2rows;

void print_map(unordered_map<string, pair<int, int> > m){
    cout << endl;
    unordered_map<string, pair<int, int> >:: iterator it = m.begin();
    for(;it != m.end(); it++){
        cout << it->first << " => " << '(' << (it->second).first << ' ' << (it->second).second << ')' << endl;
    }
    cout << endl;
}
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
                
                if(m.find(str) != m.end()){
                    // cout << "overlap with"<< m[str].first << '\t' << m[str].second << endl;
                    if(m[str].second  == cnt){
                        pair<int, int> p = make_pair(m[str].first, r);
                        
                        if(cols2rows.find(p) != cols2rows.end() ){                         //already 
                            if(!redundant){
                               printf("NO\n");
                               printf("%d %d\n", p.first, p.second);
                               printf("%d %d\n", cols2rows[p], cnt); 
                            } 
                            redundant = true;
                        }else{
                            cols2rows[p] = cnt;
                        }
                    }
                }else{
                    // cout << str << endl;
                    // cout << " => " << '(' << r << ' ' << cnt << "))" << endl;
                    m[str] = make_pair(r,cnt);
                }
            }
            
            
        }
        m.clear();
        cols2rows.clear();
        if(!redundant) printf("YES\n");
        redundant = false;
    }
    
    
    return 0;
    
}