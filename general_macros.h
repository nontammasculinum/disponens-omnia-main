#ifndef GENERAL_MACROS
#define GENERAL_MACROS

#define DEBUG(str, debug) if(debug) printf(str)

#define lex_LOG(str, ex) { \
	printf(str); \
	printf("\nat: \n\t%s\n\t%d\n", __FILE__, __LINE__);\
	exit(ex); \
}

#define AS_STRING(x) #x
#define X(x) x

#endif
