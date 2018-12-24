#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int width = 8;

void swap_row(double matrix[][width], int RA, int RB){
    double tmp;
    for(int i = 0; i < width; i++){
        tmp = matrix[RA][i];
        matrix[RA][i] = matrix[RB][i];
        matrix[RB][i] = tmp;
    }
}

int partition(double matrix[][width], int p, int r, int col){
    double pivot = matrix[r][col];
    int i = p - 1;
    for(int j = p; j < r; j++){
        if(matrix[j][col] <= pivot){
            i++;
            swap_row(matrix, i, j);
        }
    }
    swap_row(matrix, i + 1, r);
    return i + 1;
}

void sortMatrix(double matrix[][width], int startR, int endR, int col){
    if(startR < endR){
        int q = partition(matrix, startR, endR, col);
        sortMatrix(matrix,startR, q - 1, col);
        sortMatrix(matrix,q + 1, endR, col);
    }
}

void showMatrix(double matrix[][width], int pCnt){
    cout << "show matrix" << endl;
    for(int i = 0; i < pCnt; i++){
        for(int j = 0; j < width;j++){
            cout << matrix[i][j] << '\t' << '\t' << '\t' << '\t';
        }
        cout << endl;
    }
}

int findCutNum(double matrix[][width], int playerCnt){
    int i = 0, result;
    while(i < playerCnt && matrix[i][5] != INT32_MAX ){
        if(i >= 70){
            if(matrix[i][5] != matrix[69][5]){
                break;
            }
        }
        i++;
    }
    result = i;
    return result;
}

int main(){
    int caseNum, playerCnt;
    double purseValue;
    double percentages[70];
    double database[144][width] = {};      //index  RD1  RD2 RD3 RD4 subtotal total moneywon
    string namebase[144];
    cin >> caseNum;

    while(caseNum-- > 0){
        cin >> purseValue;
        for(int i = 0 ; i < 70 ;i++){
            cin >> percentages[i];
        }

        cin >> playerCnt;
        for(int i = 0; i < playerCnt; i++){
            namebase[i].resize(20);             // read 20 characters only
            cin.read(&namebase[i][0], 20);
            database[i][0] = i;
            string input;
            for(int j = 1; j <= 4; j++){
                cin >> input;
                if(input == "DQ"){
                    database[i][j] = INT32_MAX;
                    if(j <= 2) database[i][5] = INT32_MAX;
                    database[i][6] = INT32_MAX;
                    break;
                }else{
                    database[i][j] = double(stoi(input));
                }
            }
            if(database[i][5] != INT32_MAX) database[i][5] = database[i][1] + database[i][2];
            if(database[i][6] != INT32_MAX) database[i][6] = database[i][5] + database[i][3] + database[i][4];
        }
        
        
        sortMatrix(database, 0, playerCnt - 1, 5);
        // showMatrix(database, playerCnt);
        int secRound = findCutNum(database, playerCnt);
        sortMatrix(database, 0, secRound - 1, 6);


    }
}