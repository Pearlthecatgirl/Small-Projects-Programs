#pragma once
#include <stdio.h>
#include <stdlib.h>

#define list struct multi_type_list_t

struct multi_type_list_t 
{
	enum valid_list_types {
		int_t, 
		short_t,
		float_t,
		char_t, 
		string_t, // String = char *
		list_t,
	} *types; // Use this to typecast
	int arrayc; // number of elements per array
	void *values;
};
