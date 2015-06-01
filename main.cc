#include <iostream>
#include "lib.h"
#include "tcp.h"
#include "http.h"




int main()
{
	//const char ip[]="202.108.22.5";
	const string ip("202.108.22.5");
	int port= 80;
//	char request[]="GET /index.html HTTP/1.1\nHOST:www.baidu.com\n\n";
//	char request2[]="HEAD /index.html HTTP/1.1\nHOST:\n\n";
//	char buf[10000];

	Connect skt(ip,port);
	HttpRequest req(skt);
	HttpRespContent resp(req);
	resp.show();
	
	return 0;
}
