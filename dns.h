#ifndef _DNS_H_
#define _DNS_H_
#include "lib.h"
using namespace std;

class Dns{
 public:
  Dns(const string& hostname);
  const vector<string>& getIp4Vec()const;
  const string& getHostName()const;
	
 private:
  string host_name;
  vector<string> ip4_vec;	
};

class DnsLocal{
 public:
  static DnsLocal* create(void);
  void insert(const string&,const string&);
  const string find(const string&) const;
 private:
  unordered_map<string,string> hostname_ip4_hash;
};

#endif
