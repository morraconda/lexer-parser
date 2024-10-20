#include "datatypes.h"

bool strEquals(char* str1, char* str2) { return strcmp(str1, str2) == 0; }
bool isTerminal(Symbol s) { return s <= NONE; }

// returns token applicable to alpha string
Token getTokenFromWord(char* word) {
    if (strEquals(word, "true")) return (Token) {TRUE, NULL};
    else if (strEquals(word, "false")) return (Token) {FALSE, NULL};
    else if (strEquals(word, "while")) return (Token) {WHILE, NULL};
    else if (strEquals(word, "do")) return (Token) {DO, NULL};
    else if (strEquals(word, "skip")) return (Token) {SKIP, NULL};
    else if (strEquals(word, "if")) return (Token) {IF, NULL};
    else if (strEquals(word, "then")) return (Token) {THEN, NULL};
    else if (strEquals(word, "else")) return (Token) {ELSE, NULL};
    else {
        char* str = malloc(strlen(word) + 1);
        strcpy(str, word);
        return (Token) {ID, str};
    }
}

// check token equality, lexeme should be NULL in all cases except ID/NUM tokens
bool tokenEquals(Token a, Token b) {
    Symbol fst = a.symbol;
    if (fst != b.symbol) return false;
    if (fst == NUM || fst == ID) {
        if (!strEquals(a.lexeme, b.lexeme)) return false;
    }
    else if (a.lexeme != NULL || b.lexeme != NULL) return false;
    return true;
}

// display token contents
// not pretty but i don't think there's a better way to do it
void printToken(Token t) {
    char* symbolName;
    switch(t.symbol) {
        case IF:
            symbolName = "if";
            break;
        case THEN:
            symbolName = "then";
            break;
        case ELSE:
            symbolName = "else";
            break;
        case WHILE:
            symbolName = "while";
            break;
        case DO:
            symbolName = "do"; 
            break;
        case SKIP:
            symbolName = "skip";
            break;
        case PLUS:
            symbolName = "+";
            break;
        case MINUS:
            symbolName = "-";
            break;
        case MULT:
            symbolName = "*";
            break;
        case NOT:
            symbolName = "!";
            break;
        case AND:
            symbolName = "&&";
            break;
        case OR:
            symbolName = "||";
            break;
        case TRUE:
            symbolName = "true";
            break;
        case FALSE:
            symbolName = "false";
            break;
        case GREATER:
            symbolName = ">";
            break;
        case EQUALS:
            symbolName = "=";
            break;
        case LPAREN:
            symbolName = "(";
            break;
        case RPAREN:
            symbolName = ")";
            break;
        case LBRACKET:
            symbolName = "{";
            break;
        case RBRACKET:
            symbolName = "}";
            break;
        case SEMICOLON:
            symbolName = ";";
            break;
        case ASSIGN: 
            symbolName = "<-";
            break;
        case END: 
            symbolName = "END";
            break;
        case NUM: 
            symbolName = "num";
            break;
        case ID: 
            symbolName = "id";
            break;
        case NONE: 
            symbolName = "NONE";
            break;
        case START: 
            symbolName = "Start";
            break;
        case STATEMENT:
            symbolName = "Statement";
            break;
        case AATOM: 
            symbolName = "Aatom";
            break;
        case BEXP:
            symbolName = "Bexp";
            break;
    }
    printf("%s", symbolName);
    if (t.lexeme != NULL) printf(":'%s'", t.lexeme);
}

// display list of token contents 
void printTokens(Token* t, int n) {
    printf("[");
    for (int i=0; i<n; i++) {
        if (i > 0) printf(", ");
        printToken(t[i]);
    }
    printf("]\n");
}

void freeTokens(Token* tokens, int n) {
    for (int i=0; i<n; i++) {
        if (tokens[i].lexeme != NULL) free(tokens[i].lexeme);
    }
    free(tokens);
}

// initialise state with input string
State* newState(char in[]) {
    State* starting = malloc(sizeof(State));
    starting->error = false;
    starting->errorMessage = "none";
    starting->done = false;
    starting->tokenCount = 0;
    starting->current = 0;
    starting->inputLength = strlen(in);
    starting->input = in;
    starting->tokens = malloc(MAX_TOKENS * sizeof(Token));
    return starting;
}

bool stateEquals(State a, State b) {
    if (a.error != b.error) return false;
    if (!strEquals(a.errorMessage, b.errorMessage)) return false;
    if (a.done != b.done) return false;
    if (a.tokenCount != b.tokenCount) return false;
    if (a.current != b.current) return false;
    if (a.inputLength != b.inputLength) return false;
    for (int i=0; i<a.tokenCount; i++) {
        if (!tokenEquals(a.tokens[i], b.tokens[i])) return false;
    }
    return true;
}

// display state contents
void printState(State *s) {
    if (s->error) printf("%s | ", s->errorMessage);
    else printf("Okay | ");
    printf("Done: %d | Tokens: %d | Char: %d/%d | Input: '%s'\n", 
    s->done, s->tokenCount, s->current, s->inputLength, s->input + s->current);
    printTokens(s->tokens, s->tokenCount);
}

// free state malloc'd memory
void freeState(State *s) {
    freeTokens(s->tokens, s->tokenCount);
    free(s);
}

// initialise tree
AST* newTree(int childCount, Token data, AST* parent) {
    AST* tree = malloc(sizeof(AST));
    tree->data = data;
    tree->childCount = childCount;
    tree->parent = parent;
    tree->children = malloc(childCount * sizeof(AST*));
    for (int i=0; i<childCount; i++) { tree->children[i] = NULL; }
    return tree;
}

// attempt to add child to parent, return false if not possible
bool addChild(AST* parent, AST* child) {
    for (int i=0; i<parent->childCount; i++) {
        if (parent->children[i] == NULL) {
            parent->children[i] = child;
            return true;
        }
    }
    return false;
}

void printTree(AST* tree) {}

// depth first free using recursion
void freeTree(AST* tree) {
    for (int i=0; i<tree->childCount; i++) { freeTree(tree->children[i]); }
    free(tree->children);
    free(tree);
}

// get rule from parse table given next terminal and symbol in sentential form
Rule getRuleFromParseTable(Symbol terminal, Symbol next, ParseTable table) {
    return table[next][terminal];
}
