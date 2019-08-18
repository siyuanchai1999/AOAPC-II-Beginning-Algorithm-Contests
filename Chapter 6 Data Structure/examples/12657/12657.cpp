/*
manually implement a doubly linked list to handle the movement and swap. There's a map from value to its pointer to keep track of the information.
 */

#include <iostream>
#include <unordered_map>
using namespace std;

struct node
{
    node* prev;
    node* next;
    int val;

    node(){
        prev = NULL;
        next = NULL;
        val = 0;
    }
};

struct dlist
{
    node* head;
    node* tail;
    unordered_map<int, node*> val2ptr;
    int reversed;

    dlist(int cnt){
        head = new node();
        int c = 1; 
        node* cur = head;
        node* pre = NULL;
        while (cur != NULL)
        {
            cur->val = c++;
            val2ptr[cur->val] = cur;
            cur->next = (c > cnt ? NULL : new node());
            cur->prev = pre;
            pre = cur;
            tail = cur;
            cur = cur->next;
        }
        reversed = 0;
    }
    
    long sumOdd(){
        node *cur = (reversed ? tail:head);
        int cnt = 1;
        long result = 0;
        while (cur != NULL)
        {
            if(cnt % 2 == 1){
                result += cur->val;
            }
            cnt++;
            cur =  (reversed? cur->prev: cur->next);
        }
        return result;
    }

    void display(){
        node *cur = head;
        while (cur != NULL){
            cout << cur->val << '\t';
            cur = cur->next;
        }
        cout << endl;
    }

    void remove(node* toPop){
        if (toPop == head){
            head = toPop->next;
        }
        if(toPop == tail){
            tail = toPop->prev;
        }
        
        if(toPop->next != NULL){
            toPop->next->prev = toPop->prev;
        }
        if(toPop->prev != NULL){
            toPop->prev->next = toPop->next;
        }
    }

    void rightInsert(node* toInsert, node* pos){
        if(pos->next == toInsert){
            return;
        }

        remove(toInsert);
        toInsert->next = pos->next;
        toInsert->prev = pos;
        if(pos->next != NULL){
            pos->next->prev = toInsert;
        }
        pos->next = toInsert;
        if(pos == tail) tail = toInsert;
    }

    void rightInsertWrapper(int x, int y){
        if(!reversed){
            rightInsert(val2ptr[x], val2ptr[y]);
        }else{
            leftInsert(val2ptr[x], val2ptr[y]);
        }
    } 

    void leftInsert(node* toInsert, node* pos){
        if(pos->prev == toInsert){
            return;
        }

        remove(toInsert);
        toInsert->next = pos;
        toInsert->prev = pos->prev;
        if(pos->prev != NULL){
            pos->prev->next = toInsert;
        }
        pos->prev = toInsert;
        if(pos == head) head = toInsert;
    }

    void leftInsertWrapper(int x, int y){
        if(!reversed){
            leftInsert(val2ptr[x], val2ptr[y]);
        }else{
            rightInsert(val2ptr[x], val2ptr[y]);
        }
    }

    void swap(int x, int y){
        node* A = val2ptr[x];
        node* B = val2ptr[y];

        int temp = A->val;
        A->val = B->val;
        B->val = temp;

        val2ptr[A->val] = A;
        val2ptr[B->val] = B;
    }

};

int main(){
    int n, m, cmd, x, y;
    int caseNum = 0;

    while (cin >> n >> m){
        dlist curlist = dlist(n);
        // curlist.display();
        while(m-- > 0){
            cin >> cmd; 
            switch (cmd){
                case 1:
                    cin >> x >> y;
                    curlist.leftInsertWrapper(x, y);
                    break;
                case 2:
                    cin >> x >> y;
                    curlist.rightInsertWrapper(x,y);
                    break;
                case 3:
                    cin >> x >> y;
                    curlist.swap(x,y);
                    break;
                case 4:
                    curlist.reversed = !curlist.reversed;
            }
            // curlist.display();
        }
        cout << "Case " << ++caseNum << ": " <<curlist.sumOdd() << endl;
    }

    

}