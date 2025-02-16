#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifndef CRASH 
#define CRASH(errnum) {fprintf(stderr, "FATAL ERROR (line %d). Code: %s\n", __LINE__, strerror(errnum));exit(errnum);}
#endif

#ifndef WARN
#define WARN(msg) {fprintf(stderr, "Warning: %s (line: %d)\n", msg, __LINE__);}
#endif

enum valid_list_types {
		empty_t,
		int_t, 
		short_t,
		float_t,
		char_t, 
		string_t, // String = char *
		list_t,
}; // Use this to typecast

typedef struct multi_type_list_t list;
typedef enum valid_list_types list_vt;

struct multi_type_list_t
{
	unsigned int arrayc; // number of elements per array
	list_vt *types;
	void **values;

};

void appendlist(list *inputList, void *value, list_vt type);
void dellist(list *inputList);
list *newlist(unsigned int element_c);
int resizelist(list *inputList, unsigned int newSize);











