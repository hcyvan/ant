#ifndef _TCP_H_
#define _TCP_H_
#include "lib.h"
using namespace std;

class HttpConnect{
public:
	/** Use socket() to get a file discriptor.
            Set the remote host address. **/
	//HttpConnect()=default;
	HttpConnect(const string ip, int objport=80);
	HttpConnect(const HttpConnect &conn):fd(conn.fd),\
                ip4(conn.ip4),port(conn.port),           \
                timeout(conn.timeout){}
        HttpConnect(const AddrInfo);
	~HttpConnect();
	/** Set the handshake time. SO_SNDTIMEO **/
	void setTimeout(int sec,int usec=0);
protected:
	/** Get the socket to connect with web server **/
	int getfd(void);
	/** Get the ip of web server(object host **/
	const string& getip4();
	/** Use connet() to connect a remote host(and its port). 
            This finish the three-way handshake, so the fd can be 
            used to send message to the remote host. socked is
            returned **/
	void handshake();
private:
	int fd;		
	const string ip4;    // The ip of ipv4
	int port;	     // Default port is 80 for web server
	struct timeval timeout;
        
        AddrInfo addrinfo_p;
};



#endif
