#ifndef _HTTP_H_
#define _HTTP_H_
#include "tcp.h"

#define RECV_HEAD_BUF 5000
using namespace std;

class HttpRequest:private Connect{
public:
	HttpRequest(const Connect&);
	// GET (http request)
	int get();
	// HEAD (http request)
	int head();
private:
	// Http request line;
	string reqURI;
	string version;
	// Http request head;
	vector<string> reqhead;
	// Http request data;
	string reqdata;
};

class HttpResponeHead:public HttpRequest{
public:
	HttpResponeHead(const HttpRequest&);
	/** find a unique key in the map **/
	const string& find(const string&) const;
	/** print the content of the response head **/
	void show() const;
private:
	string respline;
	multimap<string,string> resp_key_value;
};



#endif
