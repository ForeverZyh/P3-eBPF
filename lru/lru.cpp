# include<unordered_map>
# include<iterator>
# include<iostream>
# include "lru.h"
using namespace std;
LRU::LRU(int capacity) {
  this->capacity = capacity;
  total = 0;
  hit = 0;
  miss = 0;
}

void LRU::put(const string &key) {
  total++;
  if (lru_map.find(key) != lru_map.end()) {
	hit++;
	queue.erase(lru_map[key]);
	queue.push_front(key);
	lru_map[key] = queue.begin();
  } else {
	miss++;
	if (lru_map.size() == capacity) {
	  lru_map.erase(queue.back());
	  queue.pop_back();
	}
	queue.push_front(key);
	lru_map[key] = queue.begin();
  }
}

void LRU::get_info() const {
  cout << "total:" << total << " hits:" << hit << " miss:" << miss << " hit rates:" << ((double)hit) / total << endl;
}
