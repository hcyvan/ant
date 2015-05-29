#include "connect.h"
#include "lib.h"
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

Connect::Connect(char* ip, int objport)
{
	ip4=strdup(ip);
	port=objport;
	fd=socket(AF_INET, SOCK_STREAM, 0); 
	if(fd==-1){
		char buf[]="Can return valuable socket";
		errorExit(buf);
	}
}
Connect::~Connect()
{
	free(ip4);
	close(fd);
}
int Connect::handshake()
{
	// configure the sockaddr	
	struct sockaddr_in address;
	memset((void*)&address, 0, sizeof(address));
	address.sin_family=AF_INET;
	inet_pton(AF_INET, ip4, &address.sin_addr);	
	address.sin_port=htons(port);

	// connect() is block
	int ret=connect(fd, (struct sockaddr*)&address, sizeof(address));
	if(ret==-1){
		char buf[30];
		if(errno==EINPROGRESS){
			sprintf(buf,"Connecting timeout: the limitation is %ds,%dms\n",\
					(int)timeout.tv_sec,(int)timeout.tv_usec);
		}else{ 
			sprintf(buf,"Can't connet with %s:%d \n",ip4,port);
		}
		errorExit(buf);
	}
	return fd;
}
int Connect::getfd()
{
	return fd;
}
void Connect::settimeout(int sec,int usec)
{
	timeout.tv_sec=sec;
	timeout.tv_usec=usec;	
	socklen_t len=sizeof(timeout);
	setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
}
