#include "datatypes.h"
#include "parser.h"

// check if token string is valid in language
bool validTokenString(Token* string, ParseTable parseTable) {
    return parse(string, parseTable) == NULL;
}

// parse string, with a parent node and next symbol in sentinal form 
// hence why LL(1) is required
AST* parseHelper(AST* parent, Symbol next, Token* string, ParseTable parseTable) {
    Token current = string[0];
    Rule rule = getRuleFromParseTable(current.symbol, next, parseTable);
    int n = rule.length;
    // data for the current node is the next symbol in the string
    AST* tree = newTree(n, current, parent);
    for (int i=0; i<n; i++) {
        Symbol s = rule.contents[i];
        // if symbol is terminal, attempt to eat it
        if (isTerminal(s)) {
            if (current.symbol == s) {
                string++;
            }
            else return NULL;
        }
        // if symbol is non-terminal, recurse and add the child's tree to the current tree
        else {
            AST* child = parseHelper(tree, s, string, parseTable);
            bool err = addChild(tree, child);
            if (err) return NULL;
        }
    }

    return tree;
}

// parse string
AST* parse(Token* string, ParseTable parseTable) {
    return parseHelper(NULL, START, string, parseTable);
}
