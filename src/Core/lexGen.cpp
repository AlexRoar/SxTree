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
#include <string>
#include <cxxopts.hpp>
#include "IOTools/FileRead.h"
#include "Exceptions/IOExceptions.h"
#include "Lexer/LexerStruct.h"
#include "Lexer/LexerGenerator.h"

using std::string;
using SxTree::LexerStruct::LexerStruct;
using SxTree::Lexer::Generator::getCompleteLexerStruct;
using SxTree::Lexer::Generator::getHeader;

int main(int argc, const char* const* argv){
    cxxopts::Options options("SxTree Lexer Generator", "Generate lexer file from lexer syntax");

    options.add_options()
            ("i,input" , "Input file [required]", cxxopts::value<string>())
            ("o,output", "Output file", cxxopts::value<string>()->default_value("lexer.cpp"))
            ("p,outputHeader", "Output header file", cxxopts::value<string>()->default_value("lexer.h"))
            ("q,quiet" , "Quiet mode (do not show errors)", cxxopts::value<bool>()->default_value("false"))
            ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return EXIT_SUCCESS;
    }

    string inputFile, outputFile, outputFileHeader;
    try {
        inputFile = result["input"].as<std::string>();
        outputFile = result["output"].as<std::string>();
        outputFileHeader = result["outputHeader"].as<std::string>();
    } catch (const cxxopts::option_has_no_value_exception& exception) {
        std::cout << "Required arguments are not specified\n" << options.help() << std::endl;
        return EXIT_FAILURE;
    }

    string fullFile;
    try {
        fullFile = SxTree::IO::readFullFile(inputFile.c_str());
    }catch(const SxTree::IO::OpenFileException& exception){
        std::cout << "Cannot open the file "<< inputFile << std::endl;
        return EXIT_FAILURE;
    }

    LexerStruct lexerStruct;
    lexerStruct.parseRules(fullFile);
    if (!(result["quiet"].as<bool>())) {
        printf("errors: %zu\n", lexerStruct.getErrors().size());
        for (auto error: lexerStruct.getErrors()) {
            printf("%zu:%s\n", error.position, error.msg);
        }
    }

    SxTree::IO::dumpFile(outputFile.c_str(), getCompleteLexerStruct(lexerStruct));
    SxTree::IO::dumpFile(outputFileHeader.c_str(), getHeader());

    return EXIT_SUCCESS;
}