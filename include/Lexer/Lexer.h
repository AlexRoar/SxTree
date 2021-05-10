
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

    class Lexer {
        string content;
        vector<Rule>   rules;
        vector<Lexeme> lexemes;
    public:
        explicit Lexer(const vector<Rule>& rulesNew);

        void parse(const string& parseContent);
    };
}

#endif //SXTREE_LEXERFILE_H
