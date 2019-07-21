#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
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
    }
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
    }
}

void printBuyQuote(){
    int bidPrice = 0, bidSize = 0;
    vector<order> tempStore;
    buyPopInactive();
    while(!buyOrders.empty()){
        // cout << "entering printBuyQuote" << endl;
        order topOrder = buyOrders.top();
        if(bidSize != 0 && topOrder.price !=  bidPrice){
            break;
        }else{
            bidPrice = topOrder.price;
            bidSize += topOrder.size;
            buyOrders.pop();
            tempStore.push_back(topOrder);
        }
        buyPopInactive();
    }

    for (unsigned i = 0; i < tempStore.size(); i++)
    {
        buyOrders.push(tempStore[i]);
    }

    cout << "QUOTE " << bidSize  << ' ' << bidPrice << ' ' << "- ";
}

void printSellQuote(){
    int askPrice = 99999, askSize = 0;
    vector<order> tempStore;
    sellPopInactive();
    while(!sellOrders.empty()){
        order topOrder = sellOrders.top();
        if(askSize != 0 && topOrder.price != askPrice){
            break;
        }else{
            askPrice = topOrder.price;
            askSize += topOrder.size;
            sellOrders.pop();
            tempStore.push_back(topOrder);
        }
        sellPopInactive();
    }

    for (unsigned i = 0; i < tempStore.size(); i++)
    {
        sellOrders.push(tempStore[i]);
    }

    cout << askSize  << ' ' << askPrice  << endl;
}


int main(){
    int n;
    while (cin >> n)
    {
        int i = 0, p, q, toCancel;
        string type;

        //reset 
        buyOrders = priority_queue<order, vector<order>, smallerComp>();
        sellOrders = priority_queue<order, vector<order>, greaterComp>();
        inactive.clear();

        while (i++ < n)
        {
            cin >> type;
            // cout << i << endl;
            if(type[0] == 'C'){
                cin >> toCancel;
                inactive.insert(toCancel);
            }else{
                cin >> p >> q;
                order o = {i, p, q, type[0]};
                if(o.type == 'B'){
                    buyTrade(o);
                }else{
                    sellTrade(o);
                }
            }
            printBuyQuote();
            printSellQuote();
        }
        cout << endl;

    }
    
    
    
}