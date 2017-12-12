#include<vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
unordered_map<int,vector<int>::iterator> cache;
bool cache_find(const vector<int>::iterator &begin, const vector<int>::iterator& vend, int key){
    if(begin == vend) return false;
    vector<int>::iterator last_watched = begin, res;
    if(cache.count(key)) {
        last_watched = cache[key];
        if (last_watched == begin) return true;
    }
    //we lookup last element in the sequence to be known not to be equal to key
    res = find(last_watched,vend,key);
//if element is found we assign beginning of vector to key as a symbol to convey this, since it cant't otherwise be assigned to a key
    if(res != vend) res = begin;
    cache.insert({key,res});
    return res == begin;
}
void populate_vector(vector<int>& v){
	for(int i = 0; i != 100; ++i){
		v.push_back(rand()%30);
	}
}

int main(){
	vector<int> keys = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,0, 1,3,4,5,6,7,8,9,11,13,14,15,16,7,18,19,20,2,23,24,25,26,27,28,29,30,0};
	for(int i = 0; i != 100; ++i){
		vector<int> v;
		populate_vector(v);
		populate_vector(keys);
		cache.clear();
		for(int& k:keys){
			if(cache_find(v.begin(),v.end(),k) != (find(v.begin(),v.end(),k) != v.end())){
				cout << "discrepancy at key: " << k << " in vector: [";
				for(auto& e: v) cout << e << ", ";
				cout << "]" << endl;
			}
		}
	}
}
