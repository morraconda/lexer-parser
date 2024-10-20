#ifndef PARSER_H
#define PARSER_H
#include "datatypes.h"

// check if token string is valid
bool validTokenString(Token* tokens, ParseTable p);

// parse token list 
AST* parse(Token* tokens, ParseTable p);

#endif
