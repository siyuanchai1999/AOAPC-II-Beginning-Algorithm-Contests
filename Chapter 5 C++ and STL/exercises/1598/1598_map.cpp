/*
This is the question that requires some attention while reading the specifications. 
I use two priority queues to track the order with highest/lowest price; two different comparator was passed to the pq to maintain priority requirement of buy and sell orders.
To make it easier to print the QUOTE two map from price to totalsize are used. The map is updated whenever any order is changed in trade, added to the orderbook or canceled.

 */

#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <map>
using namespace std;

struct order
{
    int id, size, price;
    char type;
    /*
    'B' for buy; 'S' for sell
     */
};

struct greaterComp
{
    bool operator() (const order & lhs, const order & rhs){
        return lhs.price > rhs.price || (lhs.price == rhs.price && lhs.id > rhs.id);
    }
};

struct smallerComp{
    bool operator() (const order & lhs, const order & rhs){
        return lhs.price < rhs.price || (lhs.price == rhs.price && lhs.id > rhs.id);
    }
};

priority_queue<order, vector<order>, smallerComp> buyOrders;
priority_queue<order, vector<order>, greaterComp> sellOrders;
unordered_set<int> inactive;
map<int, int> buyVal2size;
map<int, int> sellVal2size;
vector<order> orderVec;

void updateMap(map<int, int> &val2size, int val, int size, int op){
    int update;
    if(val2size.find(val) == val2size.end()){
        update = size;
    }else{
        update  = val2size[val] + size * op;
    }
    if(update == 0){
            val2size.erase(val);
    }else{
            val2size[val] = update;
    }
    
}

//always ensure that existed.top is an active order
void buyPopInactive(){
    while (!buyOrders.empty())
    {
        if(inactive.find(buyOrders.top().id) != inactive.end() || buyOrders.top().size <= 0){
            buyOrders.pop();
        }else{
            break;
        }
    }
}

void sellPopInactive(){
    while (!sellOrders.empty())
    {
        if(inactive.find(sellOrders.top().id) != inactive.end() || sellOrders.top().size <= 0){
            sellOrders.pop();
        }else{
            break;
        }
    }
}

//curOrder.type = 'B' sellOrders processed 
void buyTrade(order &currOrder){
    int tradePrice = 0, tradeSize = 0;
    sellPopInactive();
    while (currOrder.size > 0 && !sellOrders.empty())
    {   
        order topOrder = sellOrders.top();
        if(topOrder.price > currOrder.price){
            break;
        }
        
        sellOrders.pop();

        int sizeReduced = min(currOrder.size, topOrder.size);
        currOrder.size -= sizeReduced;
        topOrder.size -= sizeReduced;
        updateMap(sellVal2size, topOrder.price, sizeReduced, -1);
        orderVec[topOrder.id] = topOrder;

        tradePrice = topOrder.price;
        tradeSize = sizeReduced;
        cout << "TRADE " << tradeSize << ' ' << tradePrice << endl; 
        
        if(topOrder.size > 0){
            sellOrders.push(topOrder);
        }

        sellPopInactive();
    }

    if(currOrder.size > 0){
        buyOrders.push(currOrder);
        updateMap(buyVal2size, currOrder.price, currOrder.size, 1);
    }
    orderVec[currOrder.id] = currOrder;
}

//curOrder.type = 'S' buyorder processed 
void sellTrade(order &currOrder){
    int tradePrice = 0, tradeSize = 0;
    buyPopInactive();
    while (currOrder.size > 0 && !buyOrders.empty())
    {   
        order topOrder = buyOrders.top();
        if(topOrder.price  < currOrder.price){
            break;
        }

        buyOrders.pop();
        int sizeReduced = min(currOrder.size, topOrder.size);
        currOrder.size -= sizeReduced;
        topOrder.size -= sizeReduced;
        updateMap(buyVal2size, topOrder.price, sizeReduced, -1);
        orderVec[topOrder.id] = topOrder;

        tradePrice = topOrder.price;
        tradeSize = sizeReduced;
        cout << "TRADE " << tradeSize << ' ' << tradePrice << endl; 
        
        if(topOrder.size > 0){
            buyOrders.push(topOrder);
        }
        buyPopInactive();
    }

    
    if(currOrder.size > 0){
        sellOrders.push(currOrder);
        updateMap(sellVal2size, currOrder.price, currOrder.size, 1);
    }
    orderVec[currOrder.id] = currOrder;
}

void printBuyQuote(){
    int bidPrice = 0, bidSize = 0;
    if(!buyVal2size.empty()){
        map<int, int>::reverse_iterator it = buyVal2size.rbegin();
        bidPrice = it->first;
        bidSize = it->second;
    }

    cout << "QUOTE " << bidSize  << ' ' << bidPrice << ' ' << "- ";
}

void printSellQuote(){
    int askPrice = 99999, askSize = 0;
    if(!sellVal2size.empty()){
        map<int, int>::iterator it = sellVal2size.begin();
        askPrice = it->first;
        askSize = it->second;
    }

    cout << askSize  << ' ' << askPrice  << endl;
}


int main(){
    int n, t = 0;
    while (cin >> n)
    {   
        if(t++ != 0) cout << endl;
        int i = 0, p, q, toCancel;
        string type;

        //reset 
        buyOrders = priority_queue<order, vector<order>, smallerComp>();
        sellOrders = priority_queue<order, vector<order>, greaterComp>();
        inactive.clear();
        buyVal2size.clear();
        sellVal2size.clear();
        order temp;
        orderVec = vector<order> (n + 1, temp);

        while (i++ < n)
        {
            cin >> type;
            // cout << i << endl;
            if(type[0] == 'C'){
                cin >> toCancel;
                inactive.insert(toCancel);
                order cancelO = orderVec[toCancel];
                orderVec[toCancel].size = 0;
                if(cancelO.type == 'B'){
                    updateMap(buyVal2size, cancelO.price, cancelO.size, -1);
                }else{
                    updateMap(sellVal2size, cancelO.price, cancelO.size, -1);
                }
            }else{
                cin >> p >> q;
                order o = {i, p, q, type[0]};
                orderVec[i] = o;
                if(o.type == 'B'){
                    buyTrade(o);
                }else{
                    sellTrade(o);
                }
            }
            printBuyQuote();
            printSellQuote();
        }

    }
    
    
    
}