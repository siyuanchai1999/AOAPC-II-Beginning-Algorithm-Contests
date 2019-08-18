/*
The core trick here is that the postOrder traversal places the root as the last element so that we can easily find the position of the root in inorder traversal.
We recursively find the root of the left and right subtree to build up the tree.
Then we can implement DFS to find the shortest path from root to leaf. 
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

struct node{
    int val;
    node* left;
    node* right;

    node():left(NULL), right(NULL){
    }
};

struct binaryTree{
    node* root;
    vector<int> Avec;
    vector<int> Bvec;
    int minPath = INT32_MAX;
    int minNode = INT32_MAX;

    binaryTree(string& lineA, string& lineB){
        stringstream Aiss(lineA);
        stringstream Biss(lineB);
        int x;
        while (Aiss >> x){
            Avec.push_back(x);
            Biss >> x;
            Bvec.push_back(x);
        }
        root = build(0, Avec.size() - 1, 0, Bvec.size() - 1 );
    }

    node* build(int Astart, int Aend, int Bstart, int Bend ){
        if(Astart > Aend) return NULL;
        node* curNode = new node();
        curNode->val = Bvec[Bend];
        int i;
        for(i = Astart; i <= Aend; i++){
            if(Avec[i] == Bvec[Bend]) break;
        }
        curNode->left = build(Astart, i - 1, Bstart, Bstart + i - Astart - 1 );
        curNode->right = build(i + 1, Aend, Bstart + i - Astart, Bend - 1 );
        return curNode;
    }

    void dfs(node* curNode, int sum){
        sum += curNode->val;
        //this is the root
        if(curNode->left == NULL && curNode->right == NULL){
            // cout << "find path with val " << sum << endl;

            if(sum < minPath){
                minPath = sum;
                minNode = curNode->val;
            }else if(sum == minPath){
                minNode = min(minNode, curNode->val);
            }
        }

        if(curNode->left != NULL) dfs(curNode->left, sum);
        if(curNode->right != NULL) dfs(curNode->right, sum);
    }

    void free(node* curNode){
        if(curNode == NULL) return;
        free(curNode->left);
        free(curNode->right);
        delete curNode;
    }
};


int main(){
    string lineA;
    string lineB;
    while(getline(cin, lineA) && getline(cin, lineB)){
        binaryTree bt = binaryTree(lineA, lineB);
        bt.dfs(bt.root, 0);
        cout << bt.minNode << endl;
        // bt.free(bt.root);
    }
    return 0;
}