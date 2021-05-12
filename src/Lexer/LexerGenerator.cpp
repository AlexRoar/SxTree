
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
#include <string>
#include <regex>

namespace SxTree::Lexer::Generator {
    using std::string;

    static const string contents =
            #include "lexerStructTemplate.h.template"
    static const string contentsHeader =
            #include "lexerStructTemplateHeader.h.template"

    string getCompleteLexerStruct(const SxTree::LexerStruct::LexerStruct &structure) {
        string newContent = contents;
        newContent = replaceFirstOccurrence(newContent, "INSERT", structure.generateLexerStruct());
        return newContent;
    }

    string getHeader(const SxTree::LexerStruct::LexerStruct &structure) {
        string newContent = contentsHeader;
        newContent = replaceFirstOccurrence(newContent, "ENUM", structure.generateIdsEnum());
        return newContent;
    }

    std::string replaceFirstOccurrence(
            std::string& s,
            const std::string& toReplace,
            const std::string& replaceWith)
    {
        std::size_t pos = s.find(toReplace);
        if (pos == std::string::npos) return s;
        return s.replace(pos, toReplace.length(), replaceWith);
    }
}
