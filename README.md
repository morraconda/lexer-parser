Lexer takes a string of the while programming language, and breaks it 
down into a list of tokens. 

Parser (WIP) takes that list of tokens, checks whether it is valid, and if it 
is valid outputs it into Abstract Syntax Tree based on an LL(1) parse table
that it is given.

Usage: "make" to build <br>
"./test" to test <br>
"./main "[text]" to parse literal text (text must be in quotes) <br>
DOESN'T WORK YET - "./main f [filename] to parse the context of a .txt file

Example Lexer Inputs/Outputs: <br>
./main " count <- 0; while 6 > count do if true then count <- count + 1 else skip $ " <br>
Lexer Input: " count <- 0; while 6 > count do if true then count <- count + 1 else skip $ " <br>
Lexer Output: [id:'count', <-, num:'0', ;, while, num:'6', >, id:'count', do, if, true, then, id:'count', <-, id:'count', +, num:'1', else, skip, END] <br>
Lexer Error: none <br>

Lexer Input: "count <- 0; while 6 > count do if true then count <- count + 1 else skip" <br>
Lexer Output: [id:'count', <-, num:'0', ;, while, num:'6', >, id:'count', do, if, true, then, id:'count', <-, id:'count', +, num:'1', else, skip] <br>
Lexer Error: ERR_NO_EOF <br>

Lexer Input: "count <- 0; while 6 >% count do if true then count <- count + 1 else skip  " <br>
Lexer Output: [id:'count', <-, num:'0', ;, while, num:'6', >] <br>
Lexer Error: ERR_UNEXPECTED_CHAR <br>

Lexer Input: "aaaaaaa2bbbb123123123aaaaa$" <br>
Lexer Output: [id:'aaaaaaa', num:'2', id:'bbbb', num:'123123123', id:'aaaaa', END] <br>
Lexer Error: none <br>

Lexer Input: "qwertyuiopasdfghjklzxcvbnm$" <br>
Lexer Output: [id:'qwertyuiopasdfg'] <br>
Lexer Error: ERR_ID_TOO_LONG <br>

