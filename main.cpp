//
// Created by Yuhao Zhang on 2020/12/8.
//

# include<unordered_map>
# include<iterator>
# include<string>
# include<iostream>
# include<fstream>
# include "2q.h"
# include "opt.h"
# include "arc.h"

vector<string> trace;
unordered_map<string, queue<int> > trace_access;

int main(int argc, char **argv) {
  if (argc != 3) {
	cout << "usage:./lru trace_file_name capacity(in MB)" << endl;
	return -1;
  }
  int capacity = stoi(argv[2]);
  int real_capacity = capacity * 1024 / 4;

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
	trace.push_back(key);
	trace_access[key].push(i);
  }
  ARC policy(real_capacity);
//  OPT policy(real_capacity, &trace_access, trace.size());
//  TwoQ policy(real_capacity, 0.2, 0.5);
//  LRU policy(real_capacity);
  for (int i = 0; i < trace.size(); i++) {
	policy.put(trace[i]);
  }
  cout << "cache size:" << capacity << "M" << endl;
  policy.get_info();
  return 0;

}