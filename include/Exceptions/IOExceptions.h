/*
 * =================================================
 * Copyright (c) 2021.
 * Aleksandr Dremov
 *
 * This code has been written by Aleksandr Dremov
 * Check license agreement of this project to evade
 * possible illegal use.
 * =================================================
 */

#ifndef SXTREE_IOEXCEPTIONS_H
#define SXTREE_IOEXCEPTIONS_H
#include <exception>
#include <string>

using std::exception;
using std::string;

namespace SxTree::IO{
    struct OpenFileException : public exception {
        const char * what() const noexcept override;
    };
}

#endif //SXTREE_IOEXCEPTIONS_H
