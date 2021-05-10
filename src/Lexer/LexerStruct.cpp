
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

#include <set>
#include <cctype>
#include <cassert>
#include "Lexer/LexerStruct.h"

namespace SxTree::LexerStruct {
    const std::set skipBefore = {' ', '\n', '\t', '\r'};
    const std::set skipLine = {' ', '\t'};

    LexerStruct::LexerStruct(const string *structStorage) noexcept:
            storage(structStorage),
            rules(),
            lexerStructPos(structStorage) {

    }

    void LexerStruct::parseRules() noexcept {
        while (errors.empty() && !isEnded()) {
            auto rule = pRule();
            if (rule.has_value()) {
                rules.push_back(std::move(rule.value()));
            } else {
                skipChars(skipBefore);
                if (!isEnded())
                    errors.push_back({"Invalid rule", lexerStructPos.posNow});
                break;
            }
            skipChars(skipBefore);
        }
    }

    optional<Rule> LexerStruct::pRule() {
        skipChars(skipBefore);
        string id;
        char tmpChar = 0;
        while (isalpha(tmpChar = getChar()) || isdigit(tmpChar)) {
            id += tmpChar;
            lexerStructPos.moveForward(1);
        }

        skipChars(skipLine);

        if (!expectWord("=")) {
            errors.push_back({"No '=' symbol after identifier", lexerStructPos.posNow});
            skipChars(skipBefore);
            return optional<Rule>();
        }
        skipChars(skipLine);
        auto expr = pExpression();
        if (!expr.has_value()) {
            errors.push_back({"Invalid expression after <id> = ", lexerStructPos.posNow});
            skipChars(skipBefore);
            return optional<Rule>();
        }
        skipChars(skipLine);

        if (!expectWord("\n")) {
            errors.push_back({"No new line after definition", lexerStructPos.posNow});
            skipChars(skipBefore);
            return optional<Rule>();
        }

        return optional<Rule>({id, expr.value()});
    }

    optional<Expression> LexerStruct::pExpression() {
        skipChars(skipLine);
        Expression::ExprType type = Structure::Expression::EXP_ONE;
        if (!expectWord("(")) {
            if (!expectWord("[")) {
                if (!expectWord("?[")) {
                    errors.push_back({"Expected left parenthesis before expression", lexerStructPos.posNow});
                    skipChars(skipBefore);
                    return optional<Expression>();
                } else
                    type = Structure::Expression::EXP_OPTIONAL;
            } else
                type = Structure::Expression::EXP_ANY;
        }
        skipChars(skipLine);
        auto firstExpr = pValue();
        if (!firstExpr.has_value()) {
            errors.push_back({"At least one rule required in the expression", lexerStructPos.posNow});
            return optional<Expression>();
        }
        Expression expr;
        expr.type = type;
        expr.possible.push_back(std::move(firstExpr.value()));

        while (true) {
            skipChars(skipLine);
            if (expectWord(",")) {
                skipChars(skipLine);
                auto nextExpr = pValue();
                if (!nextExpr.has_value()) {
                    errors.push_back({"Expected a comma before declarations", lexerStructPos.posNow});
                    skipChars(skipBefore);
                    return optional<Expression>();
                }
                expr.possible.push_back(std::move(nextExpr.value()));
            } else
                break;
        }

        switch (expr.type){
            case Expression::EXP_ONE: {
                if (!expectWord(")")) {
                    errors.push_back({"Expected ')' after expression", lexerStructPos.posNow});
                    skipChars(skipBefore);
                    return optional<Expression>();
                }
                break;
            }
            case Expression::EXP_ANY: {
                if (!expectWord("]")) {
                    errors.push_back({"Expected ']' after expression", lexerStructPos.posNow});
                    skipChars(skipBefore);
                    return optional<Expression>();
                }
                break;
            }
            case Expression::EXP_OPTIONAL: {
                if (!expectWord("]")) {
                    errors.push_back({"Expected ']' after ?[ expression", lexerStructPos.posNow});
                    skipChars(skipBefore);
                    return optional<Expression>();
                }
                break;
            }
        }
        return optional<Expression>(std::move(expr));
    }

    optional<Value> LexerStruct::pValue() {
        skipChars(skipLine);
        auto getExpr = [=](const char *errMsg) -> optional<Value> {
            auto expr = pExpression();
            if (!expr.has_value()) {
                errors.push_back({errMsg, lexerStructPos.posNow});
                return optional<Value>();
            }
            return Value(expr.value(), true);
        };

        if (expectWord("skip"))
            return getExpr("Expected expression directly after 'skip' keyword");

        std::regex rgx("([\"'])(?:(?=(\\\\?))\\2.)*?\\1");
        std::sregex_iterator current(lexerStructPos.begin(), lexerStructPos.end(), rgx);
        std::sregex_iterator end;
//        printf("%s\n", current->str().c_str());
        if (current == end || current->position() != 0)
            return getExpr("Malformed rule");
        if (current->str().size() <= 2) {
            errors.push_back({"RegExpr can't be empty", lexerStructPos.posNow});
            return optional<Value>();
        }
        string stringReg = std::regex_replace(current->str(), std::regex(R"(\\")"), "\"");
        stringReg = stringReg.substr(1, current->str().size() - 2);
        lexerStructPos.moveForward(current->str().size());
        try {
            return Value(regex(stringReg));
        } catch (std::regex_error e) {
            errors.push_back({e.what(), lexerStructPos.posNow});
            return optional<Value>();
        }
    }

    bool LexerStruct::isEnded() const noexcept {
        return lexerStructPos.isEnded();
    }

    void LexerStruct::skipWhitespaces() noexcept {
        skipChar(' ');
    }

    void LexerStruct::skipChar(char c) {
        while (!isEnded()) {
            if (getChar() == c)
                lexerStructPos.moveForward(1);
            else
                break;
        }
    }

    void LexerStruct::skipChars(const std::set<char> &chars) {
        while (!isEnded()) {
            if (chars.find(getChar()) != chars.end())
                lexerStructPos.moveForward(1);
            else
                break;
        }
    }

    char LexerStruct::getChar() const {
        return (*lexerStructPos.storage)[lexerStructPos.posNow];
    }

    bool LexerStruct::expectWord(const char *word) {
        assert(word && "Cannot expect nullptr string");
        unsigned i = 0;
        while (*word) {
            if (getChar() != *word) {
                lexerStructPos.moveBack(i);
                return false;
            }
            word++;
            i++;
            lexerStructPos.moveForward(1);
        }
        return true;
    }

    const decltype(LexerStruct::errors) &LexerStruct::getErrors() {
        return errors;
    }
}