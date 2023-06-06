#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comp.h"
#include "general_macros.h"


char *read_file(char *path);

int debug = 1;

int main(int argc, char *argv[]) {
	char *file_content = read_file(argv[1]);
	printf("file read\n");
	int size = 0;
	struct token *lexed_tokens = lex(file_content, &size);
	printf("file lexed\nsize: %d\n", size);
	token_array_represent(lexed_tokens, size);
	alloced_token_array_free(lexed_tokens, size);
}

char *read_file(char *path) {
	FILE *file = fopen(path, "r");
	int size = 0;
	char *ret = malloc(size = (fseek(file, 0L, SEEK_END), ftell(file)));
	rewind(file);
	fread(ret, 1, size, file);
	fclose(file);
	return ret;
}
