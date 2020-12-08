# include<unordered_map>
# include<iterator>
# include<utility>
# include<list>
# include<string>
# include<iostream>
# include<fstream>
# include "lru.h"
using namespace std;
LRU::LRU(int capacity) {
  this->capacity = capacity;
  total = 0;
  hit = 0;
  miss = 0;
}

int LRU::get(const string &key) {
  total++;
  if (lru_map.find(key) != lru_map.end()) {
	hit++;
	queue.erase(lru_map[key]);
	queue.push_front(key);
	lru_map[key] = queue.begin();
	return 0;
  } else {
	miss++;
	return -1;
  }
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

int main(int argc, char **argv) {
  if (argc != 3) {
	cout << "usage:./lru trace_file_name capacity(in MB)" << endl;
	return -1;
  }
  int capacity = stoi(argv[2]);
  int real_capacity = capacity * 1024 / 4;
  LRU lru(real_capacity);
  ifstream ifs;
  ifs.open(argv[1], ifstream::in);
  string addr, obj, page, index;
  ifs >> addr >> obj >> page;
  int i = 0;

  while (ifs >> addr >> obj >> page >> index) {
	i++;
	//cout<<i<<endl;
	string real_index = index.substr(6);
	string key = page + real_index;
	lru.put(key);
  }
  cout << "cache size:" << capacity << "M" << endl;
  lru.get_info();
  return 0;

}