#include "http.h"
#include "lib.h"
/******************************************************
 ****************** HttpUrl **************************
 ****************************************************/
HttpUrl::HttpUrl(const string& url)
{
	regex httpUrl("^(http://|https://)?(([[:w:]]+\\.)+[[:w:]]+)(:([[:d:]]*))?(/.*)?");	
	smatch m;
	bool find=regex_match(url,m,httpUrl);
	if(find==false){
		string wrong("\""+url+"\" is a wrong http URL.");
		errorExit(wrong);
	}
	// host_name
	host_name=m.str(2);
	// port
	if(m.str(5).size()==0){
		port=80;
	}else{
		port=stoi(m.str(5));
	}
	// path
	if(m.str(6).size()==0){
		path="/index.html";
	}else{
		path=m.str(6);
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
/******************************************************
 ****************** HttpRequest ***********************
 ****************************************************/
HttpRequest::HttpRequest(const HttpConnect& conn):HttpConnect(conn)
{
	/** Three-way connect with the web server **/
	handshake();	
	reqPath="/index.html";
	version="HTTP/1.1";
	if(reqhead.empty()){
		string host="HOST:"+ getip4();
		reqhead.push_back(host);
	}
}
HttpRequest::HttpRequest(const HttpConnect& conn, \
			const string& path):HttpConnect(conn),reqPath(path)
{
	/** Three-way connect with the web server **/
	handshake();	
	version="HTTP/1.1";
	if(reqhead.empty()){
		string host="HOST:"+ getip4();
		reqhead.push_back(host);
	}
}
HttpRequest::HttpRequest(const HttpConnect& conn,\
			const string& path,const vector<string>& reqhead \
			):HttpConnect(conn),reqPath(path),reqhead(reqhead)
{
	handshake();	
	version="HTTP/1.1";
}
int HttpRequest::get()
{
	// request line
	string get="GET "+ reqPath + " " + version + "\n";
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
	string get="HEAD "+ reqPath + " " + version + "\n";
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
HttpRespContent::HttpRespContent(const HttpRequest& req):HttpRequest(req)
{
	char buf[RECV_BUF];
	// send the GET http request
	int fd=get();	
	string::size_type header_end;
	unsigned int content_length=-1;
	int chunk=-1;
	for(;;){
		memset(buf,'\0',RECV_BUF);	// Very!very!very!important
		recv(fd, buf, RECV_BUF-1, 0);
		respcontent+=buf;
		auto length=respcontent.find("Content-Length:");
		auto chunked=respcontent.find("chunked\r\n");
		if(length!=string::npos){
			length=respcontent.find_first_of("0123456789",length);
			content_length=stoul(respcontent.substr(length));
		}
		if(chunked!=string::npos){
			chunk=0;
		}
		header_end=respcontent.find("\r\n\r\n");
		if(header_end!=string::npos){
			break;
		}
	}
	if(content_length!=(unsigned int)-1){
		string::size_type head_length=header_end+4;
		while(respcontent.size()<head_length+content_length){
			memset(buf,'\0',RECV_BUF);
			recv(fd, buf, RECV_BUF-1, 0);
			respcontent+=buf;
		}
	}else if(chunk!=-1){
		unsigned int chunk_size=stoi(respcontent.substr(header_end+4),nullptr,16);
		string::size_type chunk_beg=respcontent.find("\r\n",header_end+4)+2;
		unsigned int end=chunk_beg+chunk_size;

		for(;;){
			cout<<respcontent.size()<<" "<<end<< endl;
			if(respcontent.size()>end+2){

				if(respcontent.find("\r\n",end+2)!=string::npos){
					chunk_size=stoi(respcontent.substr(end),nullptr,16);
					if(chunk_size==0){
						break;
					}else{
						chunk_beg=respcontent.find("\r\n",end+2)+2;
						end=chunk_beg+chunk_size;
					}
				}else{
					recv(fd, buf, RECV_BUF-1, 0);
					respcontent+=buf;
					chunk_size=stoi(respcontent.substr(end),nullptr,16);
					if(chunk_size==0){
						break;
					}else{
						chunk_beg=respcontent.find("\r\n",end+2)+2;
						end=chunk_beg+chunk_size;
					}
				}
			}		
			memset(buf,'\0',RECV_BUF);	// Very!very!very!important
			recv(fd, buf, RECV_BUF-1, 0);
			respcontent+=buf;
		}
	}else{
		//do something
	}
	cout << respcontent <<endl;
}
const string& HttpRespContent::data() const
{
	return respcontent;
}
void HttpRespContent::show() const
{
	cout<<respcontent<<endl;
}



	
	
