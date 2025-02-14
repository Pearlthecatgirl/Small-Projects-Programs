#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct multi_type_list_t list;

struct multi_type_list_t
{
	enum valid_list_types {
		int_t, 
		short_t,
		float_t,
		char_t, 
		string_t, // String = char *
		list_t,
		empty_t,
	} *types; // Use this to typecast
	int arrayc; // number of elements per array
	void **values;

};

list *newlist(int element_c);
int resizelist(list *inputList, unsigned int newSize);
