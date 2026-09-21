program
    → declaration*

declaration
    → letDeclaration
    | functionDeclaration
    | statement

statement
    → whileStatement
    | ifStatement
    | returnStatement
    | expressionStatement

expression
    → Pratt parser
