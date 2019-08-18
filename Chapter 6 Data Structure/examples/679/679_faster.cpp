#include <iostream>
#include <math.h>

using namespace std;

/*
Note that the left child of current node can be expressed as node *2 and right child can be expressed as node *2 +1
Also, whether or not the ball goes to the left/right branch is determined by the number of numbers that arrive at this node. 
If it's a odd time arrival (iter%2 == 1), it goes to the left.
If it's an even time arrival (iter%2 == 0), it goes to the right.
 */
// int ball(int node, int iter, int MAXNode){
//     int left = node *2;
//     int right = node *2 + 1;
//     if(right <= MAXNode){
//         if(iter%2 == 1){
//             return ball(left, (iter + 1)/2, MAXNode);
//         }else{
//             return ball(right, iter/2, MAXNode);
//         }
//     }else{
//         //current node is leaf node
//         return node;
//     } 
// }

int main(){
    int l, curD, curI;
    cin >> l;
    while (l-- > 0){
        cin.sync_with_stdio(false);
        cin >> curD >> curI;
        int node = 1;
        for(int i = 0; i < curD - 1; i++){
            if(curI%2 == 1){
                node = node *2;
                curI = (curI + 1)/2;
            }else{
                node = node * 2 + 1;
                curI = curI/2;
            }
        }
        cout << node << endl;
    }
    cin >> l;   
}