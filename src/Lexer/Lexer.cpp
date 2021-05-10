
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

#include "Lexer/Lexer.h"

namespace SxTree::Lexer {
    Lexer::Lexer(const vector<Rule> &rulesNew) :
            rules(rulesNew),
            lexemes() {}

    void Lexer::parse(const string& parseContent) {
        content = parseContent;
    }
}