#ifndef _SOCKET_H_
#define _SOCKET_H_
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>


class Connect{
public:
	/** Use socket() to get a file discriptor.
		Set the remote host address. **/
	Connect(char* ip, int objport=80);
	~Connect();
	/** Use connet() to connect a remote host(and its port). 
		This finish the	three-way handshake, so the fd can be 
		used to send message to the remote host. socked is
		returned **/
	int handshake();
	/** Get the socket to connect with web server **/
	int getfd(void);
	/** Set the handshake time. SO_SNDTIMEO **/
	void settimeout(int sec,int usec=0);
private:
	int fd;		
	int port;	// Default port is 80 for web server
	char* ip4;	// The ip of ipv4
	struct timeval timeout;
};
		


#endif
