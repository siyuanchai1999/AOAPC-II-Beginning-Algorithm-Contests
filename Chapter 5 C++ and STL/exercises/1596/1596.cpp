/*
Hint & solution
once you decided your data structure this is a easy problem to solve
We need to imitate the behavior of vector in c++ but cannot use vector directly because of the danger of overflow
I self-define a structure arr illustrated below

The eval function evaluates the expression inside '[]' recursively, raising -1 if error occur.

*/


#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;

struct arr{
    int size;               
    unordered_map<int, int> valueTracker;
    unordered_set<int> referenced;          //check a value has been referened
};
unordered_map<string, arr> str2arr;

int eval(string input){
    istringstream iss(input);
    string name;
    getline(iss, name, '[');
    if(name.length() != input.length()){        // contain [] pair
        string strInside;
        getline(iss, strInside, ']');

        int insideVal = eval(strInside);
        if(insideVal >= 0 && insideVal < str2arr[name].size){            //access element out of scope
            if(str2arr[name].referenced.find(insideVal) != str2arr[name].referenced.end()){         //access element already assigned
                return str2arr[name].valueTracker[insideVal];
            }else{
                return -1;
            }                                                  
        }else{
            return -1;
        }
    }else{                                      //doesn't contain [] pair
        return stoi(input);
    }
}

int main(){
    string line;
    getline(cin , line);
    while(line[0] != '.'){
        int l = 0;
        bool nobug = true;
        while(line[0] != '.' && nobug){
            // cout << line << endl;
            string left, right, name, num;
            istringstream iss(line);
            getline(iss, left, '=');
            istringstream leftstream(left);
            
            if(left.length() != line.length()){             //assignment command
                getline(iss, right);
                istringstream rightstream(right);
                int rightVal = eval(right);
                if(rightVal >= 0){
                    getline(leftstream, name, '[');
                    getline(leftstream, num, ']');
                    int leftIndex = eval(num);
                    if(leftIndex >= 0 && leftIndex < str2arr[name].size){
                        str2arr[name].valueTracker[leftIndex] = rightVal;
                        str2arr[name].referenced.insert(leftIndex);
                    }else{                                                      //reference value out of scope
                        nobug = false;
                    }
                }else{                                                  //error with the value assignment
                    nobug = false;
                }
            
            }else{                                                //declaration command
                getline(leftstream, name, '[');
                getline(leftstream, num,   ']');
                arr temp = {stoi(num)};
                str2arr[name] = temp;
            }
            l++;
            getline(cin, line);
        }
        cout << (nobug ? 0 : l) << endl;
        while(line[0] != '.'){
            getline(cin, line);
        }
        getline(cin, line);
    }
}
