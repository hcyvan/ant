#ifndef _HTTP_H_
#define _HTTP_H_
#include "tcp.h"

#define RECV_BUF 10000
using namespace std;

class HttpRequest:private Connect{
public:
	HttpRequest(const Connect&);
	// GET (http request)
protected:
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

/******************************************************
 ************* HttpRespHead ***********************
 ****************************************************/
class HttpRespHead:public HttpRequest{
public:
	HttpRespHead(const HttpRequest&);
	/** find the value unique key in the respone head **/
	const vector<string> find(const string&) const;
	/** find and return the response line. **/
	const string find_respline(void) const;
	/** Return the reference of resphead **/
	virtual const string& data(void) const;
	/** print the content of resphead **/
	virtual void show() const;
protected:
	/** return the resphead **/
	const string& gethead(void)const;
private:
	// Http response head
	string resphead;
};


/******************************************************
 ************* HttpResponeContent ***********************
 ****************************************************/
class HttpRespContent:public HttpRespHead{
public:
	HttpRespContent(const HttpRequest&);
	/** Return the reference of respcontent **/
	const string& data(void) const;
	/** print the content of respcontent **/
	void show() const;
private:
	string respcontent;
};

#endif
