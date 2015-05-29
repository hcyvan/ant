#ifndef _HTTP_H_
#define _HTTP_H_

class HttpRespone{
public:
	HttpRespone(char*);
private:
	int content_length;
	char* content_type;
};




#endif
