#include <iostream>
#include <algorithm>
#include <sstream>
#include <set>
#include <unordered_map>

using namespace std;

struct book{
    string bookname;
    string author;
    bool operator < (const book rhs) const{
        return author < rhs.author || (author == rhs.author && bookname < rhs.bookname);
    }
};

int main(){
    string line;
    getline(cin, line);
    set<book> onShelv;
    set<book> returnlist;
    unordered_map<string, string> book2author;
    string skip;

    while(!(line[0] == 'E' && line[1] == 'N' && line[2] == 'D')){       //line != "END"
        // cout << line;
        // cout << '\t' << line.length() << endl;
        book b = {};
        istringstream iss(line);
        getline(iss, skip, '"');
        getline(iss, b.bookname, '"');
        iss >> skip; //ignore by
        getline(iss, b.author);

        onShelv.insert(b);
        book2author[b.bookname] = b.author;
        getline(cin, line);
    }


    getline(cin, line);
    while(!(line[0] == 'E' && line[1] == 'N' && line[2] == 'D')){
        if(line[0] == 'S'){             //SHELVE
            set<book>::iterator it;
            for(it = returnlist.begin(); it != returnlist.end(); it++){
                pair<set<book>::iterator, bool> insertIt =  onShelv.insert(*it);

                cout << "Put " << '"' << it->bookname << '"';
                if(insertIt.first != onShelv.begin()){
                    cout << " after " << '"' << (--insertIt.first)->bookname << '"' << endl;  //get previous book
                }else{
                    cout << " first" << endl;
                }
            }
            returnlist.clear();
            cout << "END" << endl;

        }else{
            istringstream iss(line);
            getline(iss, skip, '"');
            book b = {};
            getline(iss, b.bookname, '"');
            b.author = book2author[b.bookname];
            if(line[0] == 'B'){         //BORROW
                onShelv.erase(b);
            }else if(line[0] == 'R'){       //RETURN    
                returnlist.insert(b);
            }
        }

        getline(cin, line);
    }
    

}