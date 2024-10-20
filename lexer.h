#ifndef LEXER_H
#define LEXER_H
#include "datatypes.h"

// while programming language lexer

// check if string has any more input characters
bool more(State *s);

// get next character in string
char peek(State *s);

// consume character, raise error if mismatch
void eat(char c, State *s);

// parse alpha token
void parseWord(char next, State *s);

// parse numeric token
void parseNumber(char next, State *s);

// parse non-alphanumeric token
void parseOther(char next, State *s);

// get next token in input, update state accordingly
void nextState(State *s);

// turn input string into tokens
Token* lex(char* input, int* n, bool* err);

#endif
