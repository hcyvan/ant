#include "tcp.h"
#include "lib.h"

HttpConnect& HttpConnect::set(const string& ip, int objport)
{
        ip4=ip;
        port=objport;
        addrinfo_p=nullptr;
	fd=socket(AF_INET, SOCK_STREAM, 0); 
	if(fd==-1){
		char buf[]="Can't return valuable socket";
		errorExit(buf);
	}
        fd_to_close.push_back(fd);
        return *this;
}
HttpConnect& HttpConnect::set(const AddrInfo addrinfo)
{
        ip4="";
        port=-1;
        addrinfo_p=addrinfo;
        fd=socket(AF_INET, SOCK_STREAM, 0); 
	if(fd==-1){
		char buf[]="Can't return valuable socket";
		errorExit(buf);
	}
        fd_to_close.push_back(fd);
        return *this;
}
        
HttpConnect::~HttpConnect()
{
	for(int i:fd_to_close)
                close(i);
}
HttpConnect& HttpConnect::handshake()
{
	// configure the sockaddr
 	struct sockaddr_in address;
        if(addrinfo_p==nullptr){
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
                                sizeof(*addrinfo_p->ai_addr));
                if(ret==-1){
                        char buf[30];
                        sprintf(buf,"Connect Wrong!: errno:%d", \
                                errno);
                        errorExit(buf);
                }
        }
        return *this;
}
int HttpConnect::getFd()
{
	return fd;
}
const string& HttpConnect::getIp4()
{
	return ip4;
}
HttpConnect& HttpConnect::setTimeout(int sec,int usec)
{
	timeout.tv_sec=sec;
	timeout.tv_usec=usec;	
	socklen_t len=sizeof(timeout);
	setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
        return *this;
}

