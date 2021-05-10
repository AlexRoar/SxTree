
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

#ifndef SXTREE_LEXERGENERATOR_H
#define SXTREE_LEXERGENERATOR_H

#include <string>
#include "LexerStruct.h"

namespace SxTree::Lexer::Generator {
    using std::string;

    [[maybe_unused]] string getCompleteLexerStruct(const LexerStruct::LexerStruct& structure);

    [[maybe_unused]] string getHeader();

    [[maybe_unused]] std::string replaceFirstOccurrence(
            std::string& s,
            const std::string& toReplace,
            const std::string& replaceWith);
}

#endif //SXTREE_LEXERGENERATOR_H
