//
// Created by 煜皓张 on 2020/12/12.
//


# include<iostream>
#include "opt.h"
using namespace std;

OPT::OPT(int capacity, unordered_map<string, queue<int> > *trace_access, int len) {
  this->capacity = capacity;
  this->trace_access = trace_access;
  this->len = len;
  total = 0;
  hit = 0;
  miss = 0;
}

void OPT::put(const string &key) {
  total++;
  if (cache.find(key) != cache.end()) {
	hit++;
	auto it = trace_access->find(key);
	int pre_loc = it->second.front();
	pri_queue.erase(make_pair(-pre_loc, key));
	it->second.pop();
	if (it->second.empty()) {
	  pri_queue.insert(make_pair(-(len + 1), key));
	} else {
	  pri_queue.insert(make_pair(-it->second.front(), key));
	}
  } else {
	miss++;
	if (cache.size() == capacity) {
	  auto it = *pri_queue.begin();
	  assert(cache.find(it.second) != cache.end());
	  cache.erase(it.second);
	  pri_queue.erase(pri_queue.begin());
	}
	cache.insert(key);
	auto it = trace_access->find(key);
	it->second.pop();
	if (it->second.empty()) {
	  pri_queue.insert(make_pair(-(len + 1), key));
	} else {
	  pri_queue.insert(make_pair(-it->second.front(), key));
	}
  }
}

void OPT::get_info() const {
  cout << "total:" << total << " hits:" << hit << " miss:" << miss << " hit rates:" << ((double)hit) / total << endl;
}
