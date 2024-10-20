#include "lexer.h"
#include "lexerTest.h"
#include "parser.h"
#include "parserTest.h"

const int MAX_INPUT = 99999;

void printUsage() {
    printf("Usage: \"./test\" to run tests\n");
    printf("\"./main [text]\" to parse literal text (text must be in quotes)\n");
    printf("\"./main f [filename]\" to parse the context of a .txt file\n");
}

char* handleFile(char* filename, bool* err) {
    FILE *in;
    in = fopen(filename, "r");
    if (!in) in = fopen(strcat(filename, ".txt"), "r");
    if (!in) { *err = true; return NULL; }

    char text[MAX_INPUT];
    fclose(in);
    return NULL;
}

int main(int n, char* args[n]) {
    char* text;
    bool badInput = false;
    if (n == 2) { text = args[1]; }
    else if (n == 3) {
        if (strEquals(args[1], "f")) {
            printf("File input handling not yet implemented.\n");
            text = handleFile(args[2], &badInput);
        }
        else badInput = true; 
    }
    else badInput = true;

    if (badInput) {
        printUsage();
        exit(-1);
    }
    else {
        // call parse on text
        int n = 0;
        bool err = false;
        Token* t = lex(text, &n, &err);
        printf("Parser not yet implemented\n");
        freeTokens(t, n);
        return 0;
    }
}
