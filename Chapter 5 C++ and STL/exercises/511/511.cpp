/*
This question requires some patience to read the description. First, different locations are mapped to a bunch of maps that contain such location.
The mappes are sorted into decreasing order of area. When there's a tie the preferred map based on the criterion described is selected.
Note that the level of detail corresponds to the area of maps (ie. two maps with same area has same level of detail).
I implement the sort function in a reversed way such that the most preferred map is the last in the vector with such level of detail.
A more intuitive way of implementation is flip the greater than and smaller than sign in the last four comparisions in in my overloading of < operator.
The example can be found on https://github.com/morris821028/UVa/blob/master/volume005/511%20-%20Do%20You%20Know%20the%20Way%20to%20San%20Jose.cpp.
 */



#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#include <set>
using namespace std;

void showPair(pair<double, double>& pt){
    cout << '(' << pt.first << '\t' << pt.second << ')' << '\t';
}

double getDistance(pair<double, double>& ptA, pair<double, double>& ptB){
    return sqrt(pow(ptA.first - ptB.first, 2) + pow(ptA.second - ptB.second, 2));
}

struct maps{
    string name;
    pair<double, double> lowerLeft;
    pair<double, double> upperRight;
    double area;
    double centerDis;
    double ratioCompStd;
    double cornerDis;

    bool ContainPt(pair<double, double>& pt){
        return (lowerLeft.first <= pt.first &&
                lowerLeft.second <= pt.second &&
                upperRight.first >= pt.first &&
                upperRight.second >= pt.second);
    }

    void show(){
        cout << name << '\t';
        showPair(lowerLeft);
        showPair(upperRight);
        cout << "area: " << area << '\t';
        cout << "centerDis " << centerDis << '\t';
        pair<double, double> ct = getCenter();
        showPair(ct);
        cout << "ratioCompStd " << ratioCompStd << '\t';
        cout << "cornerDis " << cornerDis << '\t' << endl;
    }

    pair<double, double> getCenter(){
        return make_pair((lowerLeft.first + upperRight.first)/2, (lowerLeft.second + upperRight.second)/2 );
    }
    double getCenterDis(pair<double, double>& loc){
        pair<double, double> ct = getCenter();
        return getDistance(ct, loc);
    }
    //height over width
    double getRatio(){
        return (upperRight.second - lowerLeft.second)/(upperRight.first - lowerLeft.first);
    }
    //return the distance to the 
    double ratioCompToStd(double std = 0.75){
        return fabs(this->getRatio() - std);
    }
    
    double getCornerDis(pair<double, double>& loc){
        pair<double, double> corner = make_pair(lowerLeft.second, upperRight.first);
        return getDistance(corner, loc);
    }
    
    void update(pair<double, double>& loc){
        centerDis = this->getCenterDis(loc);
        ratioCompStd = this->ratioCompToStd();
        cornerDis = this->getCornerDis(loc);
    }

    bool operator < (maps& rhs){
        if(this->area != rhs.area)
        {
            return this->area > rhs.area;

        }else if(this->centerDis != rhs.centerDis)
        {
            return this->centerDis > rhs.centerDis;

        }else if(this->ratioCompStd != rhs.ratioCompStd)
        {
            return this->ratioCompStd > rhs.ratioCompStd;

        }else if(this->cornerDis != rhs.cornerDis)
        {
            return this->cornerDis < rhs.cornerDis;

        }else{
            return this->lowerLeft.first > rhs.lowerLeft.first;
        }
    }
};



int main(){
    string header;
    
    vector<maps> mapStorage;
    cin >> header;
    map<string, vector<maps> > loc2maps;
    map<string, set<double> > areaCnt;
    if(header == "MAPS") cin >> header;
    
    //read in MAPS
    while(header != "LOCATIONS"){
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        maps newMap;
        newMap.name = header;
        newMap.lowerLeft = make_pair(min(x1, x2), min(y1, y2));
        newMap.upperRight = make_pair(max(x1, x2), max(y1, y2));
        newMap.area = fabs(x1 - x2) * fabs(y1 - y2);
        // newMap.show();
        mapStorage.push_back(newMap);
        cin >> header;
    }

    cin >> header;
    //read in locations
    while (header != "REQUESTS")
    {       
        pair<double, double> pt;
        cin >> pt.first >> pt.second;
        // cout << header;
        // showPair(pt);
        // cout << "-----" << endl;
        for(unsigned i = 0; i < mapStorage.size(); i++){
            if(mapStorage[i].ContainPt(pt)){
                loc2maps[header].push_back(mapStorage[i]);
                loc2maps[header].back().update(pt); 
                areaCnt[header].insert(mapStorage[i].area);             
            }
        }

        sort(loc2maps[header].begin(), loc2maps[header].end());
        // vector<maps> temp = loc2maps[header];
        // for (size_t i = 0; i < temp.size(); i++)
        // {
        //     temp[i].show();
        // }
        
        cin >> header;
    }

    cin >> header;
    unsigned level;

    while(header != "END"){
        cin >> level;
        cout << header << " at detail level " << level << ' ';
        if(loc2maps.find(header) == loc2maps.end()){
            //not found
            cout << "unknown location" << endl;
        }else if(loc2maps[header].size() == 0){
            //no map
            cout << "no map contains that location" << endl;
        }else if(level > areaCnt[header].size()){
            //no map at this level
            cout << "no map at that detail level; using " << loc2maps[header].back().name << endl;
        }else{
            //hit
            vector<maps> mapsT = loc2maps[header];
            
            unsigned i = 0, l = 0;
            double lastArea = -1.0;
            while(l < level){
                if(lastArea != mapsT[i].area){
                    l++;
                    lastArea = mapsT[i].area;
                }else{
                    i++;
                }
            }
            while(i < mapsT.size() && lastArea == mapsT[i].area){
                i++;
            }
            string nameNeed = mapsT[i - 1].name;
            cout << "using " << nameNeed << endl;
        }

        cin >> header;
    }
    
}