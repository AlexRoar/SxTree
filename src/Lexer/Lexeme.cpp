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
#include <sstream>
#include <string>
#include "Lexer/Lexeme.h"

namespace SxTree::Lexer {
    using std::string;

    Lexeme::Lexeme(const Lexeme &other) = default;

    Lexeme::Lexeme(const string *sourceText, unsigned lexType, size_t startInd, size_t lexSize) noexcept:
            source(sourceText),
            type(lexType),
            start(startInd),
            size(lexSize){
    }

    void Lexeme::connect(const Lexeme &other, unsigned newType) noexcept {
        if (other.size == 0) {
            type = newType;
            return;
        }
        if (other.start < start)
            leftConnect(other, newType);
        else
            rightConnect(other, newType);
    }

    void Lexeme::leftConnect(const Lexeme &other, unsigned newType) noexcept {
        assert((other.start + other.size <= start) && "Invalid lexemes placement");
        const size_t margin = start - (other.start + other.size);
        start = other.start;
        size += other.size + margin;
        type = newType;
    }

    void Lexeme::rightConnect(const Lexeme &other, unsigned newType) noexcept {
        assert((other.start >= start + size) && "Invalid lexemes placement");
        const size_t margin = other.start - (size + start);
        size += other.size + margin;
        type = newType;
    }

    Lexeme::Lexeme(const Lexeme &first, const Lexeme &second, unsigned lexType) noexcept :
            source(first.source),
            type(first.type),
            start(first.start),
            size(first.size){
        connect(second, lexType);
    }

    Lexeme::Lexeme(const Lexeme &first, const Lexeme &second) noexcept:
            source(first.source),
            type(first.type),
            start(first.start),
            size(first.size){
        assert(first.type == second.type);
        connect(second, second.type);
    }

    void Lexeme::operator+=(const Lexeme &other) noexcept {
        assert(type == other.type);
        connect(other, other.type);
    }

    Lexeme Lexeme::operator+(const Lexeme &other) const noexcept {
        assert(type == other.type);
        return Lexeme(*this, other);
    }

    Lexeme::Lexeme(Lexeme &&other) noexcept:
            source(other.source),
            type(other.type),
            start(other.start),
            size(other.size){
        other.type = 0;
        other.source = nullptr;
        other.start = other.size = 0;
    }

    bool Lexeme::operator==(const Lexeme &other) const noexcept {
        if (other.size == size && size == 0)
            return true;
        if (!type || !source || other.type || other.source)
            return false;
        return other.start == start && other.size == size && type == other.type && source == other.source;
    }

    Lexeme Lexeme::zero() {
        return Lexeme(nullptr, 0, 0, 0);
    }

    void Lexeme::setType(unsigned pString) noexcept{
        type = pString;
    }

    string Lexeme::to_string() const {
        std::stringstream ss;
        ss << "Lexeme<id=" << type << ", start=" << start << ", size=" << (size) << ">";
        return ss.str();
    }

    unsigned Lexeme::getType() const {
        return type;
    }

    [[maybe_unused]] size_t Lexeme::getStart() const {
        return start;
    }

    size_t Lexeme::getSize() const {
        return size;
    }

    string Lexeme::valueString() const{
        assert(source && "Source can't be nullptr");
        return source->substr(start, size);
    }
}