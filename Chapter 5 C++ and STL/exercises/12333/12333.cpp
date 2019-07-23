/*
Not fairly complicated question.
A big Integer sketch is used to compute the fibonacci series in high precision.
The first 40 of each result is inserted into a trie which makes lookup much easier. 
    
 */


#include <iostream>
#include <vector>
#include <limits>
#define BRANCHNUM 10
#define FIBNUM 100000
using namespace  std;

struct trieNode{
    int val;
    vector<trieNode *> branches;
    trieNode(){
        val = INT32_MAX; 
        branches = vector<trieNode *>(BRANCHNUM, NULL);
    }
};

struct trie
{
    trieNode * root;
    trie(){
        root = new trieNode();
    }

    void insert(string sequence, int index){
        trieNode * curNode = this->root;
        for(unsigned i = 0; i < sequence.length(); i++){
            int pos = sequence[i] - '0';
            if(curNode->branches[pos] == NULL){
                trieNode * temp = new trieNode();
                curNode->branches[pos] = temp;
                curNode = temp;
            }else{
                curNode = curNode->branches[pos];
            }
            curNode->val = min(curNode->val, index);
        }
    }

    int search(string toSearch){
        trieNode * curNode = this->root;
        for(unsigned i = 0; i < toSearch.length(); i++){
            int pos = toSearch[i] - '0';
            if(curNode->branches[pos] == NULL){
                return -1;
            }else{
                curNode = curNode->branches[pos];
            }
        }
        return curNode->val;
    }
};

struct bigInt
{
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> vals;

    bigInt (long num){
        vals.clear();
        do
        {
            vals.push_back(num % BASE);
            num = num/ BASE;

        } while (num > 0);

    }

    bigInt (const string s){
        vals.clear();
        int x, len = (s.length() - 1)/ WIDTH + 1;
        for(int i = 0; i < len; i++){
            int end = s.length() - i* WIDTH;
            int start = max(0, end - WIDTH);
            x = stoi(s.substr(start, end - start));
            vals.push_back(x);
        }
    }

    bigInt operator+(const bigInt & rhs){
        bigInt c(0);
        c.vals.clear();
        int x = 0, len = max(this->vals.size(), rhs.vals.size());
        for(int i = 0; i < len || x != 0 ; i++){
            if(i < int(this->vals.size())) x += this->vals[i];
            if(i < int(rhs.vals.size())) x += rhs.vals[i];
            c.vals.push_back(x % BASE);
            x = x / BASE;
        }
        return c;
    }
    
    void print(){
        cout << vals.back();
        string x, result;
        for (int i = vals.size() - 2; i >= 0; i--)        {
            x = to_string(vals[i]);
            x = string(WIDTH - x.length(), '0') + x;
            result += x;
        }
        cout << result << endl;
    }

    string toString(){
        int cnt = 0;
        string result = to_string(vals.back());
        string temp;
        for (int i = vals.size() - 2; i >= 0 && cnt < 6; i--, cnt++)
        {
            temp = to_string(vals[i]);
            temp = string(WIDTH - temp.length(), '0') + temp;
            result = result + temp;
        }
        if(result.length() > 40){
            return result.substr(0, 40);
        }else{
            return result;
        }
    }
};

int main(){
    bigInt arr[2] = {bigInt(1), bigInt(1)};
    trie t = trie();
    t.insert("1", 0);
    for(int i = 2; i < FIBNUM; i++){
        bigInt temp = arr[0] + arr[1];
        arr[i%2] = temp;
        // cout << temp.toString() << endl;
        t.insert(temp.toString(), i);
        // temp.print();
    }

    int T, te = 0;
    string input;
    cin >> T;
    while (te++ <T)
    {
        cin >> input;
        cout << "Case #" << te << ": " << t.search(input) << endl;
    }
    
}
