//
// Created by Yuhao Zhang on 2020/12/8.
//

# include<unordered_map>
# include<iterator>
# include<string>
# include<iostream>
# include<fstream>
# include "2q.h"

int main(int argc, char **argv) {
  if (argc != 3) {
	cout << "usage:./lru trace_file_name capacity(in MB)" << endl;
	return -1;
  }
  int capacity = stoi(argv[2]);
  int real_capacity = capacity * 1024 / 4;
  TwoQ policy(real_capacity, 0.2, 0.5);
//  LRU policy(real_capacity);

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
	policy.put(key);
  }
  cout << "cache size:" << capacity << "M" << endl;
  policy.get_info();
  return 0;

}