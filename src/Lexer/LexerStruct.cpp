
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
#include <utility>
#include "Lexer/LexerStruct.h"

namespace SxTree::LexerStruct {
    const std::set skipBefore = {' ', '\n', '\t', '\r'};
    const std::set skipLine = {' ', '\t'};

    LexerStruct::LexerStruct() noexcept = default;

    void LexerStruct::parseRules(const string& storage) noexcept {
        LexerStructPos lexerStructPos(&storage);
        while (errors.empty() && !isEnded(lexerStructPos)) {
            auto rule = pRule(lexerStructPos);
            if (rule.has_value()) {
                rules.push_back(std::move(rule.value()));
            } else {
                skipChars(lexerStructPos, skipBefore);
                if (!isEnded(lexerStructPos))
                    errors.push_back({"Invalid rule", lexerStructPos.posNow});
                break;
            }
            skipChars(lexerStructPos, skipBefore);
        }
    }

    optional<Rule> LexerStruct::pRule(LexerStructPos& lexerStructPos) {
        skipChars(lexerStructPos, skipBefore);
        string id;
        char tmpChar = 0;
        while (isalpha(tmpChar = getChar(lexerStructPos)) || isdigit(tmpChar)) {
            id += tmpChar;
            lexerStructPos.moveForward(1);
        }

        skipChars(lexerStructPos, skipLine);

        if (!expectWord(lexerStructPos, "=")) {
            errors.push_back({"No '=' symbol after identifier", lexerStructPos.posNow});
            skipChars(lexerStructPos, skipBefore);
            return optional<Rule>();
        }
        skipChars(lexerStructPos, skipLine);
        auto expr = pExpression(lexerStructPos);
        if (!expr.has_value()) {
            errors.push_back({"Invalid expression after <id> = ", lexerStructPos.posNow});
            skipChars(lexerStructPos, skipBefore);
            return optional<Rule>();
        }
        skipChars(lexerStructPos, skipLine);

        if (!expectWord(lexerStructPos, "\n")) {
            errors.push_back({"No new line after definition", lexerStructPos.posNow});
            skipChars(lexerStructPos, skipBefore);
            return optional<Rule>();
        }

        return optional<Rule>({getRuleId(id), expr.value()});
    }

    optional<Expression> LexerStruct::pExpression(LexerStructPos& lexerStructPos) {
        skipChars(lexerStructPos, skipLine);
        Expression::ExprType type = Structure::Expression::EXP_ONE;
        if (!expectWord(lexerStructPos, "(")) {
            if (!expectWord(lexerStructPos, "[")) {
                if (!expectWord(lexerStructPos, "?[")) {
                    errors.push_back({"Expected left parenthesis before expression", lexerStructPos.posNow});
                    skipChars(lexerStructPos, skipBefore);
                    return optional<Expression>();
                } else
                    type = Structure::Expression::EXP_OPTIONAL;
            } else
                type = Structure::Expression::EXP_ANY;
        }
        skipChars(lexerStructPos, skipLine);
        auto firstExpr = pValue(lexerStructPos);
        if (!firstExpr.has_value()) {
            errors.push_back({"At least one rule required in the expression", lexerStructPos.posNow});
            return optional<Expression>();
        }
        Expression expr;
        expr.type = type;
        expr.possible.push_back(std::move(firstExpr.value()));

        while (true) {
            skipChars(lexerStructPos, skipLine);
            if (expectWord(lexerStructPos, ",")) {
                skipChars(lexerStructPos, skipLine);
                auto nextExpr = pValue(lexerStructPos);
                if (!nextExpr.has_value()) {
                    errors.push_back({"Expected a comma before declarations", lexerStructPos.posNow});
                    skipChars(lexerStructPos, skipBefore);
                    return optional<Expression>();
                }
                expr.possible.push_back(std::move(nextExpr.value()));
            } else
                break;
        }

        return expectClosingBracket(lexerStructPos, expr);
    }

    optional <Expression> LexerStruct::expectClosingBracket(LexerStructPos &lexerStructPos, Expression &expr) {
        switch (expr.type) {
            case Expression::EXP_ONE: {
                if (!expectWord(lexerStructPos, ")")) {
                    errors.push_back({"Expected ')' after expression", lexerStructPos.posNow});
                    skipChars(lexerStructPos, skipBefore);
                    return std::__1::optional<Expression>();
                }
                break;
            }
            case Expression::EXP_ANY: {
                if (!expectWord(lexerStructPos, "]")) {
                    errors.push_back({"Expected ']' after expression", lexerStructPos.posNow});
                    skipChars(lexerStructPos, skipBefore);
                    return std::__1::optional<Expression>();
                }
                break;
            }
            case Expression::EXP_OPTIONAL: {
                if (!expectWord(lexerStructPos, "]")) {
                    errors.push_back({"Expected ']' after ?[ expression", lexerStructPos.posNow});
                    skipChars(lexerStructPos, skipBefore);
                    return std::__1::optional<Expression>();
                }
                break;
            }
        }
        return std::__1::optional<Expression>(std::move(expr));
    }

