#include <iostream>
#include "lib.h"
#include "connect.h"



int main()
{
	char ip[]="202.108.22.5";
	int port= 80;
	char request[]="GET /index.html HTTP/1.1\nHOST:www.baidu.com\n\n";
	char buf[10000];

	Connect skt(ip,port);

	skt.settimeout(1);
	int fd=skt.handshake();

	send(fd, request, strlen(request), 0); 


		recv(fd,buf,sizeof(buf),0);
		std::cout<< buf <<std::endl;
	
	
	
	return 0;
}
