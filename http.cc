#include "http.h"
#include "lib.h"
HttpRequest::HttpRequest(const HttpConnect& conn):HttpConnect(conn)
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
 ************* HttpRespHead ***********************
 ****************************************************/
HttpRespHead::HttpRespHead(const HttpRequest& req):HttpRequest(req)
{
	char buf[RECV_BUF];
	// send the HEAD http request
	int fd=head();	
	recv(fd, buf, sizeof(buf), 0);
	resphead=buf;
}
const vector<string> HttpRespHead::find(const string& pattern) const
{
	vector<string> vec;	
	string key(pattern);
	key+=": ";
	string::size_type begIdx=resphead.find(key);
	while(begIdx != string::npos){		
		begIdx=begIdx+key.length()-1;
		string::size_type endIdx=resphead.find("\r\n",begIdx);
		vec.push_back(resphead.substr(begIdx+1,endIdx-begIdx));
	 	begIdx=resphead.find(key,endIdx);
	}
	return vec;
}
const string& HttpRespHead::gethead(void)const
{
	return resphead;
}
const string HttpRespHead::find_respline() const
{
	string::size_type endIdx=resphead.find("\r\n");
	string respline=resphead.substr(0,endIdx);
	return respline;
}
const string& HttpRespHead::data() const
{
	return resphead;
}
void HttpRespHead::show() const
{
	cout<<resphead<<endl;
}

/******************************************************
 ************* HttpRespContent ***********************
 ****************************************************/
HttpRespContent::HttpRespContent(const HttpRequest& req):HttpRespHead(req)
{
	char buf[RECV_BUF];
	// send the GET http request
	int fd=get();	
	
	string::size_type data_len=stoi(*find("Content-Length").begin());
	string::size_type head_len=gethead().length();
	string::size_type total_len=data_len+head_len;
	string::size_type len=0;
	while(len<total_len){
		memset(buf,'\0',RECV_BUF);	// Very! very! very! important
		int recv_len=recv(fd, buf, RECV_BUF-1, 0);
		len+=recv_len;
		respcontent+=buf;
	}
}
const string& HttpRespContent::data() const
{
	return respcontent;
}
void HttpRespContent::show() const
{
	cout<<respcontent<<endl;
}



/******************************************************
 ****************** HttpUrl **************************
 ****************************************************/
HttpUrl::HttpUrl(const string& url)
{
	string::size_type http=url.find("http://");
	string::size_type https=url.find("https://");
	if(http==0){
		http+=7;
		string::size_type slash=url.find("/",http);
		// http://www.baidu.com[:80]
		if(slash==string::npos){
			string::size_type colon=url.find(":",http);
			// http://www.baidu.com
			if(colon==string::npos){
				host_name=url.substr(http);
				port=80;
			// http://www.baidu.com:80
			}else{
				host_name=url.substr(http,colon-http);
				port=stoi(url.substr(colon+1));
			}
		// http://www.baidu.com[:80]/[index.html]
		}else{
			string::size_type colon=url.rfind(":",slash);
			// http://www.baidu.com/[index.html]
			//if(colon==string::npos){
			if(colon<http){
				host_name=url.substr(http);
				port=80;
			// http://www.baidu.com:80/[index.html]
			}else{
				host_name=url.substr(http,colon-http);
				port=stoi(url.substr(colon+1));
			}
			path=url.substr(slash);
		}
	}else if(https==0){
		https+=8;
		string::size_type slash=url.find("/",https);
		// https://www.baidu.com[:80]
		if(slash==string::npos){
			string::size_type colon=url.find(":",https);
			// https://www.baidu.com
			if(colon==string::npos){
				host_name=url.substr(http);
				port=80;
			// https://www.baidu.com:80
			}else{
				host_name=url.substr(http,colon-http);
				port=stoi(url.substr(colon+1));
			}
		// https://www.baidu.com[:80]/[index.html]
		}else{
			string::size_type colon=url.rfind(":",slash);
			// https://www.baidu.com/[index.html]
			if(colon==string::npos){
				host_name=url.substr(http);
				port=80;
			// https://www.baidu.com:80/[index.html]
			}else{
				host_name=url.substr(http,colon-http);
				port=stoi(url.substr(colon+1));
			}
			path=url.substr(slash);
		}
	}else{
		string wrong;
		wrong=wrong + "\"" + url.c_str() + "\" is a wrong http URL.";
		errorExit(wrong.c_str());
	}
}

const string& HttpUrl::getHostName()const
{
	return host_name;
}
int  HttpUrl::getPort()const
{
	return port;
}
const string& HttpUrl::getPath()const
{
	return path;
}
	
	





			


	









































