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
```yaml
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