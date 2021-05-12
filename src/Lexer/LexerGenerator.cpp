
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

#include "Lexer/LexerGenerator.h"
#include "Lexer/StructureUnits.h"
#include <string>
#include <regex>
#include <vector>


namespace SxTree::Lexer::Generator {
    using std::string;
    using std::vector;
    using LexerStruct::Expression;
    using LexerStruct::Value;

    static const string contents =

#include "templates/lexerStructTemplate.h.template"
static const string contentsHeader =
#include "templates/lexerStructTemplateHeader.h.template"

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

    static string generateExpression(const Expression &exp) {
        string output = "{{";
        for (const auto &val: exp.possible) {
            output += "{ R\"(" + val.regexString + ")\", " + valTypeString(val.type) + "," +
                      generateExpression(val.expr) + "},";
        }
        output += "}, " + exprTypeString(exp.type) + "}";
        return output;
    }

    static string generateLexemesToStringBody(const SxTree::LexerStruct::LexerStruct &structure) {
        string output;
        for (auto &lex: structure.getLexemesMap())
            output += "case SxTree::Lexer::LexemeType::lex_" + lex.first + ": return \"" + lex.first + "\";\n";
        return output;
    }

    static string generateLexerStruct(const SxTree::LexerStruct::LexerStruct &structure) {
        string output = "{\n";
        for (const auto &rule: structure.getRules())
            output += "\t{" + std::to_string(rule.id + 1) + ", " + generateExpression(rule.expression) + "},\n";

        output += "}";
        return output;
    }

    static string generateIdsEnum(const SxTree::LexerStruct::LexerStruct &structure) {
        string output = "{\n";
        const auto &ruleIdsNo = structure.getLexemesMap();

        vector<const string *> orderedIds(ruleIdsNo.size() + 1, nullptr);

        string none = "NONE";
        orderedIds[0] = &none;
        for (const auto &id: ruleIdsNo)
            orderedIds[id.second + 1] = &id.first;

        for (unsigned i = 0; i < orderedIds.size(); i++)
            output += "\tlex_" + *(orderedIds[i]) + " = " + std::to_string(i) + ",\n";

        output += "}";
        return output;
    }

    string getCompleteLexerStruct(const SxTree::LexerStruct::LexerStruct &structure) {
        string newContent = contents;
        newContent = replaceFirstOccurrence(newContent, "INSERT", generateLexerStruct(structure));
        newContent = replaceFirstOccurrence(newContent, "SWITCHBODY", generateLexemesToStringBody(structure));
        newContent = replaceFirstOccurrence(newContent, "LEXNUM", std::to_string(structure.getLexemesMap().size()));
        return newContent;
    }

    string getHeader(const SxTree::LexerStruct::LexerStruct &structure) {
        string newContent = contentsHeader;
        newContent = replaceFirstOccurrence(newContent, "ENUM", generateIdsEnum(structure));
        return newContent;
    }

    std::string replaceFirstOccurrence(
            std::string &s,
            const std::string &toReplace,
            const std::string &replaceWith) {
        std::size_t pos = s.find(toReplace);
        if (pos == std::string::npos) return s;
        return s.replace(pos, toReplace.length(), replaceWith);
    }
}
