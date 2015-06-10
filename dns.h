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


#endif
