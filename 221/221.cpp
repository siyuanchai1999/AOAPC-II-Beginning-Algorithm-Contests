#include <iostream>
#include <algorithm>

using namespace std;
const int MAXbuild = 105; 
double positions[MAXbuild*2 + 1];
int buildingNum;

struct building{
    int id;
    double x, y, w, d, h;
    bool operator < (const building rhs) const{
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
}buildinglist[MAXbuild];

bool inRange(int i, double mid){
    return buildinglist[i].x <= mid && buildinglist[i].x + buildinglist[i].w >= mid;
}
//return whether building i is visible at position mid
bool visible(int i, double mid){
    if(!inRange(i,mid)) return false;
    for(int k = 0; k < buildingNum; k++){
        if(inRange(k,mid) && buildinglist[k].y < buildinglist[i].y && buildinglist[k].h >= buildinglist[i].h) return false;
    }
    return true;
}



int main(){
    int kase = 0;
    cin >> buildingNum;
    while(buildingNum > 0){
        for(int i = 0; i < buildingNum; i++){
            cin >> buildinglist[i].x >> buildinglist[i].y >> buildinglist[i].w >> buildinglist[i].d >> buildinglist[i].h;
            buildinglist[i].id = i + 1;
            positions[i*2] = buildinglist[i].x;
            positions[i*2 + 1] = buildinglist[i].x + buildinglist[i].w;
        }
        
        sort(buildinglist, buildinglist + buildingNum);
        sort(positions, positions + buildingNum*2);

        double *newEnd = unique(positions, positions + buildingNum*2);

        if(kase++) cout << endl;
        cout << "For map #" << kase << ", the visible buildings are numbered as follows:" << endl;
        cout << buildinglist[0].id;
        for(int i = 1; i < buildingNum; i++){
            for(double *posIt = positions; posIt < newEnd - 1; posIt++){
                double midpoint = (*posIt + *(posIt+1))/2;
                if(visible(i,midpoint)){
                    cout << ' ' << buildinglist[i].id ;
                    break;
                }
            }
        }
        cout << endl;
        

        cin >>buildingNum;
    }
}