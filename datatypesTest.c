#include <assert.h>
#include "datatypes.h"

char text0[] = " count <- 0; while 6 > count do if true then count <- count + 1 else skip $ ";

// this is mutable
State starting0 = (State) {
    .error = false,
    .errorMessage = "none",
    .done = false,
    .tokenCount = 0,
    .current = 0,
    .input = text0,
    .inputLength = 76
};

void testStateCreation() {
    State* s = newState(text0);
    assert(stateEquals(*s, starting0));
    freeState(s);
}

void testGetTokenFromWord() {
    assert(tokenEquals((Token) {TRUE, NULL}, getTokenFromWord("true")));
    assert(tokenEquals((Token) {FALSE, NULL}, getTokenFromWord("false")));
    assert(tokenEquals((Token) {WHILE, NULL}, getTokenFromWord("while")));
    assert(tokenEquals((Token) {DO, NULL}, getTokenFromWord("do")));
    assert(tokenEquals((Token) {SKIP, NULL}, getTokenFromWord("skip")));
    assert(tokenEquals((Token) {IF, NULL}, getTokenFromWord("if")));
    assert(tokenEquals((Token) {THEN, NULL}, getTokenFromWord("then")));
    assert(tokenEquals((Token) {ELSE, NULL}, getTokenFromWord("else")));
    Token t = getTokenFromWord("whiletrue");
    assert(tokenEquals((Token) {ID, "whiletrue"}, t));
    free(t.lexeme);
}

void testDatatypes() {
    testStateCreation();
    testGetTokenFromWord();
    printf("Datatypes Tests Passed\n");
}
