# SxTree

Generate AST syntax parser from grammar files. Implements:

- Lexer generator
- Parser generator

## Lexer generator

Generates lexer basing on syntax file. Example:

```yaml
space       = (skip("\s"))
lineBreak   = ["[\n]+"]
integer     = ("^[-+]?[0-9]\d*")
float       = ("^[+-]?([0-9]*[.])?[0-9]+")

def         = ("def")
```

Lexer syntax grammar:
```bash
G       := [Rule]*
ID      := regex(^[a-zA-Z_$][a-zA-Z_$0-9]*)
Rule    := ID '=' Exp '\n'
Exp     := '('P [, P]*')' | '['P [, P]*']' | '?['P [, P]*']'
P(part) := skip+Exp | regex | Exp
```

Several main types of rules are used:
- `'('P [, P]*')'`  – sequence of parts, all parts must be met one by one.
- `'['P [, P]*']'`  – any of listed parts.
- `'?['P [, P]*']'` – any of listed parts or none.
- `skip+Exp`        - get expression and skip it.

Tokens parsed from top to bottom – upper statements have higher priority.

### Lexer generator usage

Generator takes lexer syntax file and generates a file used by SxTree parser further.
```bash
> sxlgen -h
Generate lexer file from lexer syntax
Usage:
  SxTree Lexer Generator [OPTION...]

  -i, --input arg         Input file [required]
  -o, --output arg        Output file (default: lexer.cpp)
  -p, --outputHeader arg  Output header file (default: lexer.h)
  -q, --quiet             Quiet mode (do not show errors)
  -h, --help              Print usage
```

### Example:

```bash
space       = (skip("\s"))
var         = ("var")
funcDecl    = ["def", "define"]
ok          = ("o", ?["k"])
```

```cpp
enum LexemeType {
    lex_NONE = 0,
    lex_space = 1,
    lex_var = 2,
    lex_funcDecl = 3,
    lex_ok = 4,
};

Lexer coreLexer({
    {1, {{{ R"()", Value::VAL_SKIP,{{{ R"(\s)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
    {2, {{{ R"(var)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
    {3, {{{ R"(def)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"(define)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ANY}},
    {4, {{{ R"(o)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"()", Value::VAL_EXPRESSION,{{{ R"(k)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_OPTIONAL}},}, Expression::EXP_ONE}},
});
```

Here's an example that can be found in `/examples/simple`. It is extremely easy to adjust lexer for your needs.

```python
def someFunction() {
    "Hello world"
}
```

```bash
Lexeme<def[0-3]> Lexeme<identifier[4-16]> Lexeme<leftPa[16-17]>
Lexeme<rightPa[17-18]> Lexeme<leftBlock[19-20]> Lexeme<lineBreak[20-21]>
Lexeme<margin[21-25]> Lexeme<margin[25-29]> Lexeme<string[29-42]>
Lexeme<lineBreak[42-43]> Lexeme<rightBlock[43-44]>
```

## Parser

In progress