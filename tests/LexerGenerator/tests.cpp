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

#include <gtest/gtest.h>
#include <string>
#include "IOTools/FileRead.h"
#include "Exceptions/IOExceptions.h"
#include "Lexer/LexerStruct.h"
#include "Lexer/Lexer.h"
#include "Lexer/LexerGenerator.h"

using std::string;
using SxTree::LexerStruct::LexerStruct;
using SxTree::Lexer::Generator::getCompleteLexerStruct;
using SxTree::Lexer::Generator::getHeader;
using SxTree::Lexer::Lexer;

LexerStruct getLexer(const string& inputFile){
    string fullFile;
    EXPECT_NO_THROW({
                        fullFile = SxTree::IO::readFullFile(inputFile.c_str());
                    });
    LexerStruct lexerStruct;
    lexerStruct.parseRules(fullFile);
    return lexerStruct;
}

TEST(LexerGenerator, generalInit) {
    auto lexerGen = getLexer("../tests/LexerGenerator/cumulativeTest.txt");
    EXPECT_EQ(lexerGen.getErrors().size(), 0);
    EXPECT_NE(lexerGen.generateLexerStruct().size(), 0);
    EXPECT_EQ(lexerGen.getRules().size(), 4);

    Lexer lexer(lexerGen.getRules());

    auto lexemes = lexer.parse("t      ssss ss s s s s any not any or not");
    EXPECT_EQ(lexer.getErrors().size(), 0);
    string result;
    string expected = "Lexeme<margin[0-1]>"
                      "Lexeme<margin[7-11]>"
                      "Lexeme<margin[12-14]>"
                      "Lexeme<wordAnyOrNot[23-30]>"
                      "Lexeme<wordAnyOrNot[31-41]>";
    for(const auto& lex: lexemes){
        result += lex.to_string();
    }
    EXPECT_EQ(result, expected);
}