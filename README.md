Lexer takes a string of the while programming language, and breaks it 
down into a list of tokens. 

Parser (WIP) takes that list of tokens, checks whether it is valid, and if it 
is valid outputs it into Abstract Syntax Tree based on an LL(1) parse table
that it is given.

Usage: "make" to build
"./test" to test
"./main "[text]" to parse literal text (text must be in quotes)
DOESN'T WORK YET - "./main f [filename] to parse the context of a .txt file

Example Lexer Inputs/Outputs:
./main " count <- 0; while 6 > count do if true then count <- count + 1 else skip $ "
Lexer Input: " count <- 0; while 6 > count do if true then count <- count + 1 else skip $ "
Lexer Output: [id:'count', <-, num:'0', ;, while, num:'6', >, id:'count', do, if, true, then, id:'count', <-, id:'count', +, num:'1', else, skip, END]
Lexer Error: none

Lexer Input: "count <- 0; while 6 > count do if true then count <- count + 1 else skip"
Lexer Output: [id:'count', <-, num:'0', ;, while, num:'6', >, id:'count', do, if, true, then, id:'count', <-, id:'count', +, num:'1', else, skip]
Lexer Error: ERR_NO_EOF

Lexer Input: "count <- 0; while 6 >% count do if true then count <- count + 1 else skip  "
Lexer Output: [id:'count', <-, num:'0', ;, while, num:'6', >]
Lexer Error: ERR_UNEXPECTED_CHAR

Lexer Input: "aaaaaaa2bbbb123123123aaaaa$"
Lexer Output: [id:'aaaaaaa', num:'2', id:'bbbb', num:'123123123', id:'aaaaa', END]
Lexer Error: none

Lexer Input: "qwertyuiopasdfghjklzxcvbnm$"
Lexer Output: [id:'qwertyuiopasdfg']
Lexer Error: ERR_ID_TOO_LONG

