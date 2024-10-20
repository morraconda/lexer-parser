#include "datatypes.h"
#include "lexer.h"

const int MAX_LEXEME = 16;
const int MAX_TOKENS = 100;

// while programming language lexer

// check if string has any more input characters
bool more(State *s) { return s->inputLength > s->current; } 

// get next character in string
char peek(State *s) {
    //printState(s);
    if (more(s)) return s->input[s->current]; 
    else return NONE;
}

// consume character, raise error if mismatch
void eat(char c, State *s) {
    if (!more(s)) {
        s->error = true;
        s->errorMessage = "ERR_NO_EOF";
    }
    else if (c != peek(s)) {
        s->error = true;
        s->errorMessage = "ERR_UNEXPECTED_CHAR";
    }
    else s->current++;
}

// parse alpha token
void parseWord(char next, State *s) {
    if (!isalpha(next)) {
        s->error = true;
        s->errorMessage = "ERR_PARSEWORD_EXPECTED_ALPHA";
        return;
    }
    int i = 0;
    char word[MAX_LEXEME];
    while (isalpha(next)) {
        eat(next, s);
        word[i] = next;
        i++;
        next = peek(s);
        if (i == MAX_LEXEME) {
            s->error = true;
            s->errorMessage = "ERR_ID_TOO_LONG";
            i--;
            break;
        }
    }
    word[i] = '\0';
    s->tokens[s->tokenCount] = getTokenFromWord(word);
    s->tokenCount++;
}

// parse numeric token
void parseNumber(char next, State *s) {
    if (!isdigit(next)) {
        s->error = true;
        s->errorMessage = "ERR_PARSENUMBER_EXPECTED_DIGIT";
        return;
    }
    int i = 0;
    char num[MAX_LEXEME];
    while (isdigit(next)) {
        eat(next, s);
        num[i] = next;
        i++;
        next = peek(s);
        if (i == MAX_LEXEME) {
            s->error = true;
            s->errorMessage = "ERR_NUM_TOO_LONG";
            i--;
            break;
        }
    }
    num[i] = '\0';
    char* str = malloc(i + 1);
    strcpy(str, num);    
    s->tokens[s->tokenCount] = (Token) {NUM, str};
    s->tokenCount++;
}

// parse non-alphanumeric token
void parseOther(char next, State *s) {
    if (isdigit(next) || isalpha(next)) {
        s->error = true;
        s->errorMessage = "ERR_PARSEOTHER_EXPECTED_OTHER";
        return;
    }
    eat(next, s);
    if (s->error) return;
    
    Symbol symbol;
    switch (next) {
        case '&':
            eat('&', s);
            symbol = AND;
            break;
        case '|':
            eat('|', s);
            symbol = OR;
            break;
        case '!':
            symbol = NOT;
            break;
        case '+':
            symbol = PLUS;
            break;
        case '-':
            symbol = MINUS;
            break;
        case '*':
            symbol = MULT;
            break;
        case '>':
            symbol = GREATER;
            break;
        case '=':
            symbol = EQUALS; 
            break;
        case '(':
            symbol = LPAREN;
            break;
        case ')':
            symbol = RPAREN;
            break;
        case '{':
            symbol = LBRACKET;
            break;
        case '}':
            symbol = RBRACKET;
            break;
        case '<':
            eat('-', s);
            symbol = ASSIGN;
            break;
        case ';':
            symbol = SEMICOLON;
            break;
        case '$':
            symbol = END;
            s->done = true;
            break;
        default:
            s->error = true;
            s->errorMessage = "ERR_UNEXPECTED_CHAR";
            return;
    }
    s->tokens[s->tokenCount] = (Token) {symbol, NULL};
    s->tokenCount++;
}

// get next token in input, update state accordingly
void nextState(State *s) {
    char next = peek(s);
    while (next == ' ') {
        eat(next, s);
        next = peek(s);
    }
    if (s->tokenCount == MAX_TOKENS) {
        s->error = true;
        s->errorMessage = "ERR_MAX_TOKENS";
    }
    if (!s->error) {
        if (isalpha(next)) parseWord(next, s);
        else if (isdigit(next)) parseNumber(next, s);
        else parseOther(next, s);
    }
}

// turn input string into tokens
Token* lex(char* input, int* n, bool* err) {
    State* s = newState(input);
    while (!s->error && !s->done) {
        nextState(s);
    }
    Token* output = s->tokens;
    *n = s->tokenCount;
    *err = s->error;
    printf("Lexer Input: \"%s\"\n", input);
    printf("Lexer Output: ");
    printTokens(output, *n);
    printf("Lexer Error: %s\n\n", s->errorMessage);

    // don't free the full state as tokens need to be returned
    free(s);
    return output;
}
