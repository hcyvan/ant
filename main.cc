#include <iostream>
#include "lib.h"
#include "tcp.h"
#include "http.h"
#include "dns.h"




int main()
{
	//const char ip[]="202.108.22.5";
//	const string ip("202.108.22.5");
//	const string ip("115.239.211.112");
//	int port= 80;
//	char request[]="GET /index.html HTTP/1.1\nHOST:www.baidu.com\n\n";
//	char request2[]="HEAD /index.html HTTP/1.1\nHOST:\n\n";
//	char buf[10000];

/*
	Connect skt(ip,port);
	HttpRequest req(skt);
	HttpRespContent resp(req);
	resp.show();
*/
	
	const string name("www.baidu.com");
	//const string name("115.239.211.112");
	Dns dns(name);
	auto l=dns.data();
	for(auto i:l)
		cout << i<< endl;
////////////////////////////////////////////////
	const string name2("http://www.baidu.com");
	HttpUrl url(name2);
	cout << url.getHostName()<<endl;
	
	return 0;
}
