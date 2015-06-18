#include "spider.h"

string Spider::get(const string &httpUrl)
{
	// HttpUrl
	HttpUrl url(httpUrl);
	// Dns	
	Dns dns(url.getHostName());
	// HttpConnect
	HttpConnect skt(dns.getIp4Vec()[0],url.getPort());
	// HttpRequest
	vector<string> reqhead;
	reqhead.push_back("HOST: "+url.getHostName());

	HttpRequest req(skt,url.getPath(),reqhead);
	// HttpRespContent
	HttpRespContent resp(req);
	return resp.data();
}
