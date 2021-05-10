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
Generate lexer file from lexer syntax
Usage:
  SxTree Lexer Generator [OPTION...]

  -i, --input arg   Input file [required]
  -o, --output arg  Output file (default: lexer.cpp)
  -q, --quiet       Quiet mode (do not show errors)
  -h, --help        Print usage
```

### Example:

```bash
space       = (skip("\s"))
var         = ("var")
funcDecl    = ["def", "define"]
ok          = ("o", ?["k"])
```

```cpp
const Lexer coreLexer({
    {R"(space)" , {{{ R"()", Value::VAL_SKIP,{{{ R"(\s)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
    {R"(var)" , {{{ R"(var)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
    {R"(funcDecl)" , {{{ R"(def)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"(define)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ANY}},
    {R"(ok)" , {{{ R"(o)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"()", Value::VAL_EXPRESSION,{{{ R"(k)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_OPTIONAL}},}, Expression::EXP_ONE}},
    });
```