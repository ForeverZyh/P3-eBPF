//
// Created by Aoran Wu on 2020/12/8.
//

# include<unordered_map>
# include<iterator>
# include<list>
# include<string>
# include<unordered_set>
# include<queue>
using namespace std;

class LRU {
 public:
  list<string> queue;
  unordered_map<string, list<string>::iterator> lru_map;
  int capacity;
  int total;
  int hit;
  int miss;
  explicit LRU(int capacity);

  void put(const string &key);

  void get_info() const;
};