#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "./multi_type_array.h"

void appendlist(list *inputList, void *value, list_vt type) {

}

//void appendlist(list *inputList, void *value, list_vt type) {
//	inputList->arrayc++;
//	list_vt *realloc_res_type=realloc(inputList->types, sizeof(enum valid_list_types)*inputList->arrayc);
//	if (!realloc_res_type) CRASH(ENOMEM);
//	inputList->types=realloc_res_type;
//
//	void **realloc_res_val=realloc(inputList->types,sizeof(void *)*inputList->arrayc);
//	if (!realloc_res_val) CRASH(ENOMEM);
//	inputList->values=realloc_res_val;
//
//	inputList->types[inputList->arrayc]=type;
//	inputList->values[inputList->arrayc]=value;
//}

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
	static struct multi_type_list_t output;
	output.types=malloc(sizeof(enum valid_list_types)*element_c);
	if (!output.types) CRASH(ENOMEM);
	output.values=malloc(sizeof(void *)*element_c);
	if (!output.values) CRASH(ENOMEM);
	for (int i=0;i<element_c;i++) output.types[i]=empty_t;
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
	for (int i=0;i<5;i++) printf("%d\n", l1->types[i]);
	
	return 0;
}
#endif
