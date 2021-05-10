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

int main() {
    SxTree::Lexer::Lexer lexer = SxTree::Lexer::coreLexer;

    string code = SxTree::IO::readFullFile("code.txt");
    lexer.parse(code);

    for(const auto& lex: lexer.getLexemes()){
        printf("%s ", lex.to_string().c_str());
    }
}

