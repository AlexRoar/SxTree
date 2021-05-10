
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

#ifndef SXTREE_LEXERSTRUCT_H
#define SXTREE_LEXERSTRUCT_H

#include <cstdlib>
#include <string>
#include <vector>
#include "Lexer/StructureUnits.h"
#include "Lexer/LexerStructPos.h"

namespace SxTree::LexerStruct {
    using std::string;
    using std::vector;
    using namespace Structure;

    class LexerStruct {
        const string* storage;
        LexerStructPos lexerStructPos;
        vector<Structure::Rule> rules;
        vector<Structure::ParseError> errors;

        void skipWhitespaces() noexcept;

        [[nodiscard]] bool isEnded() const noexcept;

        optional <Rule> pRule();

        optional <Expression> pExpression();

        optional <Value> pValue();

        void skipChar(char c);

        void skipChars(const std::set<char> &chars);

        char getChar() const;

        bool expectWord(const char* word);
    public:
        explicit LexerStruct(const string* structStorage) noexcept;

        void parseRules() noexcept;

        const decltype(LexerStruct::errors)& getErrors();
    };
}


#endif //SXTREE_LEXERSTRUCT_H
