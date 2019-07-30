/*
Quick implementation of list; c++ list helps
Note that after list.insert(cur, val) operation, cur still pointing to the previous element.
Only change cur = list.begin() when input[i] == '[' and change cur = list.end() when input[i] == ']'
 */

#include <iostream>
#include <list>
using namespace std;

void showlist(list<char> & storage){
    list<char>::iterator it;
    for(it = storage.begin(); it != storage.end(); it++){
        cout << *it;
    }
    cout << endl;
}
int main(){
    
    string input;
    while (cin >> input)
    {
        list<char> storage;
        list<char>::iterator cur = storage.begin();
        for(unsigned i = 0; i < input.size(); i++){
            char c = input[i];
            if(c == '['){
                cur = storage.begin();
            }else if(c == ']'){
                cur = storage.end();
            }else{
                storage.insert(cur,c);
            }
        }
        showlist(storage);
    }
    
    // list<char> storage;
    // list<char>::iterator cur = storage.begin();
    // storage.insert(cur, 'a');
    // storage.insert(cur, 'b');
    // storage.insert(cur, 'c');
    // showlist(storage);
    
    
}