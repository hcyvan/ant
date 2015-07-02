## Crawler
This is a suite of APIs for web spider. These APIs are wirte by C++11 and use the linux socket APIs for the lower layer. The version 0.2 is relased. 0.2 means it is not stable and maybe contain a lot of bugs. When 1.0 is released, the APIs is OK to use. There are several modules in the APIs.  
For more information, read the manual.md in chinese.
---
## Brief
There are five moudle's in the API suite.
### tcp
+ **HttpConnect**: This class is used to connect with the (web) server.
  + *set()*: set the object remote host.
  + *handshack()*: member func to do the three-way handshake with remote host.
  + *getfd()*: return the socket fd of local cleint.
  + *getip4()*: return the ip of remote host.
  + *setTimeout(int,int)*: Set the the time deadline to do the three-way handshake.

### http
There are four class in this module.

+ **HttpUrl** is used to parse the url. It parse the url as three parts.
	+ host_name
	+ port
	+ path
+ **HttpRequest** is the drived class of HttpConnect and is used to send request to the remote http server.
+ **HttpRespHead** and **HttpRespHead** is the derived class of HttpRequest. The diffreint of the two classes is the request the HttpRquest send to the server. As a result, the cotent the class get is diffreint.

### dns
This module has two class.

+ **Dns** is used to set a host_name to the dns server and get some ip (or some other info in the further).
+ **DnsLocal** is a container to the information the class Dns get.

### Spider
This is a module use integrate the other modules to build a web spider. A "local dns server",*__loca_dns* is defined in this module. It is a global pointer to a *DnsLocal* object. When *Spider* get hostname from a *HttpUrl* object, it check the hostname in the "local dns server". If the hostname is in the local tablee, *Spider* won't use *Dns* object to get the remote server ip.

---
## Usage
you can change the code in main.cc to do want you want.

+ **make** complie all the *.c* file in the file and link them
+ **make clean** clean *.o* file and the *crawler* 
