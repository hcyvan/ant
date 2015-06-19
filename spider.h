#ifndef _SPIDER_H_
#define _SPIDER_H_
#include "lib.h"
#include "tcp.h"
#include "http.h"
#include "dns.h"
using namespace std;


class Spider{
public:
  Spider();
  string get(const string &);
private:

  const string url;
	
};


#endif
