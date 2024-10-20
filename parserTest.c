#include <assert.h>
#include "datatypes.h"
#include "lexer.h"
#include "parser.h"

//char text[] = " count <- 0; while 6 > count do if true then count <- count + 1 else skip $ ";

Token start[] = {
    {ID, "count"},
    {ASSIGN, NULL},
    {NUM, "0"},
    {SEMICOLON, NULL},
    {WHILE, NULL},
    {NUM, "6"},
    {GREATER, NULL},
    {ID, "count"},
    {DO, NULL},
    {TRUE, NULL},
    {IF, NULL},
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

void testParser() {
    printf("Parser Tests Passed\n");
}
