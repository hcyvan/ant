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
	HttpResponeHead resp(req);

	cout <<"*** "<<resp.find("Set-Cookie")<<endl;


	resp.show();

//	int fd=skt.handshake();

//	send(fd, request2, strlen(request2), 0); 

/*
while(1){
		recv(fd,buf,sizeof(buf),0);
		std::cout<< buf <<std::endl;
	}
*/	
	
	
	return 0;
}
