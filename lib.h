#ifndef _LIB_H_
#define _LIB_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <unordered_map>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include <regex>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
using namespace std;

typedef struct addrinfo* AddrInfo;

// the function prototype decleared in <string.h>
//extern char* strdup(char*);
// if malloc() return NULL, call exit().
void *checked_malloc(int);
// perror() massage and eixt()
void errorExit(const char*);
void errorExit(const string);
/** string split:
	str: The string to be split.
	vec: The container to put the splited string.
	delim: The set of delimiters. 
	It return the num of splited strings. If it return 1, then we konw 
	the string has not been splited. If it return 0, we konw the str is 
	made up of the delimiters **/
int split(const string& str,vector<string> & vec, const string& delims);
		
#endif
