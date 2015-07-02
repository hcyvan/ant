#include "lib.h"
#include "dns.h"
/**********************************************
 ****************** Dns **********************
 *******************************************/
Dns& Dns::getHostByName(const string& name)
{
        if(addrinfo_p!=NULL){
                freeaddrinfo(addrinfo_p);
                addrinfo_p=NULL;
        }
        hostent_p=gethostbyname(name.c_str());
        if(hostent_p==nullptr)
                errorExit(hstrerror(h_errno));

        return *this;
}
const string Dns::getHostName()const
{
        if(hostent_p)
                return hostent_p->h_name;
        else if(addrinfo_p)
                return addrinfo_p->ai_canonname;
        else 
                errorExit("Can't use Dns::getHostName()");
        return nullptr;
}
const int Dns::getAddrType()const
{
        if(!hostent_p)
                errorExit("Can't use Dns::getAddrType()");
        return hostent_p->h_addrtype;
}
const vector<string> Dns::getAliases()const
{
        if(!hostent_p)
                errorExit("Can't use Dns::getAliases()");
        vector<string> h_aliases;
        for(char** s=hostent_p->h_aliases;*s!=nullptr;++s){
                h_aliases.push_back(*s);
        }
        return h_aliases;
}
const vector<string> Dns::getAddrList()const
{
        if(!hostent_p)
                errorExit("Can't use Dns::getAddrList()");
        vector<string> h_addr_list;
        for(char** s=hostent_p->h_addr_list;*s!=nullptr;++s){
                h_addr_list.push_back(inet_ntoa(*(struct in_addr*)*s));
        }

        return h_addr_list;
}
void Dns::openTcp(void)
{
        sethostent(1);
}
void Dns::closeTcp(void)
{
        endhostent();
}

AddrInfo Dns::getAddrInfo(const string& name, const int port)
{
        if(addrinfo_p!=NULL){
                freeaddrinfo(addrinfo_p);
        }
        hostent_p=NULL;
        
        string port_str=to_string(port);
        struct addrinfo hints;
        struct addrinfo *result;

        memset(&hints,0,sizeof(struct addrinfo));
        hints.ai_family=AF_INET;       /* Allow IPv4 or IPv6 */
        hints.ai_socktype=SOCK_STREAM;   /* Datagram socket */
        hints.ai_protocol=IPPROTO_TCP;   /* TCP protocol */
        hints.ai_flags= 0;               /* lookup IPv4 or IPv6 */

        int s=getaddrinfo(name.data(),port_str.data(),&hints,&result);
        if(s!=0){
                fprintf(stdout,"getaddrinfo: %s\n",gai_strerror(s));
                exit(EXIT_FAILURE);
        }
        addrinfo_p=result;
        return addrinfo_p;
}
/**********************************************
 ************** DnsLocal **********************
 *******************************************/
DnsLocal* DnsLocal::create()
{
        DnsLocal *p=new DnsLocal;
        // cout << "dnslocal create" <<endl;
        return p;
}

void DnsLocal::insert(const string& hostname,const string& ip4)
{
        hostname_ip4_hash.insert(make_pair(hostname,ip4));
}
void DnsLocal::insert(const string& hostname,const AddrInfo ai)
{
        for(AddrInfo rp=ai;rp!=nullptr;rp=rp->ai_next){
                if(rp->ai_family==AF_INET){
                        struct sockaddr_in* p;
                        p=(struct sockaddr_in *)rp->ai_addr;
                        char ip4buf[INET_ADDRSTRLEN];
                        inet_ntop(AF_INET,&p->sin_addr,\
                                  ip4buf,INET_ADDRSTRLEN);
                        const string ip4=ip4buf;
                        hostname_ip4_hash.insert(make_pair(\
                                                   hostname,ip4));
                }
        }
}
const string DnsLocal::find(const string& hostname) const
{
        auto pos=hostname_ip4_hash.find(hostname);
        if(pos==hostname_ip4_hash.end()){
                return "";
        }else{
                return pos->second;
        }
}

