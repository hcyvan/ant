#ifndef _DNS_H_
#define _DNS_H_
#include "lib.h"
using namespace std;

class Dns{
public:
	Dns(const string& hostname);
	const vector<string>& data()const;
private:
	vector<string> ip4_list;	
};


#endif
