#include "lib.h"
#include "dns.h"
/**********************************************
 ****************** Dns **********************
 *******************************************/
Dns& Dns::getHostByName(const string& name)
{
  hostent_p=gethostbyname(name.c_str());
  if(hostent_p==nullptr)
    hErrno();
  // official name of host
  h_name=hostent_p->h_name;
  // alias list
  for(char** s=hostent_p->h_aliases;*s!=nullptr;++s){
    h_aliases.push_back(*s);
  }
  // host address type
  h_addrtype=hostent_p->h_addrtype;
  // list of addresses
  for(char** s=hostent_p->h_addr_list;*s!=nullptr;++s){
    h_addr_list.push_back(inet_ntoa(*(struct in_addr*)*s));
  }

  return *this;
}
const string Dns::getHostName()const
{
  return h_name;
}
const int Dns::getAddrType()const
{
  return h_addrtype;
}
const vector<string> Dns::getAliases()const
{
  return h_aliases;
}
const vector<string> Dns::getAddrList()const
{
  return h_addr_list;
}

void Dns::hErrno()const
{
  string wrong("DNS Parse Wrong: ");
  switch(h_errno){
  case HOST_NOT_FOUND:
    wrong=wrong+h_name.c_str()+" is unknown. ";
    errorExit(wrong);
    break;
  case NO_ADDRESS:
    wrong=wrong+h_name.c_str()+" is valid, but does not have IP address. ";
    errorExit(wrong);
    break;
  case NO_RECOVERY:
    wrong=wrong+h_name.c_str()+" Nonrecoverable name server error occurred. ";
    errorExit(wrong);
    break;
  case TRY_AGAIN:
    wrong=wrong+h_name.c_str()+" Try Again later. ";
    errorExit(wrong);
    break;
  default:
    wrong=wrong+h_name.c_str()+" Unkown reasion";
    errorExit(wrong);
    break;
  }
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

const string DnsLocal::find(const string& hostname) const
{
  auto pos=hostname_ip4_hash.find(hostname);
  if(pos==hostname_ip4_hash.end()){
    return "";
   
  }else{
    return pos->second;
  }
}

