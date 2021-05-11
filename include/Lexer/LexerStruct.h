
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
        vector<Structure::Rule> rules;
        vector<Structure::ParseError> errors;

    private:
        [[nodiscard]] static bool isEnded(LexerStructPos& lexerStructPos) noexcept;

        optional <Rule> pRule(LexerStructPos& lexerStructPos);

        optional <Expression> pExpression(LexerStructPos& lexerStructPos);

        optional <Value> pValue(LexerStructPos& lexerStructPos);

        void skipChars(LexerStructPos& lexerStructPos, const std::set<char> &chars);

        static char getChar(LexerStructPos& lexerStructPos) ;

        bool expectWord(LexerStructPos& lexerStructPos, const char* word);

        [[nodiscard]] string generateExpression(const Expression &exp) const;

        optional <Expression> expectClosingBracket(LexerStructPos &lexerStructPos, Expression &expr);
    public:
        LexerStruct() noexcept;

        void parseRules(const string& storage) noexcept;

        const decltype(LexerStruct::errors)& getErrors();

        [[nodiscard]] string generateLexerStruct() const noexcept;

        [[nodiscard]] const vector<Structure::Rule> &getRules() const;
    };
}


#endif //SXTREE_LEXERSTRUCT_H
