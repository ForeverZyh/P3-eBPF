//
// Created by Aoran Wu on 2020/12/8.
//

# include<unordered_map>
# include<iterator>
# include<list>
# include<string>
using namespace std;

#ifndef LAB4_INCLUDE_LRU_H_
#define LAB4_INCLUDE_LRU_H_

class LRU {
 public:
  list<string> queue;
  unordered_map<string, list<string>::iterator> lru_map;
  int capacity;
  int total;
  int hit;
  int miss;
  explicit LRU(int capacity);

  int get(const string& key);

  void put(const string& key);

  void get_info() const;
};

#endif //LAB4_INCLUDE_LRU_H_
