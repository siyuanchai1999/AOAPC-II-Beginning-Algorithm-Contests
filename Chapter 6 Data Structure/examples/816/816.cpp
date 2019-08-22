/*
Very important question as marked in the book. Use BFS to generate next-step search object (ptr).
backtracking with pointer to print the final result.
*/


#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string.h>
#define MAXSIZE 10
using namespace std;

string directions = "NSEW";
string turning = "LFR";

//row and column update given direction d: (curRow + rowUpdate[d], curCol + colUpdate[d])
const int rowUpdate[4] = {-1, 1, 0, 0};
const int colUpdate[4] = {0, 0, 1, -1};

//encoding of next direction as nextDir[d][t] given d is the current direction and t is the turning method
const int nextDir[4][3] = {
    {3, 0, 2},
    {2, 1, 3},
    {0, 2, 1},
    {1, 3, 0}
};

//encoding of directions to numbers
unordered_map<char, int> dir2index({
    {'N', 0}, {'S', 1}, {'E', 2}, {'W', 3}
});

//encoding of turns to numbers
unordered_map<char, int> turn2index({
    {'L', 0}, {'F', 1}, {'R', 2}    
});

//MAXSIZE rows * MAXSIZE cols * 4 directions * 3 turns; true when r row, c column, coming to d direction and make t turn is valid.
bool infoMap[MAXSIZE][MAXSIZE][4][3];
bool searched[MAXSIZE][MAXSIZE][4];

//reinitialize the info map
void searchAgain(){
    memset(infoMap, 0, sizeof(infoMap));
    memset(searched, 0, sizeof(searched));
}

struct Node{
    int r, c, dir;
    Node* prev;
    Node(int r, int c, int d, Node * prev){
        this->r = r;
        this->c = c;
        this->dir = d;
        this->prev = prev;
    }

    // for debugging reason only 
    string toString(){
        string result = '(' + to_string(r) + ',' + to_string(c) + ')' +  '\t' + to_string(dir) ;
        return result;
    }
};

vector<Node*> toClear;
int startR, startC, endR, endC;
char startD;

/*
helper function to generate next step search pointer
*/
Node* makeTurn(Node* curNode, int turn){
    int nextDirection = nextDir[curNode->dir][turn];
    return new Node(curNode->r + rowUpdate[nextDirection],
                curNode->c + colUpdate[nextDirection],
                nextDirection, curNode);
}

//BFS to find the shortest path. Return the endNode when there's a valid path NULL if no solution exists (BFS finishes but goal position not reached)
Node* BFS(){
    int startDindex = dir2index[startD];
    Node* initNode = new Node(startR, startC, startDindex, NULL);
    Node* startNode = new Node(startR + rowUpdate[startDindex], startC + colUpdate[startDindex], 
                                startDindex, initNode);
    toClear.push_back(initNode);
    toClear.push_back(startNode);
    // cout << "startNode :" << startNode->toString() << endl;
    queue<Node *> q;
    q.push(startNode);
    while (!q.empty()){
        Node * curNode = q.front();
        q.pop();
        if(curNode->r == endR && curNode->c == endC) return curNode;
        for(int t = 0; t < 3; t++){
            if(infoMap[curNode->r][curNode->c][curNode->dir][t] && !searched[curNode->r][curNode->c][curNode->dir]){
                Node * newNode = makeTurn(curNode, t);
                // cout << newNode->toString() << endl;
                toClear.push_back(newNode);
                q.push(newNode);
            }
        }
        searched[curNode->r][curNode->c][curNode->dir] = true;
    }
    return NULL;
}

void show(Node * endNode, string& name){
    cout << name << endl;
    if(endNode == NULL) cout << "  No Solution Possible" << endl;
    
    Node * curNode = endNode;
    vector<Node *> toPrint;
    while (curNode != NULL){
        
        // cout << ' ' << '(' << curNode->r << ',' << curNode->c << ')';
        toPrint.push_back(curNode);
        curNode = curNode->prev;
    }

    //use vector as container of all the poniter to display
    //we don't use recursion because of the danger of stackoverflow
    int cnt = 0;
    for(int i = toPrint.size() - 1; i >= 0 ; i--){
        if(cnt % 10 == 0 ) cout << ' ';
        cout << ' ' << '(' << toPrint[i]->r << ',' << toPrint[i]->c << ')';
        if(cnt++ % 10 == 9) cout << endl;
    }
    if(toPrint.size() % 10 != 0) cout << endl;
}

void clearAll(){
    for(unsigned i = 0; i < toClear.size(); i++){
        free(toClear[i]);
    }
    toClear.clear();
}

int main(){
    cout.sync_with_stdio(false);
    cin.sync_with_stdio(false);
    string mazeName;
    cin >> mazeName;
    while (mazeName != "END"){
        cin >> startR >> startC >> startD >> endR >> endC;
        searchAgain();
        int r, c;
        cin >> r;
        while(r != 0){
            cin >> c;
            string input;
            cin >> input;
            while (input[0] != '*'){
                int dir = dir2index[input[0]];
                for(unsigned i = 1; i < input.size(); i++){
                    infoMap[r][c][dir][turn2index[input[i]]] = 1;
                }
                cin >> input;
            }
            
            cin >> r;
        }
        Node* endNode = BFS();
        show(endNode, mazeName);
        clearAll();
        cin >> mazeName;
    }
    
}