#include "spider.h"
DnsLocal* __local_dns=nullptr;
Spider::Spider()
{
  // To judge whether local_dns is defined.
  // Create local_dns if it not exist.
  if(!__local_dns){
    __local_dns=DnsLocal::create();
  }
}

string Spider::get(const string& url)
{
  
  // HttpUrl
  HttpUrl url_parser(url);
  
  // Dns
  string ip4=__local_dns->find(url_parser.getHostName());
  if(ip4==""){
    // cout << "use remote dns ..." <<endl;
    Dns dns;
    ip4=dns.getHostByName(url_parser.getHostName()).getAddrList()[0];
    __local_dns->insert(url_parser.getHostName(),ip4);
  }//else{cout << ip4 <<endl;}

  // HttpConnect
  HttpConnect skt(ip4,url_parser.getPort());
  // HttpRequest
  vector<string> reqhead;
  reqhead.push_back("HOST: "+url_parser.getHostName());
  
  HttpRequest req(skt,url_parser.getPath(),reqhead);
  // HttpRespContent
  HttpRespContent resp(req);
  return resp.data();
}
