#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int binsearch(vector<int> st, int val){
	int start = 0;
	int end = st.size() - 1;
	int mid;
	while(start <= end){
		mid = (start + end)/2;
		if(st[mid] == val){
			return mid;
		}else if(st[mid] < val){
			start = mid + 1;
		}else{
			end = mid - 1;
		}
	}
	return -1;
}

int main(){
	int N, Q;
	cin >> N;
	cin >> Q;
	int serialNum = 0, temp, pos;
	vector<int> storage;
	while(N != 0 && Q != 0){
		for(int i = 0; i < N; i++){
			cin >> temp;
			storage.push_back(temp);
		}
		sort(storage.begin(), storage.end());
		vector<int>::iterator p = storage.begin();
		
		
		cout << "CASE# " << (++serialNum) << ":" << endl;
				
		while(Q-- > 0){
			cin >> temp;
			pos = lower_bound(storage.begin(),storage.end() - 1, temp) - storage.begin();
			cout << temp << ' ';
			if(storage[pos] != temp){
				cout << "not found" << endl;
			}else{
				cout << "found at " << (pos + 1) << endl;
			}
		}
		cin >> N;
		cin >> Q;
		storage.clear();
	}
}
