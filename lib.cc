/*************************************************************************
    > File Name: lib.c
	> Author: hcyvan
	> Mail: navych@126.com 
	> Created Time: 2015年05月12日 星期二 23时24分12秒
************************************************************************/
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
