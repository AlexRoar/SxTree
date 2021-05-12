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

namespace SxTree::Lexer {
    using std::string;
    class Lexeme {
        /**
         * Source text where this lexeme located
         */
        const string *source;

        /**
         * The type of lexeme
         */
        unsigned type;

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
        void leftConnect(const Lexeme &other, unsigned newType) noexcept;

        /**
         * Merge two lexemes by appending other lexeme
         * this + other
         * @param other
         * @param newType
         */
        void rightConnect(const Lexeme &other, unsigned newType) noexcept;

    public:
        Lexeme(const Lexeme &other);

        Lexeme(Lexeme &&other) noexcept;

        Lexeme(const string *sourceText, unsigned lexType, size_t startInd, size_t lexSize) noexcept;

        Lexeme(const Lexeme &first, const Lexeme &second, unsigned lexType) noexcept;

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
        void connect(const Lexeme &other, unsigned newType) noexcept;

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
        void setType(unsigned pString) noexcept;

        /**
         * Standard to_string function
         * @return string representation
         */
        [[nodiscard]] string to_string() const;

        [[nodiscard]] unsigned getType() const;

        [[nodiscard]] size_t getStart() const;

        [[nodiscard]] size_t getSize() const;
    };
}

#endif //SXTREE_LEXEME_H
