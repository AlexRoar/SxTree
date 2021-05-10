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
#include "Exceptions/IOExceptions.h"
#include "exception"
#include <string>

using std::exception;
using std::string;

namespace SxTree::IO {
    const char *OpenFileException::what() const noexcept {
        return "Unable to open file";
    }
}

