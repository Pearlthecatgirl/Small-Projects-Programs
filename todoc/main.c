#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <curses.h>

struct arg {
	char *filepath;
	int filepath_len;
	char **contents;
	unsigned long int *content_len; // Length of each line
	int contentc; // Number of total lines
};

int util_load(struct arg *args) {
	FILE *fptr;
}

int
main(int argc, char **argv) {
	struct arg *args;
	if (argc<3) {
		fprintf(stdout, "Usage: \n", argc);
		return 0;
	} else 
		// Check for access perms
		if (access(argv[3], R_OK || W_OK)!=0) {
			fprintf(stderr, "ERROR 1: filepath invalid or insufficient perms\n (line: %d)", __LINE__);
			return -1;	
		}

		args=malloc(sizeof(struct arg));
		args->filepath_len=(int)strlen(argv[3]);
		args->filepath=argv[3];
		fprintf(stdout, "%s\n", args->filepath);
		// Load generically here
		if (!strcmp(argv[2], "-motd")) {
			// Display in stdout only, no interaction
		} else if (!strcmp(argv[2], "-md")) {
			// Open in a markdown somehow
		} else if (!strcmp(argv[2], "-tty")) {
			// Use curses.h
	}

	return 0;
}
