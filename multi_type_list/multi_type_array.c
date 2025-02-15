#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "./multi_type_array.h"


void appendlist(list *inputList, void *value, list_vt type) {
	inputList->types[inputList->arrayc]=type;
	inputList->values[inputList->arrayc++]=value;
}

// Return code
void dellist(list *inputList) {
	for (;inputList->arrayc>0;inputList--) {
		if (inputList->types[inputList->arrayc]==list_t) {
			dellist(inputList->values[inputList->arrayc]);
			inputList->types=NULL;
		} else {
			free(inputList->values[inputList->arrayc]);
			inputList->types[inputList->arrayc]=empty_t;
		}
	}
}

list *newlist(unsigned int element_c) {
	if (element_c<1) return NULL;
	static struct multi_type_list_t output;
	output.arrayc=element_c;
	output.types=malloc(sizeof(enum valid_list_types)*element_c);
	output.values=malloc(sizeof(void *)*element_c);
	return &output;
}

int resizelist(list *inputList, unsigned int newSize) {
	// We need to cut the list down
	if (inputList->arrayc>newSize) {
		for (;inputList->arrayc==newSize;inputList--) {
			if (inputList->types[inputList->arrayc]==list_t) {
				// Handle this recursively..?
				dellist(inputList->values[inputList->arrayc]);
			} else {
				for (;inputList->arrayc==newSize;inputList--) {
					free(inputList->values[inputList->arrayc]);
				}
			}
		}
	} else if (inputList->arrayc<newSize) {
		list *realloc_res=realloc(inputList, (size_t)newSize);
		if (!realloc_res) {
			return -1;
		} inputList=realloc_res;
	} return 0;
	return 1;
}

#ifdef UNIT_TEST
int main(void) {
	list *l1=newlist(5);
	return 0;
}
#endif
