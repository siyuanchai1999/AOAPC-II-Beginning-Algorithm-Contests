/*
simulation of binary tree
 */

#include <iostream>
#include <queue>
#include <limits>
using namespace std;

struct node{
    bool assigned;
    int val;
    node* left;
    node* right;

    node(): assigned(false), left(NULL), right(NULL){}
};

struct binaryTree{
    node* root;
    int rem;
    binaryTree(){
        root = new node();
        rem = 1;
    }

    //return true when value assignment is correctly specified (the target node is not assigned)
    bool addNode(string seq, int val){
        node* curNode = root;
        for(unsigned i = 0; i < seq.length(); i++){
            if(seq[i] == 'L'){
                if(curNode->left == NULL){
                    curNode->left = new node();
                    rem++;
                }
                curNode = curNode->left;
            }else{
                if(curNode->right == NULL){
                    curNode->right = new node();
                    rem++;
                }
                curNode = curNode->right;
            }

        }

        if(curNode->assigned){
            rem = INT32_MAX;
            return false;
        }else{
            curNode->assigned = true;
            curNode->val = val;
            // cout << "assign " << val << " "  + seq << endl;
            rem--;
            return true;
        }
    }

    void traverse(){
        if(rem > 0){
            // cout << rem << endl;
            cout << "not complete" << endl;
        }else{
            queue<node *> q;
            node* f = root;
            cout << f->val;
            if(f->left != NULL) q.push(f->left);
            if(f->right != NULL) q.push(f->right);

            while (!q.empty()){
               f = q.front();
               q.pop();
               cout << ' ' << f->val;
               if(f->left != NULL) q.push(f->left);
               if(f->right != NULL) q.push(f->right);
            }
            cout << endl;
        }
    }
};


int main(){
    cin.sync_with_stdio(false);
    string input;
    binaryTree bt = binaryTree();
    bool complete = true;
    while (cin >> input){
        if(input[1] == ')'){
            bt.traverse();
            complete = true;
            bt = binaryTree();
        }else if(complete){
            size_t commaPos = input.find(',');
            size_t paraPos = input.find(')');
            string seq = input.substr(commaPos + 1, paraPos - commaPos - 1);
            int val = stoi(input.substr(1, commaPos - 1));
            complete = bt.addNode(seq, val);
        }
        
    }
    
}
