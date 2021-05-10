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

#ifndef SXTREE_LEXEME_H
#define SXTREE_LEXEME_H

#include <cstdlib>
#include <string>

namespace SxTree::LexerStruct {
    using std::string;
    class Lexeme {
        /**
         * Source text where this lexeme located
         */
        const string *source;

        /**
         * The type of lexeme
         */
        const string *type;

        /**
         * Start position of lexeme in the source
         */
        size_t start;

        /**
         * Size of lexeme in the source
         */
        size_t size;

        /**
         * Merge two lexemes by appending other lexeme
         * other + this
         * @param other
         * @param newType
         */
        void leftConnect(const Lexeme &other, const string *newType) noexcept;

        /**
         * Merge two lexemes by appending other lexeme
         * this + other
         * @param other
         * @param newType
         */
        void rightConnect(const Lexeme &other, const string *newType) noexcept;

    public:
        Lexeme(const Lexeme &other);

        Lexeme(Lexeme &&other) noexcept;

        Lexeme(const string *sourceText, const string *lexType, size_t startInd, size_t lexSize) noexcept;

        Lexeme(const Lexeme &first, const Lexeme &second, const string *lexType) noexcept;

        static Lexeme zero();

        /**
         * @warning Lexemes must have the same type
         * @param first
         * @param second
         */
        Lexeme(const Lexeme &first, const Lexeme &second) noexcept;

        /**
         * Connects the lexeme to the current one
         * @param other
         * @param newType
         */
        void connect(const Lexeme &other, const string *newType) noexcept;

        /**
         * Connects the lexeme to the current one
         * @warning Lexemes must have the same type
         * @param other
         */
        void operator+=(const Lexeme &other) noexcept;

        /**
         * Connects lexemes
         * @warning Lexemes must have the same type
         * @param other
         */
        Lexeme operator+(const Lexeme &other) const noexcept;

        /**
         * @warning Sources are compared by the pointers, not values
         * @param other
         * @return
         */
        bool operator==(const Lexeme &other) const noexcept;

        /**
         * Update lexeme type
         * @param pString
         */
        void setType(const string *pString) noexcept;
    };
}

#endif //SXTREE_LEXEME_H
