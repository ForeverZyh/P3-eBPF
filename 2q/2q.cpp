//
// Created by Yuhao Zhang on 2020/12/8.
//

# include<unordered_map>
# include<iterator>
# include<iostream>
# include "2q.h"
using namespace std;

TwoQ::TwoQ(int capacity, double kin, double kout) : am(LRU(int(capacity * (1 - kin)))) {
  this->capacity = capacity;
  total = 0;
  hit = 0;
  miss = 0;
  this->kin = capacity - am.capacity;
  this->kout = int(kout * capacity);
}

void TwoQ::reclaim_for_am(const string &key) {
  am.put(key);
}

void TwoQ::reclaim_for_a1in(const string &key) {
  if (a1in.size() == this->kin) { // remove a key from a1in, if it is full
	string y = a1in.front();
	a1in.pop();
	a1in_set.erase(y);
	if (a1out.size() == this->kout) { // remove a key from a1out, if it is full
	  string z = a1out.front();
	  a1out.pop();
	  a1out_set.erase(z);
	}
	// put y into a1out
	a1out_set.insert(y);
	a1out.push(y);
  }
  // put key into a1in
  a1in_set.insert(key);
  a1in.push(key);
}

void TwoQ::put(const string &key) {
  total++;
  if (am.lru_map.find(key) != am.lru_map.end()) {
	hit++; // in Am, it's a hit!
	am.put(key); // remove the key to the head of Am
  } else if (a1out_set.find(key) != a1out_set.end()) {
	miss++; // in A1out, ghost, it's a miss!
	reclaim_for_am(key); // put key in Am
  } else if (a1in_set.find(key) != a1in_set.end()) {
	hit++; // in A1in, it's a hit!
  } else {
	miss++; // Miss!
	reclaim_for_a1in(key); // put key in A1in
	// remove the key to the head of A1in
  }
}

void TwoQ::get_info() const {
  cout << "total:" << total << " hits:" << hit << " miss:" << miss << " hit rates:" << ((double)hit) / total << endl;
}