    optional<Value> LexerStruct::pValue(LexerStructPos &lexerStructPos) {
        auto getExpr = [=](LexerStructPos &lexerStructPos, const char *errMsg, bool skip=false) -> optional<Value> {
            auto expr = pExpression(lexerStructPos);
            if (!expr.has_value()) {
                errors.push_back({errMsg, lexerStructPos.posNow});
                return optional<Value>();
            }
            return Value(expr.value(), skip);
        };

        skipChars(lexerStructPos, skipLine);
        if (expectWord(lexerStructPos, "skip"))
            return getExpr(lexerStructPos, "Expected expression directly after 'skip' keyword", true);

        std::regex rgx(R"((["'])(?:(?=(\\?))\2.)*?\1)");
        std::sregex_iterator current(lexerStructPos.begin(), lexerStructPos.end(), rgx);
        std::sregex_iterator end;
//        printf("%s\n", current->str().c_str());
        if (current == end || current->position() != 0)
            return getExpr(lexerStructPos, "Malformed rule");
        if (current->str().size() <= 2) {
            errors.push_back({"RegExpr can't be empty", lexerStructPos.posNow});
            return optional<Value>();
        }
        string stringReg = current->str();/*std::regex_replace(current->str(), std::regex(R"(\\")"), "\"");*/
        stringReg = stringReg.substr(1, current->str().size() - 2);
        lexerStructPos.moveForward(current->str().size());
        try {
            return Value(stringReg);
        } catch (const std::regex_error &e) {
            errors.push_back({"Wrong regular expression detected", lexerStructPos.posNow});
            errors.push_back({e.what(), lexerStructPos.posNow});
            return optional<Value>();
        }
    }

    bool LexerStruct::isEnded(LexerStructPos &lexerStructPos) noexcept {
        return lexerStructPos.isEnded();
    }

    void LexerStruct::skipChars(LexerStructPos &lexerStructPos, const std::set<char> &chars) {
        while (!isEnded(lexerStructPos)) {
            if (chars.find(getChar(lexerStructPos)) != chars.end())
                lexerStructPos.moveForward(1);
            else
                break;
        }
    }

    char LexerStruct::getChar(LexerStructPos &lexerStructPos) {
        return (*lexerStructPos.storage)[lexerStructPos.posNow];
    }

    bool LexerStruct::expectWord(LexerStructPos &lexerStructPos, const char *word) {
        assert(word && "Cannot expect nullptr string");
        unsigned i = 0;
        while (*word) {
            if (getChar(lexerStructPos) != *word) {
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

    string LexerStruct::generateLexerStruct() const noexcept {
        string output = "{\n";
        for (const auto &rule: rules)
            output += "\t{" + std::to_string(rule.id + 1) + ", " + generateExpression(rule.expression) + "},\n";

        output += "}";
        return output;
    }

    string LexerStruct::generateIdsEnum() const noexcept {
        string output = "{\n";

        vector<const string*> orderedIds(ruleIdsNo.size() + 1, nullptr);

        string none = "NONE";
        orderedIds[0] = &none;
        for(const auto& id: ruleIdsNo)
            orderedIds[id.second + 1] = &id.first;

        for(unsigned i = 0; i < orderedIds.size(); i++)
            output += "\tlex_" + *(orderedIds[i]) + " = " + std::to_string(i) + ",\n";

        output += "}";
        return output;
    }

    static string valTypeString(Value::ValueType type) {
        switch (type) {
            case Value::VAL_EXPRESSION:
                return "Value::VAL_EXPRESSION";
            case Value::VAL_REGEXP:
                return "Value::VAL_REGEXP";
            case Value::VAL_SKIP:
                return "Value::VAL_SKIP";
        }
    }

    static string exprTypeString(Expression::ExprType type) {
        switch (type) {
            case Expression::EXP_ONE:
                return "Expression::EXP_ONE";
            case Expression::EXP_ANY:
                return "Expression::EXP_ANY";
            case Expression::EXP_OPTIONAL:
                return "Expression::EXP_OPTIONAL";
        }
    }

    string LexerStruct::generateExpression(const Expression &exp) const {
        string output = "{{";
        for (const auto &val: exp.possible) {
            output += "{ R\"(" + val.regexString + ")\", " + valTypeString(val.type) + "," +
                    generateExpression(val.expr) + "},";
        }
        output += "}, " + exprTypeString(exp.type) + "}";
        return output;
    }

    const vector<Structure::Rule> &LexerStruct::getRules() const {
        return rules;
    }

    unsigned LexerStruct::getRuleId(const string& id) {
        const auto found = ruleIdsNo.find(id);
        if (found == ruleIdsNo.end()) {
            ruleIdsNo[id] = ruleIdsNo.size();
            return ruleIdsNo.size() - 1;
        }
        return found->second;
    }
}