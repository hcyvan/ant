#include "tcp.h"
#include "lib.h"

HttpConnect::HttpConnect(const string ip, int objport)\
        :ip4(ip),port(objport),addrinfo_p(nullptr)
{
	fd=socket(AF_INET, SOCK_STREAM, 0); 
	if(fd==-1){
		char buf[]="Can't return valuable socket";
		errorExit(buf);
	}
}
HttpConnect::HttpConnect(const AddrInfo addrinfo)\
        :ip4(""),port(-1),addrinfo_p(addrinfo)
{
        fd=socket(AF_INET, SOCK_STREAM, 0); 
	if(fd==-1){
		char buf[]="Can't return valuable socket";
		errorExit(buf);
	}
}
        
HttpConnect::~HttpConnect()
{
	close(fd);
}
void HttpConnect::handshake()
{
	// configure the sockaddr
 	struct sockaddr_in address;
        if(ip4!=""){
                memset((void*)&address, 0, sizeof(address));
                address.sin_family=AF_INET;
                const char* c_ip4=ip4.c_str();
                inet_pton(AF_INET, c_ip4, &address.sin_addr);	
                address.sin_port=htons(port);
                // connect() is block, Three-way handshake
                int ret=connect(fd, (struct sockaddr*)&address, \
                                sizeof(address));
                if(ret==-1){
                        char buf[30];
                        sprintf(buf,"Connect Wrong!: errno:%d", \
                                errno);
                        errorExit(buf);
                }
        }else{
                int ret=connect(fd,addrinfo_p->ai_addr,         \
                                sizeof(addrinfo_p->ai_addr));
                if(ret==-1){
                        char buf[30];
                        sprintf(buf,"Connect Wrong!: errno:%d", \
                                errno);
                        errorExit(buf);
                }
        }
}
int HttpConnect::getfd()
{
	return fd;
}
const string& HttpConnect::getip4()
{
	return ip4;
}
void HttpConnect::setTimeout(int sec,int usec)
{
	timeout.tv_sec=sec;
	timeout.tv_usec=usec;	
	socklen_t len=sizeof(timeout);
	setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
}

