#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "./multi_type_array.h"

void _list_append(list *inputList, void *value, list_vt type) { 
	list_resize(inputList, inputList->arrayc+1);
	inputList->values[inputList->arrayc-1]=value;
	inputList->types[inputList->arrayc-1]=type;
}

// This is challenging.... TODO
void _element_insert_single(list *inputList, void *value, list_vt type, unsigned int element_n) {
	// Arrayc is the count of elements, element_n is the nth position (starts at 0)
	unsigned int element_c=element_n+1;
	if (element_c>inputList->arrayc) {
		// Resize and then shuffle everything up 1
		list_resize(inputList, inputList->arrayc+1);
		// arrayc-1 should be empty.. move from arrayc-2 to arrayc-1
		for (int i=inputList->arrayc-2;i>element_n;i--) {
			inputList->values[i+1]=inputList->values[i];
			inputList->types[i+1]=inputList->types[i];
		} 
		inputList->types[element_n]=type;
		inputList->values[element_n]=value;
	} else if (element_c<inputList->arrayc) {
	
	} else _list_append(inputList, (void *)value, type); // If it is placed at this position, its the same as an append
}

// Might need a code review...
void list_del(list *inputList) {
	for (;inputList->arrayc>=0;inputList--) {
		if (inputList->types[inputList->arrayc]==list_t) {
			list_del(inputList->values[inputList->arrayc]);
		} else {
			free(inputList->values[inputList->arrayc]);
			inputList->types[inputList->arrayc]=empty_t;
		}
	}
	free(inputList->types);
	free(inputList->values);
	free(inputList);
}

list *list_create(unsigned int element_c) {
	static struct multi_type_list_t output;
	output.types=malloc(sizeof(enum valid_list_types)*element_c);
	if (!output.types) CRASH(ENOMEM);
	output.values=malloc(sizeof(void *)*element_c);
	if (!output.values) CRASH(ENOMEM);
	for (int i=0;i<element_c;i++) output.types[i]=empty_t;
	return &output;
}

int list_resize(list *inputList, unsigned int newSize) {
	if (newSize!=inputList->arrayc) {
		// If scaling down: free and then realloc to get the memory back
		if (newSize<inputList->arrayc) {
			// use i here to avoid having to -1 every time
			for (int i=inputList->arrayc-1;inputList->arrayc>=newSize;inputList--) {
				if (inputList->types[inputList->arrayc-1]!=list_t) {
					free(inputList->values[inputList->arrayc]);
				} else {
					list_del(inputList->values[i]);
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
	//list *l1=list_create(0);
	//list *l2=list_create(0);
	//char char1='%'; 
	//char char2='*';
	//char *str1="abcd";
	//char *str2="bcde";
	//appendlist(l1, str1, char_t);
	//appendlist(l2, str2, char_t);

	////_list_append(l1, (void *)&l2, list_t);
	//appendlist(l1, l2, list_t);
	////_element_insert_single(l1, (void *)&str1, string_t, 1);

	//fprintf(stdout, "%s\n", *(char **)l1->values[0]);
	//fprintf(stdout, "%s\n", *(char **)l2->values[0]);
	//fprintf(stdout, "%s\n", *(char **)(*(list **)l1->values[1])->values[0]);


	list *l1=list_create(0);
	list *l2=list_create(0);
	char *str0="abcd";
	char *str1="efgh";
	//appendlist(l1, str0, string_t);
	//appendlist(l2, str0, string_t);
	//appendlist(l1, l2, list_t);
	l1->values[0]=(void *)&str0;
	l2->values[0]=(void *)&str1;
	l1->values[1]=(void *)&l2;
	fprintf(stdout, "%p\n", (char **)l1->values[0]);
	fprintf(stdout, "%p\n", &str0);
	fprintf(stdout, "%p\n", &str1);
	fprintf(stdout, "%p\n", (char **)l1->values[0]);
	fprintf(stdout, "%p\n", (char **)l2->values[0]);
	fprintf(stdout, "%p\n", (char **)(*(list **)l1->values[1])->values[0]);

	return 0;
}
#endif
