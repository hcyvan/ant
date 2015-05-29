#ifndef _LIB_H_
#define _LIB_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// the function prototype decleared in <string.h>
//extern char* strdup(char*);
// if malloc() return NULL, call exit().
void *checked_malloc(int);
// perror() massage and eixt()
void errorExit(char*);
		
#endif
