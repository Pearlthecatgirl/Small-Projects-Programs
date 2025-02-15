#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

enum valid_list_types {
		int_t, 
		short_t,
		float_t,
		char_t, 
		string_t, // String = char *
		list_t,
		empty_t,
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











