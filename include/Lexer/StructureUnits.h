
/*
 * =================================================
 * Copyright © 2021
 * Aleksandr Dremov
 *
 * This code has been written by Aleksandr Dremov
 * Check license agreement of this project to evade
 * possible illegal use.
 * =================================================
 */

#ifndef SXTREE_STRUCTUREUNITS_H
#define SXTREE_STRUCTUREUNITS_H

#include <string>
#include <vector>
#include <regex>
#include <optional>
#include <set>
#include "Lexer/Lexeme.h"
#include "Lexer/LexerStructPos.h"

namespace SxTree::LexerStruct::Structure {
    using std::string;
    using std::vector;
    using std::regex;
    using std::optional;
    using SxTree::LexerStruct::Structure::LexerStructPos;

    struct ParseError {
        const char* msg;
        size_t position;
    };

    struct Value;

    struct Expression {
        enum ExprType {
            EXP_ONE,
            EXP_ANY,
            EXP_OPTIONAL
        };
        vector<Value> possible;
        ExprType type;

        optional<Lexeme> parse(LexerStructPos& lexer) const noexcept;
        optional<Lexeme> parseSkipping(LexerStructPos& lexer) const noexcept;
    };

    struct Value{
        enum ValueType{
            VAL_EXPRESSION,
            VAL_REGEXP,
            VAL_SKIP
        };
        regex strRegex;
        ValueType type;
        Expression expr;

        explicit Value(regex  reg);

        explicit Value(Expression  e, bool skip=false);

        optional<Lexeme> parse(LexerStructPos& lexer) const noexcept;
    private:
        optional<Lexeme> parseRegexp(LexerStructPos& lexer) const noexcept;
    };

    struct Rule {

        string id;
        Expression expression;

        optional<Lexeme> parse(LexerStructPos& lexer) const noexcept;
    };
}

#endif //SXTREE_STRUCTUREUNITS_H
