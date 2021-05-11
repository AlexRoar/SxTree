
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

#ifndef SXTREE_LEXERFILE_H
#define SXTREE_LEXERFILE_H

#include <vector>
#include "Lexer/Lexeme.h"
#include "Lexer/LexerStruct.h"
#include "Lexer/StructureUnits.h"

namespace SxTree::Lexer {
    using std::vector;
    using namespace SxTree::LexerStruct::Structure;

    struct LexerError {
        const char* msg;
        size_t position;
    };

    class Lexer {
        string content;
        LexerStructPos lexPos;
        vector<Rule>   rules;
        vector<LexerError> errors;

        void addError(const char* msg);

    public:
        explicit Lexer(const vector<Rule>& rulesNew);

        vector<Lexeme> parse(const string& parseContent);

        [[nodiscard]] const vector<LexerError> &getErrors() const;
    };
}

#endif //SXTREE_LEXERFILE_H
