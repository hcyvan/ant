#include "lib.h"
#include "dns.h"
Dns::Dns(const string& hostname)
{
  struct hostent* dns=gethostbyname(hostname.c_str());
  if(!dns){
    string wrong("DNS Parse Wrong: ");
    switch(h_errno){
    case HOST_NOT_FOUND:
      wrong=wrong+hostname.c_str()+" is unknown. ";
      errorExit(wrong);
      break;
    case NO_ADDRESS:
      wrong=wrong+hostname.c_str()+" is valid, but does not have IP address. ";
      errorExit(wrong);
      break;
    case NO_RECOVERY:
      wrong=wrong+hostname.c_str()+" Nonrecoverable name server error occurred. ";
      errorExit(wrong);
      break;
    case TRY_AGAIN:
      wrong=wrong+hostname.c_str()+" Try Again later. ";
      errorExit(wrong);
      break;
    default:
      wrong=wrong+hostname.c_str()+" Unkown reasion";
      errorExit(wrong);
      break;
    }
  }
  host_name=hostname;
  for(char** s=dns->h_addr_list;*s!=nullptr;++s){
    char*str=inet_ntoa(*(struct in_addr*)*s);
    ip4_vec.push_back(str);
  }
}
const vector<string>& Dns::getIp4Vec()const
{
  return ip4_vec;
}
const string& Dns::getHostName()const
{
  return host_name;
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

