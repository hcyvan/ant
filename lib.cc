#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
void* checked_malloc(int n)
{
	void *p=malloc(n);
	if(!p){
		char msg[]="bad malloc\n";
		errorExit(msg);
	}
	return p;
}
void errorExit(char* s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int split(const string& str,vector<string> & vec, const string& delims)
{
	string::size_type begIdx, endIdx;	
	int count=0;
	// find the beginning of the first word	
	begIdx=str.find_first_not_of(delims);
	while(begIdx != string::npos){
		endIdx=str.find_first_of(delims, begIdx);
		if(endIdx==string::npos){
			endIdx=str.length();
		}
		vec.push_back(str.substr(begIdx,endIdx-begIdx));
		++count;
		
		// find the beginning of the next word
		begIdx=str.find_first_not_of(delims,endIdx);
	}
	return count;
}




	
