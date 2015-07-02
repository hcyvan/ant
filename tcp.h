#ifndef _TCP_H_
#define _TCP_H_
#include "lib.h"
using namespace std;

class HttpConnect{
public:
	/** Use socket() to get a file discriptor.
            Set the remote host address. **/
        HttpConnect():ip4(""),port(-1),addrinfo_p(nullptr){};
        HttpConnect(const HttpConnect &conn):fd(conn.fd),        \
                ip4(conn.ip4),port(conn.port),                   \
                timeout(conn.timeout),                           \
                addrinfo_p(conn.addrinfo_p){}
	~HttpConnect();
        
	HttpConnect& set(const string& ip, int objport=80);
        HttpConnect& set(const AddrInfo);
	/** Set the handshake time. SO_SNDTIMEO **/
	HttpConnect& setTimeout(int sec,int usec=0);
	/** Get the socket to connect with web server **/
	int getFd(void);
	/** Get the ip of web server(object host **/
	const string& getIp4();
	/** Use connet() to connect a remote host(and its port). 
            This finish the three-way handshake, so the fd can be 
            used to send message to the remote host. socked is
            returned **/
	HttpConnect& handshake();
private:
	int fd;		
	string ip4;    // The ip of ipv4
	int port;	     // Default port is 80 for web server
	struct timeval timeout;
        
        AddrInfo addrinfo_p;

        vector<int> fd_to_close;
};



#endif
