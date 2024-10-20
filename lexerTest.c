#include <assert.h>
#include "datatypes.h"
#include "lexer.h"

char text[] = " count <- 0; while 6 > count do if true then count <- count + 1 else skip $ ";

// this is mutable
State starting = (State) {
    .error = false,
    .errorMessage = "",
    .done = false,
    .tokenCount = 0,
    .current = 0,
    .input = text,
    .inputLength = 76
};

void testMore() {
    assert(more(&starting));
    starting.current = starting.inputLength / 2;
    assert(more(&starting));
    // boundary checks
    starting.current = starting.inputLength - 1;
    assert(more(&starting));
    starting.current = starting.inputLength;
    assert(!more(&starting));
}

void testPeek() {
    starting.current = 0;
    for (int i=0; i<starting.inputLength; i++) {
        assert(peek(&starting) == starting.input[i]);
        starting.current++;
    }
    starting.current = starting.inputLength;
    assert(peek(&starting) == NONE);
}

void testEat() {
    // check cannot eat at end of string
    eat(NONE, &starting);
    assert(starting.error = true);
    assert(strEquals(starting.errorMessage, "ERR_NO_EOF"));
    State* s = newState(text);  
    eat(text[0], s); assert(!s->error); assert(s->current == 1);
    eat(text[1], s); assert(!s->error); assert(s->current == 2);
    eat(text[2], s); assert(!s->error); assert(s->current == 3);
    
    eat(text[4], s); assert(s->error);
    assert(strEquals(s->errorMessage, "ERR_UNEXPECTED_CHAR"));
    freeState(s);
}

void testParseWord() {
    char maxLength[MAX_LEXEME];
    char tooLong[MAX_LEXEME + 1];
    for (int i=0; i<MAX_LEXEME; i++) { 
        maxLength[i] = 'a'; 
        tooLong[i] = 'a';
        }
    maxLength[MAX_LEXEME - 1] = '\0';
    tooLong[MAX_LEXEME] = '\0';

    State *q = newState(maxLength);
    parseWord('a', q);
    assert(!q->error); assert(tokenEquals(q->tokens[0], (Token) {ID, maxLength}));

    State *r = newState(tooLong);
    parseWord('a', r);
    assert(r->error); assert(strEquals(r->errorMessage, "ERR_ID_TOO_LONG"));

    State *s = newState(text);
    s->current = 1;
    parseWord('c', s);
    assert(!s->error); assert(s->current == 6); assert(s->tokenCount == 1);
    assert(tokenEquals(s->tokens[0], (Token) {ID, "count"}));

    s->current = 29;
    parseWord('d', s);
    assert(!s->error); assert(s->current == 31); assert(s->tokenCount == 2);
    assert(tokenEquals(s->tokens[1], (Token) {DO, NULL}));

    parseWord(' ', s);
    assert(s->error); assert(strEquals(s->errorMessage, "ERR_PARSEWORD_EXPECTED_ALPHA"));

    freeState(q);
    freeState(r);
    freeState(s);
}

void testParseNumber() {
    char maxLength[MAX_LEXEME];
    char tooLong[MAX_LEXEME + 1];
    for (int i=0; i<MAX_LEXEME; i++) { 
        maxLength[i] = '2'; 
        tooLong[i] = '2';
        }
    maxLength[MAX_LEXEME - 1] = '\0';
    tooLong[MAX_LEXEME] = '\0';

    State *q = newState(maxLength);
    parseNumber('2', q);
    assert(!q->error); assert(tokenEquals(q->tokens[0], (Token) {NUM, maxLength}));

    State *r = newState(tooLong);
    parseNumber('2', r);
    assert(r->error); assert(strEquals(r->errorMessage, "ERR_NUM_TOO_LONG"));

    State *s = newState(text);
    s->current = 10;
    parseNumber('0', s);
    assert(!s->error); assert(s->current == 11); assert(s->tokenCount == 1);
    assert(tokenEquals(s->tokens[0], (Token) {NUM, "0"}));

    s->current = 29;
    parseNumber('d', s);
    assert(s->error); assert(strEquals(s->errorMessage, "ERR_PARSENUMBER_EXPECTED_DIGIT"));

    freeState(q);
    freeState(r);
    freeState(s);
}

void testParseOther() {

}

void testNextState() {

}

void testLex() {
    int n = 0;
    bool err = false;
    Token* out = lex(text, &n, &err);
    Token correct[] = {
    {ID, "count"},
    {ASSIGN, NULL},
    {NUM, "0"},
    {SEMICOLON, NULL},
    {WHILE, NULL},
    {NUM, "6"},
    {GREATER, NULL},
    {ID, "count"},
    {DO, NULL},
    {IF, NULL},
    {TRUE, NULL},
    {THEN, NULL},
    {ID, "count"},
    {ASSIGN, NULL},
    {ID, "count"},
    {PLUS, NULL},
    {NUM, "1"},
    {ELSE, NULL},
    {SKIP, NULL},
    {END, NULL}
    };

    assert(!err);
    assert(n == 20);
    for (int i=0; i<n; i++) {
        assert(tokenEquals(out[i], correct[i]));
    }
    freeTokens(out, n);
}

void testLexer() {
    testMore();
    testPeek();
    testEat();
    testParseWord();
    testParseNumber();
    testParseOther();
    testNextState();
    testLex();
    printf("Lexer Tests Passed\n");
}
