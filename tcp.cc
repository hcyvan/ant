#include "tcp.h"
#include "lib.h"

Connect::Connect(const string& ip, int objport):ip4(ip),port(objport)
{
	fd=socket(AF_INET, SOCK_STREAM, 0); 
	if(fd==-1){
		char buf[]="Can return valuable socket";
		errorExit(buf);
	}
}
Connect::~Connect()
{
	close(fd);
}
void Connect::handshake()
{
	// configure the sockaddr	
	struct sockaddr_in address;
	memset((void*)&address, 0, sizeof(address));
	address.sin_family=AF_INET;
	const char* c_ip4=ip4.c_str();
	inet_pton(AF_INET, c_ip4, &address.sin_addr);	
	address.sin_port=htons(port);

	// connect() is block
	// Three-way handshake
	int ret=connect(fd, (struct sockaddr*)&address, sizeof(address));
	if(ret==-1){
		char buf[30];
		if(errno==EINPROGRESS){
			sprintf(buf,"Connecting timeout: the limitation is %ds,%dms\n",\
					(int)timeout.tv_sec,(int)timeout.tv_usec);
		}else{ 
			sprintf(buf,"Can't connet with %s:%d \n",c_ip4,port);
		}
		errorExit(buf);
	}
}
int Connect::getfd()
{
	return fd;
}
const string& Connect::getip4()
{
	return ip4;
}
void Connect::settimeout(int sec,int usec)
{
	timeout.tv_sec=sec;
	timeout.tv_usec=usec;	
	socklen_t len=sizeof(timeout);
	setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
}

