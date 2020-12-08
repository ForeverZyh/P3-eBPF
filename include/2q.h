//
// Created by Yuhao Zhang on 2020/12/8.
//

#ifndef LAB4_INCLUDE_2Q_H_
#define LAB4_INCLUDE_2Q_H_

# include<string>
# include<unordered_set>
# include<queue>
# include "lru.h"
using namespace std;

class TwoQ {
 public:
  LRU am;
  int capacity, total, hit, miss, kin, kout;

  unordered_set<string> a1in_set, a1out_set;
  queue<string> a1in, a1out;
  TwoQ(int capacity, double kin, double kout);

  void reclaim_for_am(const string &key);

  void reclaim_for_a1in(const string &key);

  void put(const string &key);

  void get_info() const;
};

#endif //LAB4_INCLUDE_2Q_H_
