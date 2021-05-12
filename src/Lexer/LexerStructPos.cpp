
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

#include <cstdlib>
#include <string>
#include "Lexer/LexerStructPos.h"

namespace SxTree::LexerStruct::Structure {
    using std::string;

    decltype(LexerStructPos::storage->end()) LexerStructPos::end() const {
        return storage->end();
    }

    decltype(LexerStructPos::storage->begin()) LexerStructPos::begin() const {
        return storage->begin() + (long long) posNow;
    }

    size_t LexerStructPos::getPosNow() const {
        return posNow;
    }

    const string *LexerStructPos::getStorage() const {
        return storage;
    }

    void LexerStructPos::moveForward(unsigned long dist) {
        posNow += dist;
    }

    bool LexerStructPos::isEnded() const {
        return posNow >= storage->size();
    }

    void LexerStructPos::moveBack(unsigned long dist) {
        posNow -= dist;
    }

    LexerStructPos::LexerStructPos(const string *s): posNow(0), storage(s) {}
}