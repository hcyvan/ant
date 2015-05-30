#include "http.h"
#include "lib.h"
HttpRequest::HttpRequest(const Connect& conn):Connect(conn)
{
	/** Three-way connect with the web server **/
	handshake();	
	reqURI="/index.html";
	version="HTTP/1.1";
	if(reqhead.empty()){
		string host="HOST:"+ getip4();
		reqhead.push_back(host);
	}
}
int HttpRequest::get()
{
	// request line
	string get="GET "+ reqURI + " " + version + "\n";
	// request head
	for(auto &s : reqhead){
		get=get+s+"\n";
	}
	// request data
	get=get+"\n"+reqdata;

	const char* req=get.c_str();
	int fd=getfd();

	send(fd, req, strlen(req), 0);
	return fd;
}
int HttpRequest::head()
{
	// request line
	string get="HEAD "+ reqURI + " " + version + "\n";
	// request head
	for(auto &s : reqhead){
		get=get+s+"\n";
	}
	// request data
	get=get+"\n"+reqdata;

	const char* req=get.c_str();
	int fd=getfd();

	send(fd, req, strlen(req), 0);
	return fd;
}

/******************************************************
 ************* HttpResponeHead ***********************
 ****************************************************/
HttpResponeHead::HttpResponeHead(const HttpRequest& req):HttpRequest(req)
{
	char buf[RECV_HEAD_BUF];
	// send the HEAD http request
	int fd=head();	
	recv(fd, buf, sizeof(buf), 0);

	const string headbuf(buf);
	// split when \r\n
	const string delim("\r\n");
	vector<string> vec;
	// split the response head content
	split(headbuf, vec, delim);
	// parse the response 
	for(auto beg=vec.cbegin()+1;beg != vec.cend();++beg){
		// split the string by ": " .
		string colon(": ");
		string::size_type num = beg->find(colon);
		pair<string, string> key_value=make_pair(beg->substr(0,num),\
										beg->substr(num+2));
		// insert the pair to the map.
		resp_key_value.insert(key_value);
	}
	respline=*vec.cbegin();
}
const string& HttpResponeHead::find(const string& key) const
{
	auto value=resp_key_value.find(key);	
	return value->second; 

}

void HttpResponeHead::show() const
{
	cout << respline <<endl;
	for(auto i:resp_key_value)
		cout << i.first << " => " << i.second << endl;
}














