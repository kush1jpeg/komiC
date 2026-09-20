# komiLang

> **komiLang** is a small, readable, C/Python-inspired language designed to be easy to write, easy to read, and simple enough to compile from scratch.

**Status:** Draft language specification — v0.1

---

## 1. Design Goals

komiLang should be:

- **Simple** — minimal syntax and low ceremony.
- **Readable** — code should be obvious at a glance.
- **Familiar** — borrow proven ideas from C and Python.
- **Predictable** — avoid hidden behavior and surprising syntax.
- **Compiler-friendly** — the first version should stay small enough to implement cleanly.

komiLang is **not** trying to be syntactically exotic. Its identity should come from clarity and semantics, not strange punctuation.

---

## 2. Hello, komiLang

```komi
fn main() {
    print("hello from komiLang");
}
```

---

## 3. Variables

Variables are declared using `let`.

```komi
let x = 10;
let name = "Komi";
let alive = true;
```

Type annotations are optional:

```komi
let x: int = 10;
let name: string = "Komi";
```

Variables are mutable by default in v0.1:

```komi
let x = 10;
x = 20;
```

---

## 4. Primitive Types

Initial built-in types:

```text
int
float
bool
string
void
```

Examples:

```komi
let age: int = 19;
let pi: float = 3.14;
let awake: bool = true;
let name: string = "komiLang";
```

---

## 5. Literals

### Integer

```komi
10
42
999
```

### Float

```komi
3.14
0.5
10.0
```

### Boolean

```komi
true
false
```

### String

```komi
"hello"
"komiLang"
```

---

## 6. Operators

### Arithmetic

```text
+   addition
-   subtraction
*   multiplication
/   division
%   remainder
```

Example:

```komi
let result = 10 + 20 * 3;
```

### Comparison

```text
==  equal
!=  not equal
<   less than
<=  less than or equal
>   greater than
>=  greater than or equal
```

### Logical

```text
&&  and
||  or
!   not
```

Example:

```komi
if age >= 18 && alive {
    print("allowed");
}
```

### Assignment

```text
=
```

Example:

```komi
x = x + 1;
```

---

## 7. Conditionals

komiLang uses C-style braces without requiring parentheses around conditions.

```komi
if x > 10 {
    print("large");
}
```

With `else`:

```komi
if x > 10 {
    print("large");
} else {
    print("small");
}
```

Chained conditions:

```komi
if score >= 90 {
    print("excellent");
} else if score >= 60 {
    print("good");
} else {
    print("try again");
}
```

---

## 8. Loops

### While

```komi
let i = 0;

while i < 10 {
    print(i);
    i = i + 1;
}
```

`while` is the only loop required for v0.1.

Possible future syntax:

```komi
for item in items {
    print(item);
}
```

---

## 9. Functions

Functions are declared using `fn`.

```komi
fn add(a: int, b: int) -> int {
    return a + b;
}
```

Calling a function:

```komi
let result = add(10, 20);
```

Functions with no return value:

```komi
fn greet(name: string) {
    print(name);
}
```

Equivalent explicit form:

```komi
fn greet(name: string) -> void {
    print(name);
}
```

---

## 10. Return

```komi
fn square(x: int) -> int {
    return x * x;
}
```

Bare return:

```komi
fn stop() {
    return;
}
```

---

## 11. Comments

Single-line comments use `//`.

```komi
// this is a comment

let x = 10; // comments may follow code
```

Block comments are not required for v0.1.

---

## 12. Statement Termination

komiLang v0.1 uses semicolons.

```komi
let x = 10;
x = x + 1;
print(x);
```

This keeps parsing explicit and simple.

A future version may allow optional semicolons if the grammar can remain predictable.

---

## 13. Blocks

Blocks use braces:

```komi
{
    let x = 10;
    print(x);
}
```

Braces are used for:

- functions
- conditionals
- loops
- nested scopes

---

## 14. Identifiers

Identifiers may contain:

```text
A-Z
a-z
0-9
_
```

but cannot begin with a digit.

Valid:

```text
x
hello
hello_world
value2
_private
```

Invalid:

```text
2value
```

---

## 15. Reserved Keywords

Initial keywords:

```text
let
fn
if
else
while
return
true
false

int
float
bool
string
void
```

Future keywords may include:

```text
for
break
continue
struct
import
const
```

---

## 16. Token Set — v0.1

### Literals / identifiers

```text
TOKEN_IDENTIFIER
TOKEN_INTEGER
TOKEN_FLOAT
TOKEN_STRING
```

### Keywords

```text
TOKEN_LET
TOKEN_FN
TOKEN_IF
TOKEN_ELSE
TOKEN_WHILE
TOKEN_RETURN
TOKEN_TRUE
TOKEN_FALSE

TOKEN_INT
TOKEN_FLOAT_TYPE
TOKEN_BOOL
TOKEN_STRING_TYPE
TOKEN_VOID
```

### Arithmetic

```text
TOKEN_PLUS
TOKEN_MINUS
TOKEN_STAR
TOKEN_SLASH
TOKEN_PERCENT
```

### Comparison / assignment

