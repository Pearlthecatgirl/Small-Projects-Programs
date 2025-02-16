#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "./multi_type_array.h"

void _append_list(list *inputList, void *value, list_vt type) { 
	// Dupe code from resizing up. Since function calls are wasted over, head here we are
	resizelist(inputList, inputList->arrayc+1);
	inputList->values[inputList->arrayc-1]=value;
	inputList->types[inputList->arrayc-1]=type;
}

// This is challenging.... TODO
void insertlist(list *inputList, void *value, list_vt type, unsigned int elementn) {
	// Elementn refers to element location. Array starts at 0
	if ((elementn)>inputList->arrayc-1) {
		// Call resize here...
	}
}

// Might need a code review...
void dellist(list *inputList) {
	for (;inputList->arrayc>=0;inputList--) {
		if (inputList->types[inputList->arrayc]==list_t) {
			dellist(inputList->values[inputList->arrayc]);
		} else {
			free(inputList->values[inputList->arrayc]);
			inputList->types[inputList->arrayc]=empty_t;
		}
	}
	free(inputList->types);
	free(inputList->values);
	free(inputList);
}

list *newlist(unsigned int element_c) {
	static struct multi_type_list_t output;
	output.types=malloc(sizeof(enum valid_list_types)*element_c);
	if (!output.types) CRASH(ENOMEM);
	output.values=malloc(sizeof(void *)*element_c);
	if (!output.values) CRASH(ENOMEM);
	for (int i=0;i<element_c;i++) output.types[i]=empty_t;
	return &output;
}

int resizelist(list *inputList, unsigned int newSize) {
	if (newSize!=inputList->arrayc) {
		// If scaling down: free and then realloc to get the memory back
		if (newSize<inputList->arrayc) {
			// use i here to avoid having to -1 every time
			for (int i=inputList->arrayc-1;inputList->arrayc>=newSize;inputList--) {
				if (inputList->types[inputList->arrayc-1]!=list_t) {
					free(inputList->values[inputList->arrayc]);
				} else {
					// Dupe code from dellist. No overhead from calling another function!
					dellist(inputList->values[i]);
				}
			}
		} 

		// Reallocation of memory
		list_vt *types_realloc_res=realloc(inputList->types, sizeof(list_vt)*newSize);
		if (!types_realloc_res) CRASH(ENOMEM);
		inputList->types=types_realloc_res;
		void **values_realloc_res=realloc(inputList->values, sizeof(void *)*newSize);
		if (!values_realloc_res) CRASH(ENOMEM);
		inputList->values=values_realloc_res;
		// Populate the new entries with empty
		for (;inputList->arrayc<=newSize;inputList->arrayc++) inputList->types[inputList->arrayc]=empty_t;
		// Only change the array count after everything is sorted
		inputList->arrayc=newSize;
	}
	return 0; // Success! If newsize is the same as old size, just return 
}

#ifdef UNIT_TEST
int main(void) {
	list *l1=newlist(0);
	char char1='%'; 
	char *str1="abcd";
	_append_list(l1, (void *)&char1, char_t);
	_append_list(l1, (void *)&str1, string_t);

	void **testv=malloc(sizeof(void *)*2);
	//testv[0]=(void *)&char1;
	//testv[1]=(void *)&str1;
	fprintf(stdout, "%c\n", *(char*)l1->values[0]);
	fprintf(stdout, "%s\n", *(char **)l1->values[1]);

	return 0;
}
#endif
