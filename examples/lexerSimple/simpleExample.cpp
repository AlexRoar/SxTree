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

#include <string>
#include "lexer.h"
#include "Lexer/Lexer.h"
#include "IOTools/FileRead.h"

using std::string;
using SxTree::Lexer::Lexer;

int main() {
    Lexer lexer = SxTree::Lexer::coreLexer;

    string code = SxTree::IO::readFullFile("code.txt");
    auto lexemes = lexer.parse(code);

    for(const auto& err: lexer.getErrors())
        printf("%zu:%s\n", err.position, err.msg);

    for(const auto& lex: lexemes)
        printf("%s('%s')\n", lex.to_stringTypeDereference(SxTree::Lexer::to_string).c_str(), lex.valueString().c_str());
}

