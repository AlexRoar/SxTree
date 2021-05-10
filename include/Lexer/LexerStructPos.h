
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

#ifndef SXTREE_LEXERSTRUCTPOS_H
#define SXTREE_LEXERSTRUCTPOS_H


#include <string>

namespace SxTree::LexerStruct::Structure {
    using std::string;

    struct LexerStructPos {
        size_t posNow;
        const string* storage;
    public:
        explicit LexerStructPos(const string* s);

        [[nodiscard]] decltype(LexerStructPos::storage->end()) end() const;

        [[nodiscard]] decltype(LexerStructPos::storage->begin()) begin() const;

        [[nodiscard]] size_t getPosNow() const;

        [[nodiscard]] const string *getStorage() const;

        void moveForward(unsigned long dist);

        void moveBack(unsigned long dist);

        [[nodiscard]] bool isEnded() const;
    };
}

#endif //SXTREE_LEXERSTRUCTPOS_H
