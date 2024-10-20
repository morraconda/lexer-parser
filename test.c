#include "stdio.h"
#include "datatypesTest.h"
#include "lexerTest.h"
#include "parserTest.h"

int main() {
    testDatatypes();
    testLexer();
    testParser();
    printf("All Tests Passed\n");
    return 0;
}
