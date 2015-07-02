#ifndef _DNS_H_
#define _DNS_H_
#include "lib.h"
using namespace std;

class Dns{
public:
        Dns():hostent_p(nullptr),addrinfo_p(nullptr){}
        ~Dns(){if(addrinfo_p){freeaddrinfo(addrinfo_p);\
                        addrinfo_p=nullptr;}}
        // Get the host address and other information
        // from the name server.
        Dns& getHostByName(const string&);
        // Get address information from the name server.
        AddrInfo getAddrInfo(const string&, const int port=80);

        // Connect with name server use TCP socket. The
        // default is UDP.
        static void openTcp(void);
        // Colse the TCP socket.
        static void closeTcp(void);
        // official name of host
        const string getHostName(void)const;
        // host address type
        const int getAddrType(void)const;
        // alias list
        const vector<string> getAliases(void)const;
        // list of addresses
        const vector<string> getAddrList(void)const;

private:
        struct hostent* hostent_p;
        AddrInfo addrinfo_p;
};

class DnsLocal{
public:
        static DnsLocal* create(void);
        void insert(const string&,const string&);
        void insert(const string&,const AddrInfo);
        const string find(const string&) const;
private:
        unordered_map<string,string> hostname_ip4_hash;
};

#endif
