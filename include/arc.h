//
// Created by Yuhao Zhang on 2020/12/12.
//

#ifndef LAB4_ARC_ARC_H_
#define LAB4_ARC_ARC_H_

# include<unordered_map>
# include<iterator>
# include<list>
# include<string>
# include<unordered_set>
# include<queue>
using namespace std;

struct DLB {
  list<string> queue;
  unordered_map<string, list<string>::iterator> lru_map;
  int size();
  void remove(const string &key);
  void append(const string &key);
  string popleft();
};

class ARC {
 public:
  DLB T1, B1, T2, B2;
  int capacity;
  int total;
  int hit;
  int miss;
  int ratio;
  unordered_set<string> cache;
  explicit ARC(int capacity);

  void put(const string &key);

  void replace(const string &key);

  void get_info() const;
};

#endif //LAB4_ARC_ARC_H_
