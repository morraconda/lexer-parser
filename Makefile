main: main.c datatypes.c lexer.c parser.c
	clang -std=c11 -Wall -pedantic -g datatypes.c lexer.c parser.c main.c -o main \
	    -fsanitize=undefined -fsanitize=address -I.

test: test.c datatypes.c datatypesTest.c lexer.c lexerTest.c parser.c parserTest.c 
	clang -std=c11 -Wall -pedantic -g datatypes.c datatypesTest.c lexer.c lexerTest.c parser.c parserTest.c test.c -o test \
	    -fsanitize=undefined -fsanitize=address -I.