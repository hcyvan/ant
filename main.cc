#include <iostream>
#include "lib.h"
#include "tcp.h"
#include "http.h"
#include "dns.h"




int main()
{
// HttpUrl
//	const string name("http://www.baidu.com");
//	const string name("www.oschina.net/question/188977_58777");
	const string name("http://www.ibm.com/developerworks/cn/aix/library/1212_lufang_c11new/");
//const string name("https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=0&rsv_idx=1&tn=baidu&wd=hehe&rsv_pq=b03e487e0000aaca&rsv_t=9933pRtE2hawygTHkZYD9IvK4ElbqyrR6R%2BxHHd%2BP7DTM78t%2FRSEGMh2C%2BI&rsv_enter=1&rsv_sug3=6&rsv_sug1=4&rsv_sug2=0&inputT=541&rsv_sug4=2518");

	HttpUrl url(name);
// Dns	
	Dns dns(url.getHostName());
// HttpConnect
	HttpConnect skt(dns.getIp4Vec()[0],url.getPort());
	skt.setTimeout(1);

// HttpRequest
	vector<string> reqhead;

	reqhead.push_back("HOST: www.ibm.com");
//	reqhead.push_back("HOST: www.baidu.com");
//	reqhead.push_back("User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:38.0) Gecko/20100101 Firefox/38.0 Iceweasel/38.0.1");
//	reqhead.push_back("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
//	reqhead.push_back("Accept-Language: en-US,en;q=0.5");
//	reqhead.push_back("Accept-Encoding: gzip, deflate");
//	reqhead.push_back("Cache-Control: max-age=0");
//	reqhead.push_back("Referer: http://www.ibm.com/developerworks/cn/aix/library/1212_lufang_c11new/");
//	reqhead.push_back("Connection: keep-alive");


	HttpRequest req(skt,url.getPath(),reqhead);

//
	HttpRespContent resp(req);
//	HttpRespHead resp(req);
//	resp.show();

	
	return 0;
}
