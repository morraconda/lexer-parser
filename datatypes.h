#ifndef DATATYPES_H
#define DATATYPES_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const int MAX_LEXEME;
extern const int MAX_TOKENS;

typedef enum Symbol {
    // terminals
    IF, THEN, ELSE, 
    WHILE, DO, SKIP, 
    PLUS, MINUS, MULT, 
    NOT, AND, OR,
    TRUE, FALSE, 
    GREATER, EQUALS, 
    LPAREN, RPAREN, LBRACKET, RBRACKET,
    SEMICOLON, ASSIGN, END,
    NUM, ID, // must contain lexeme
    NONE,

    // non-terminals
    START, 
    STATEMENT, AATOM, BEXP

} Symbol;

// token struct
typedef struct Token {
    Symbol symbol;
    char* lexeme;
} Token;

// state struct
typedef struct State {
    bool error;
    char* errorMessage;
    bool done;
    int tokenCount;
    int current;
    int inputLength;
    const char* input;
    Token* tokens;
} State;

typedef struct Rule {
    int length;
    Symbol* contents;
} Rule;

typedef Rule** ParseTable;

// abstract syntax tree data structure
typedef struct AST {
    Token data;
    int childCount;
    struct AST* parent;
    struct AST** children;
} AST;

// check whether symbol is terminal
bool isTerminal(Symbol s);

// returns token applicable to alpha string
Token getTokenFromWord(char* word);

bool strEquals(char* word1, char* word2);

bool tokenEquals(Token a, Token b);
void printToken(Token t);
void printTokens(Token* t, int n);
void freeTokens(Token* tokens, int n);

// initialise state with input string
State* newState(char in[]);
bool stateEquals(State a, State b);
void printState(State *s);
void freeState(State *s);

// initialise tree
AST* newTree(int childCount, Token data, AST* parent);

// attempt to add child to parent, return false if not possible
bool addChild(AST* parent, AST* child);

bool treeEquals(AST* tree1, AST* tree2);
void printTree(AST* tree);
void freeTree(AST* tree);

// get rule from parse table given next terminal and symbol in sentential form
Rule getRuleFromParseTable(Symbol terminal, Symbol next, ParseTable table);

#endif
