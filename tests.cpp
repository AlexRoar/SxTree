/*
 * =================================================
 * Copyright © 2021.
 * Aleksandr Dremov.
 *
 * This code has been written by Aleksandr Dremov
 * Check license agreement of this project to evade
 * possible illegal use.
 * =================================================
 */
#include <iostream>
#include <string>
#include "IOTools/FileRead.h"
#include "Lexer/LexerStruct.h"

using SxTree::LexerStruct::LexerStruct;

int main(){
    const std::string fullFile = SxTree::IO::readFullFile("input.txt");
    LexerStruct lexerStruct(&fullFile);
    lexerStruct.parseRules();
    printf("errors: %zu\n", lexerStruct.getErrors().size());
    for (auto error: lexerStruct.getErrors()){
        printf("%zu:%s\n", error.position, error.msg);
    }

    return 0;
}