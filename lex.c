#include "comp.h"

int operator(char in) {
	switch(in) {
	case '+': return t_add;
	case '-': return t_sub;
	case '*': return t_mul;
	case '/': return t_div;
	case ',': return t_com;
	case '.': return t_dot;
	case '&': return t_and;
	case '|': return t_or;
	case '^': return t_xor;
	case '=': return t_equ;
	case '!': return t_not;
	case '~': return t_compl;
	case '<': return t_less;
	case '>': return t_great;
	case '(': return t_open;
	case ')': return t_close;
	case '[': return t_square_op;
	case ']': return t_square_cl;
	case '{': return t_block_op;
	case '}': return t_block_cl;
	case ';': return t_semi;
	default:
		return -1;
	}
}

int token_string_get_type(char *string) {
	if(strcmp(string, "return") == 0) return t_return;
	else if(strcmp(string, "if") == 0) return t_if;
	else if(strcmp(string, "else") == 0) return t_else;
	else if(strcmp(string, "struct") == 0) return t_struct;
	else if(strcmp(string, "enum") == 0) return t_enum;
	else if(strcmp(string, "union") == 0) return t_union;
	else if(strcmp(string, "mut") == 0) return t_mut;
	else if(strcmp(string, "int") == 0) return t_int;
	else if(strcmp(string, "float") == 0) return t_float;
	else if(strcmp(string, "char") == 0) return t_char;
	else {
		if(string[0] == '\'') return t_char_c;
		else for(char *x = string; *x; x++) {
			if(!isdigit(*x))
				if(*x != '.') return t_iden;
				else return t_float_c;
		}
		return t_int_c;
	}
	return -1;
}

char *token_string_get_value(char *string, int type, int *sz) {
	switch(type) {
	case t_iden:
	case t_int_c:
	case t_float_c: {
		*sz = strlen(string) + 1;
		char *ret_ = malloc(*sz);
		memcpy(ret_, string, *sz);
		return ret_;
					}
	case t_char_c: {
		*sz = 2;
		char ret[2] = {string[1], '\0'};
		char *ret_ = malloc(2);
		memcpy(ret_, ret, 2);
		return ret_;
				 }
	default: return calloc(1,1);
	}
}

struct token token_new(int type, char *value, int sz, int v_type) {
	struct token ret;
	ret.type = type;
	ret.value = value;
	ret.sz = sz;
	ret.v_type = v_type;
	return ret;
}

void token_free(struct token tok) {
	tok.type = -1;
	free(tok.value);
	tok.sz = 0;
	tok.v_type = -1;
}

void token_represent(struct token tok, int *index, int ln) {
	const char *type_names[] = FOREACH_TOKEN_TYPE(AS_STRING);
	if(index != 0) printf("%s, ", type_names[tok.type]);
	else printf("%s\n", type_names[tok.type]);
	if(*index > ln) *index = 0;
}

void token_array_represent(struct token *tok, int sz) {
	for(int i = 0; i < sz; i++) switch(tok[i].type) {
	case t_return: printf("return "); break;
	case t_if: printf("if "); break;
	case t_else: printf("else "); break;
	case t_struct: printf("struct "); break;
	case t_enum: printf("enum "); break;
	case t_union: printf("union "); break;
	case t_mut: printf("mut "); break;
	case t_int: printf("int "); break;
	case t_char: printf("char "); break;
	case t_float: printf("float "); break;
	case t_open: printf("("); break;
	case t_close: printf(")"); break;
	case t_add: printf("+ "); break;
	case t_sub: printf("- "); break;
	case t_mul: printf("* "); break;
	case t_div: printf("/ "); break;
	case t_and: printf("& "); break;
	case t_or: printf("| "); break;
	case t_equ: printf("= "); break;
	case t_not: printf("!"); break;
	case t_compl: printf("~"); break;
	case t_xor: printf("^ "); break;
	case t_less: printf("< "); break;
	case t_great: printf("> "); break;
	case t_square_op: printf("["); break;
	case t_square_cl: printf("]"); break;
	case t_block_op: printf("{\n"); break;
	case t_block_cl: printf("}\n"); break;
	case t_char_c:
	case t_float_c:
	case t_iden:
	case t_int_c: printf("%s ", tok[i].value); break;
	case t_semi: printf(";\n");
	}
}

void alloced_token_array_free(struct token *tokens, int sz) {
	unalloced_token_array_free(tokens, sz);
	free(tokens);
}
void unalloced_token_array_free(struct token *tokens, int sz) {
	struct token *t;
	for(int i = 0; t = tokens + i, i < sz; i++)
		token_free(*t);
}

struct token *lex(char *content, int *size) {
	struct token *ret = malloc(sizeof(struct token)); *size = 0;
	char *tok = calloc(1, 1); int sz = 1;
	for(char *c = content; *c; c++) {
		int op;
		if((op = operator(*c)) + 1) {
			int type = 0;
			if(strcmp("", tok) != 0) {
				printf(" |%s : %d| \n", tok, type = token_string_get_type(tok));
				ret = realloc(ret, ((*size) + 2) * sizeof(struct token));
				*size += 2;
				if(ret == NULL) lex_LOG("realloced into NULL", 1)
				int size_ = 0;
				ret[(*size) - 2] = token_new(type, (token_string_get_value(tok, type, &size_)), size_, v_char);
			} else ret = realloc(ret, (++(*size)) * sizeof(struct token));
			ret[*size - 1] = token_new(op, calloc(1,1), 1, v_char);
			free(tok); tok = calloc(1,1); sz = 1;
			continue;
		}
		else if((*c == ' ' || *c == '\n' || *c == '\t') && (*(c + 1) != ' ' && *(c + 1) != '\n' && *(c + 1) != '\t') && strcmp("", tok) != 0) {
			if(strcmp("", tok) != 0) {
				int type = 0;
				printf(" |%s : %d| \n", tok, type = token_string_get_type(tok));
				ret = realloc(ret, (++(*size)) * sizeof(struct token));
				if(ret == NULL) lex_LOG("realloced into NULL", 1)
				int size_ = 0;
				ret[*size - 1] = token_new(type, (token_string_get_value(tok, type, &size_)), size_, v_char);
			}
			free(tok); tok = calloc(1,1); sz = 1;
			continue;
		}
		if(*c == ' ' || *c == '\n' || *c == '\t') continue;
		tok = realloc(tok, ++sz);
		tok[sz - 2] = *c;
		printf("%c", *c);
		tok[sz - 1] = '\0';
	}
	free(tok);
	return ret;
}
