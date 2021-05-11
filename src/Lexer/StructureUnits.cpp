
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

        auto parsedLexeme = Lexeme(lexer.getStorage(), &tmpLexType, lexer.getPosNow(), iter->str().size());
        lexer.moveForward(iter->str().size());
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

    optional <Lexeme> Structure::Expression::exprParseOneType(LexerStructPos &lexer) const {
        auto firstLexeme = possible[0].parse(lexer);
        if (!firstLexeme.has_value())
            return optional<Lexeme>();

        Lexeme &lexeme = firstLexeme.value();
        for (auto val = ++(possible.begin()); val != possible.end(); ++val) {
            auto tryParse = val->parse(lexer);
            if (!tryParse.has_value())
                return optional<Lexeme>();
            lexeme.connect(tryParse.value(), &tmpLexType);
        }
        return optional<Lexeme>(std::move(lexeme));
    }

    optional <Lexeme> Structure::Expression::exprParseAnyType(LexerStructPos &lexer) const {
        for (const auto & val : possible) {
            auto tryParse = val.parse(lexer);
            if (tryParse.has_value()) {
//                lexer.moveForward(tryParse.value().getSize());
                return tryParse.value();
            }
        }
        return optional<Lexeme>();
    }

    optional<Lexeme> Structure::Expression::parse(LexerStructPos &lexer) const noexcept {
        assert((!possible.empty()) && "Can't have empty rules");

        switch (type) {
            case EXP_ONE:
                return exprParseOneType(lexer);
            case EXP_ANY:
                return exprParseAnyType(lexer);
            case EXP_OPTIONAL: {
                auto parsed = exprParseAnyType(lexer);
                if (parsed.has_value())
                    return parsed;
                return Lexeme::zero();
            }
        }
    }

    optional<Lexeme> Structure::Expression::parseSkipping(LexerStructPos &lexer) const noexcept {
        assert((!possible.empty()) && "Can't have empty rules");
        bool found = false;
        for (const auto &val : possible)
            found |= val.parse(lexer).has_value();
        if (!found)
            return std::optional<Lexeme>();
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