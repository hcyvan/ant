#ifndef _DNS_H_
#define _DNS_H_
#include "lib.h"
using namespace std;

class Dns{
 public:
  // Connect with name server use TCP socket. The
  // default is UDP.
  static void openTcp(void);
  // Colse the TCP socket.
  static void closeTcp(void);
  // Get the host address and other information
  // from the name server.
  Dns& getHostByName(const string&);
  const string getHostName(void)const;
  const int getAddrType(void)const;
  const vector<string> getAliases(void)const;
  const vector<string> getAddrList(void)const; 
 private:
  void hErrno(void)const;

  struct hostent* hostent_p;
  string h_name;             // official name of host
  vector<string> h_aliases;  // alias list
  int h_addrtype;            // AF_INET/AF_INET6 
  // int h_length;           // length of address
  vector<string> h_addr_list;// list of addresses
  
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