```text
TOKEN_EQUAL
TOKEN_EQUAL_EQUAL
TOKEN_NOT_EQUAL
TOKEN_LESS
TOKEN_LESS_EQUAL
TOKEN_GREATER
TOKEN_GREATER_EQUAL
```

### Logical

```text
TOKEN_AND
TOKEN_OR
TOKEN_NOT
```

### Punctuation

```text
TOKEN_LPAREN
TOKEN_RPAREN
TOKEN_LBRACE
TOKEN_RBRACE
TOKEN_COMMA
TOKEN_COLON
TOKEN_SEMICOLON
TOKEN_ARROW
```

### Special

```text
TOKEN_EOF
TOKEN_ERROR
```

---

## 17. Lexical Rules

### Integer

```text
integer := digit+
```

Examples:

```text
0
10
9999
```

### Float

```text
float := digit+ "." digit+
```

Examples:

```text
3.14
10.0
0.5
```

### Identifier

```text
identifier := (letter | "_") (letter | digit | "_")*
```

Examples:

```text
hello
hello_world
x1
_private
```

### String

```text
string := '"' characters* '"'
```

Example:

```komi
"hello komiLang"
```

---

## 18. Operator Precedence

typedef enum Precedence {
  PREC_NONE = 0,
  PREC_ASSIGNMENT, // =
  PREC_OR,         // ||
  PREC_AND,        // &&
  PREC_EQUALITY,   // == !=
  PREC_COMPARISON, // < <= > >=
  PREC_TERM,       // + -
  PREC_FACTOR,     // * / %
  PREC_UNARY,      // ! - (prefix)
  PREC_CALL,       // ()
  PREC_PRIMARY,
} Precedence;

prefix:
-   unary minus
!   logical not
(   grouped expression
literal
identifier

infix:
+
-
*
/
%
==
!=
<
<=
>
>=
&&
||
=
(

Highest to lowest:

```text
1.  ()
2.  !
3.  * / %
4.  + -
5.  < <= > >=
6.  == !=
7.  &&
8.  ||
9.  =
```

Example:

```komi
let x = 2 + 3 * 4;
```

is interpreted as:

```text
2 + (3 * 4)
```

---

## 19. Grammar — v0.1

This grammar is intentionally small.

```text
program
    -> declaration* EOF
```

### Declarations

```text
declaration
    -> variable_declaration
     | function_declaration
     | statement
```

### Variable Declaration

```text
variable_declaration
    -> "let" IDENTIFIER (":" type)? "=" expression ";"
```

Examples:

```komi
let x = 10;
let x: int = 10;
```

### Function Declaration

```text
function_declaration
    -> "fn" IDENTIFIER "(" parameters? ")" return_type? block

parameters
    -> parameter ("," parameter)*

parameter
    -> IDENTIFIER ":" type

return_type
    -> "->" type
```

### Statements

```text
statement
    -> expression_statement
     | if_statement
     | while_statement
     | return_statement
     | block
```

### Expression Statement

```text
expression_statement
    -> expression ";"
```

### If

```text
if_statement
    -> "if" expression block ("else" ("if" expression block | block))?
```

### While

```text
while_statement
    -> "while" expression block
```

### Return

```text
return_statement
    -> "return" expression? ";"
```

### Block

```text
block
    -> "{" declaration* "}"
```

---

## 20. Expression Grammar

```text
expression
    -> assignment

assignment
    -> IDENTIFIER "=" assignment
     | logical_or

logical_or
    -> logical_and ("||" logical_and)*

logical_and
    -> equality ("&&" equality)*

equality
    -> comparison (("==" | "!=") comparison)*

comparison
    -> term (("<" | "<=" | ">" | ">=") term)*

term
    -> factor (("+" | "-") factor)*

factor
    -> unary (("*" | "/" | "%") unary)*

unary
    -> ("!" | "-") unary
     | call

call
    -> primary ("(" arguments? ")")*

arguments
    -> expression ("," expression)*

primary
    -> INTEGER
     | FLOAT
     | STRING
     | "true"
     | "false"
     | IDENTIFIER
     | "(" expression ")"
```

---

## 21. Example Program

```komi
fn add(a: int, b: int) -> int {
    return a + b;
}

fn main() {
    let x = 10;
    let y = 20;

    let result = add(x, y);

    if result > 20 {
        print("result is large");
    } else {
        print("result is small");
    }

    let i = 0;

    while i < 5 {
        print(i);
        i = i + 1;
    }
}
```

---

## 22. v0.1 Scope

The first implementation of komiLang should support:

- source files
- identifiers
- integers
- arithmetic
- variable declarations
- assignment
- `if` / `else`
- `while`
- functions
- function calls
- return values
- basic type checking
- native executable generation

Not required for v0.1:

- arrays
- structs
- classes
- generics
- modules
- garbage collection
- macros
- inheritance
- async
- metaprogramming

Those can come later if the language earns them.

---

## 23. Philosophy

komiLang should prefer:

```text
obvious > clever
small   > bloated
explicit > magical
useful  > unique-for-the-sake-of-being-unique
```

The goal of v0.1 is not to compete with C, Python, Rust, or Go.

The goal is to build a language whose entire path from:

```text
source
  -> tokens
  -> AST
  -> semantic analysis
  -> IR
  -> assembly
  -> executable
```

can be understood end-to-end.
