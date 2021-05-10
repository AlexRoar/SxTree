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

#include <cassert>
#include <string>
#include "Lexer/Lexeme.h"

namespace SxTree::LexerStruct {
    using std::string;

    Lexeme::Lexeme(const Lexeme &other) = default;

    Lexeme::Lexeme(const string *sourceText, const string *lexType, size_t startInd, size_t lexSize) noexcept:
            source(sourceText),
            type(lexType),
            start(startInd),
            size(lexSize) {
    }

    void Lexeme::connect(const Lexeme &other, const string *newType) noexcept {
        if (other.size == 0) {
            type = newType;
            return;
        }
        if (other.start < start)
            leftConnect(other, newType);
        else
            rightConnect(other, newType);
    }

    void Lexeme::leftConnect(const Lexeme &other, const string *newType) noexcept {
        assert((other.start + other.size <= start) && "Invalid lexemes placement");
        const size_t margin = start - (other.start + other.size);
        start = other.start;
        size += other.size + margin;
        type = newType;
    }

    void Lexeme::rightConnect(const Lexeme &other, const string *newType) noexcept {
        assert((other.start >= start + size) && "Invalid lexemes placement");
        const size_t margin = other.start - (size + start);
        size += other.size + margin;
        type = newType;
    }

    Lexeme::Lexeme(const Lexeme &first, const Lexeme &second, const string *lexType) noexcept:
            size(first.size),
            start(first.start),
            source(first.source),
            type(first.type) {
        connect(second, lexType);
    }

    Lexeme::Lexeme(const Lexeme &first, const Lexeme &second) noexcept:
            size(first.size),
            start(first.start),
            source(first.source),
            type(first.type) {
        assert(*first.type == *second.type);
        connect(second, second.type);
    }

    void Lexeme::operator+=(const Lexeme &other) noexcept {
        assert(*type == *other.type);
        connect(other, other.type);
    }

    Lexeme Lexeme::operator+(const Lexeme &other) const noexcept {
        assert(*type == *other.type);
        return Lexeme(*this, other);
    }

    Lexeme::Lexeme(Lexeme &&other) noexcept:
            start(other.start),
            size(other.size),
            source(other.source),
            type(other.type) {
        other.type = other.source = nullptr;
        other.start = other.size = 0;
    }

    bool Lexeme::operator==(const Lexeme &other) const noexcept {
        if (other.size == size && size == 0)
            return true;
        if (!type || !source || other.type || other.source)
            return false;
        return other.start == start && other.size == size && *type == *other.type && source == other.source;
    }

    Lexeme Lexeme::zero() {
        return Lexeme(nullptr, nullptr, 0, 0);
    }

    void Lexeme::setType(const string *pString) noexcept{
        type = pString;
    }
}