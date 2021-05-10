
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

    const string contents =
            #include "lexerStructTemplate.h.template"

    string getCompleteLexerStruct(const SxTree::LexerStruct::LexerStruct &structure) {
        return std::regex_replace(contents, std::regex(R"(INSERT)"), structure.generateLexerStruct());
    }
}
