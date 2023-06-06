#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "general_macros.h"

#ifndef LEX_DEF
#define LEX_DEF

#define FOREACH_TOKEN_TYPE(T) { \
	T(t_return), T(t_if), T(t_else), T(t_struct), T(t_enum), T(t_union), T(t_mut), \
	T(t_int), T(t_char), T(t_float), T(t_add), T(t_sub), T(t_mul), T(t_div), \
	T(t_and), T(t_or), T(t_equ), T(t_not), T(t_compl), T(t_xor), T(t_less), T(t_great), \
	T(t_com), T(t_dot), T(t_open), T(t_close), \
	T(t_square_op), T(t_square_cl), \
	T(t_block_op), T(t_block_cl), \
	T(t_int_c), T(t_char_c), T(t_float_c), \
	T(t_iden), T(t_semi) \
}

enum token_type FOREACH_TOKEN_TYPE(X);

enum value_type {
	v_int,
	v_char,
	v_str,
	v_float
};

//value is alloced
struct token {
	int type;
	char *value; int sz;
	int v_type;
};

struct token token_new(int type, char *value, int sz, int v_type);
void token_free(struct token tok);
void token_represent(struct token tok, int *index, int ln);
void token_array_represent(struct token *tok, int sz);

void unalloced_token_array_free(struct token *tokens, int sz);
void alloced_token_array_free(struct token *tokens, int sz);

struct token *lex(char *content, int *size);

#endif







