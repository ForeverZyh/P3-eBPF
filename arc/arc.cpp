//
// Created by Yuhao Zhang on 2020/12/12.
// from https://github.com/andryej/PyARC/blob/master/arc/arc.py
//

# include<unordered_map>
# include<iterator>
# include<iostream>
# include<algorithm>
# include "arc.h"
using namespace std;
ARC::ARC(int capacity) {
  this->capacity = capacity;
  total = 0;
  hit = 0;
  miss = 0;
  ratio = 0;
}

void DLB::remove(const string &key) {
  queue.erase(lru_map[key]);
  lru_map.erase(key);
}

void DLB::append(const string &key) {
  queue.push_back(key);
  auto it = queue.end();
  it--;
  lru_map[key] = it;
}

string DLB::popleft() {
  string key = queue.front();
  queue.pop_front();
  lru_map.erase(key);
  return key;
}

int DLB::size() { return queue.size(); }

void ARC::put(const string &key) {
  total++;
//#  Hit in ARC(c)
//#  place it at the LRU position of T2 list
  int lt1 = T1.size(), lb1 = B1.size(), lt2 = T2.size(), lb2 = B2.size();
  if (cache.find(key) != cache.end()) {
	hit++;
	if (T1.lru_map.find(key) != T1.lru_map.end()) {
	  T1.remove(key);
	} else {
	  T2.remove(key);
	}
	T2.append(key);
  }
//#  Hit in DLB(2c)
//#  Element was seen "recently" seen only once
//#  place it at the MRU position of T2 list
  else if (B1.lru_map.find(key) != B1.lru_map.end()) {
	miss++;
	ratio = min(capacity, ratio + max(1, lb2 / lb1));
	replace(key);
	B1.remove(key);
	T2.append(key);
	cache.insert(key);
  }
//#  Hit in DLB(2c)
//#  Element was seen "recently" seen only once
//#  place it at the MRU position of T2 list
  else if (B2.lru_map.find(key) != B2.lru_map.end()) {
	miss++;
	ratio = max(0, ratio - max(1, lb1 / lb2));
	replace(key);
	B2.remove(key);
	T2.append(key);
	cache.insert(key);
  }
//#  No hit
//#  element was not seen "recently"
//#  place it at the MRU position of T1 list
  else {
	miss++;
	if (lt1 + lb1 == capacity) {
	  if (lt1 < capacity) {
		B1.popleft();
		replace(key);
	  } else {
		cache.erase(T1.popleft());
	  }
	} else {
	  int sm = lt1 + lt2 + lb1 + lb2;
	  if (sm >= capacity) {
		if (sm == 2 * capacity) {
		  B2.popleft();
		}
		replace(key);
	  }
	}
	T1.append(key);
	cache.insert(key);
  }
}

void ARC::replace(const string &key) {
  int l = T1.size();
  string x;
  if (l > 0 && (ratio < l || (l == ratio && B2.lru_map.find(key) != B2.lru_map.end()))) {
	x = T1.popleft();
	B1.append(x);
  } else {
	x = T2.popleft();
	B2.append(x);
  }
  cache.erase(x);
}

void ARC::get_info() const {
  cout << "total:" << total << " hits:" << hit << " miss:" << miss << " hit rates:" << ((double)hit) / total << endl;
}