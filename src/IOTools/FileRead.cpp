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

#include <string>
#include <cstdio>
#include <IOTools/FileRead.h>

#include "Exceptions/IOExceptions.h"

namespace SxTree::IO {

    /**
     * @throws OpenFileException
     * @param fileName
     * @return
     */
    std::string readFullFile(const char *fileName) {
        auto inputFile = fopen(fileName, "rb");
        if (!inputFile)
            throw OpenFileException();

        fseek(inputFile, 0, SEEK_END);
        const auto size = ftell(inputFile);
        rewind(inputFile);
        std::string input(size, '\0');
        fread(&input[0], 1, size, inputFile);
        fclose(inputFile);

        return input;
    }

    /**
     * @throws OpenFileException
     * @param fileName
     * @param content
     */
    void dumpFile(const char *fileName, const string &content) {
        auto inputFile = fopen(fileName, "wb");
        if (!inputFile)
            throw OpenFileException();

        fwrite(content.c_str(), 1, content.size(), inputFile);

        fclose(inputFile);
    }

}