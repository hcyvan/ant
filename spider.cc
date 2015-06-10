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
	//reqhead.push_back("User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:38.0) Gecko/20100101 Firefox/38.0 Iceweasel/38.0.1");
//	reqhead.push_back("User-Agent: Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6");
//	reqhead.push_back("Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");

//	reqhead.push_back("Accept-Language: en-US,en;q=0.5");
//	reqhead.push_back("Accept-Encoding: gzip, deflate");
//	reqhead.push_back("Cookie: ptui_loginuin=736913187; pt2gguin=o0736913187; ptcz=fea6653019ef44071012e6e3ac4a34ab38038a31f2c76ab1166ee3c74926200e; pgv_pvid=1924931212; o_cookie=736913187; pgv_info=ssid=s6119877720; ts_last=www.qq.com/; ts_uid=7364313030; ad_play_index=81");
//	reqhead.push_back("Connection: keep-alive");

	HttpRequest req(skt,url.getPath(),reqhead);
	// HttpRespContent
	HttpRespContent resp(req);
	return resp.data();
}
