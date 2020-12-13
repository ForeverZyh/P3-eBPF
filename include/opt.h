//
// Created by Yuhao Zhang on 2020/12/12.
//

#ifndef LAB4_INCLUDE_OPT_H_
#define LAB4_INCLUDE_OPT_H_

# include<unordered_map>
# include<iterator>
# include<list>
# include<string>
# include<unordered_set>
# include<queue>
# include<set>
using namespace std;

class OPT {
 public:
  unordered_map<string, queue<int> > *trace_access;
  set<pair<int, string>> pri_queue;
  unordered_set<string> cache;
  int capacity;
  int total;
  int hit;
  int miss;
  int len;
  explicit OPT(int capacity, unordered_map<string, queue<int> > *trace_access, int len);

  void put(const string &key);

  void get_info() const;
};

#endif //LAB4_INCLUDE_OPT_H_
