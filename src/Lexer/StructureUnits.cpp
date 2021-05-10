
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

#include <cassert>
#include <utility>
#include <vector>
#include <regex>
#include <optional>
#include "Lexer/Lexeme.h"
#include "Lexer/StructureUnits.h"

namespace SxTree::LexerStruct {
    using namespace SxTree::LexerStruct::Structure;
    using std::string;
    using std::vector;
    using std::regex;
    using std::optional;
    using SxTree::Lexer::Lexeme;

    const string tmpLexType("TMP");

    optional<Lexeme> Structure::Value::parse(LexerStructPos &lexer) const noexcept {
        switch (type) {
            case VAL_EXPRESSION:
                return expr.parse(lexer);
            case VAL_REGEXP:
                return parseRegexp(lexer);
            case VAL_SKIP:
                return expr.parseSkipping(lexer);
        }
        assert(false && "This code must not be reached");
    }

    optional<Lexeme> Structure::Value::parseRegexp(LexerStructPos &lexer) const noexcept {
        std::sregex_iterator iter(lexer.begin(), lexer.end(), strRegex);
        std::sregex_iterator end;

        if (iter == end || iter->position() != 0)
            return std::optional<Lexeme>();

        auto parsedLexeme = Lexeme(lexer.getStorage(), &tmpLexType, lexer.getPosNow(), iter->size());
        lexer.moveForward(iter->size());
        return parsedLexeme;
    }

    Value::Value(const string &regex) : strRegex(regex), type(VAL_REGEXP), regexString(regex) {

    }

    Value::Value(Expression e, bool skip) : expr(std::move(e)), type(skip ? VAL_SKIP : VAL_EXPRESSION) {

    }

    Value::Value(const string &&regexStringNew,
                 Value::ValueType typeNew,
                 const Expression &&exprNew) :
            strRegex(regexStringNew),
            regexString(regexStringNew),
            type(typeNew),
            expr(exprNew) {
    }

    optional<Lexeme> Structure::Expression::parse(LexerStructPos &lexer) const noexcept {
        assert((!possible.empty()) && "Can't have empty rules");
        auto firstLexeme = possible[0].parse(lexer);
        if (!firstLexeme.has_value())
            return std::optional<Lexeme>();

        Lexeme &lexeme = firstLexeme.value();
        for (auto val = ++(possible.begin()); val != possible.end(); ++val) {
            auto tryParse = val->parse(lexer);
            if (!tryParse.has_value())
                return std::optional<Lexeme>();
            lexeme.connect(tryParse.value(), &tmpLexType);
        }

        return std::optional<Lexeme>(std::move(lexeme));
    }

    optional<Lexeme> Structure::Expression::parseSkipping(LexerStructPos &lexer) const noexcept {
        assert((!possible.empty()) && "Can't have empty rules");
        for (const auto &val : possible)
            val.parse(lexer);
        return std::optional<Lexeme>(Lexeme::zero());
    }

    Expression::Expression(): type(EXP_ONE), possible(){

    }

    Expression::Expression(std::vector<Value>  possibleNew, ExprType typeNew):possible(std::move(possibleNew)), type(typeNew) {

    }

    optional<Lexeme> Structure::Rule::parse(LexerStructPos &lexer) const noexcept {
        auto tryParse = expression.parse(lexer);
        if (!tryParse.has_value())
            return tryParse;
        tryParse.value().setType(&id);
        return tryParse;
    }
}