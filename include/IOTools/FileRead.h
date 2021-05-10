/*
 * =================================================
 * Copyright © 2021.
 * Aleksandr Dremov
 *
 * This code has been written by Aleksandr Dremov
 * Check license agreement of this project to evade
 * possible illegal use.
 * =================================================
 */

#ifndef SXTREE_FILEREAD_H
#define SXTREE_FILEREAD_H

#include <string>
#include <fstream>

namespace SxTree::IO {
    using std::string;
    /**
     * Reads full file to string container
     *
     * @throws OpenFileException if unable to open the file
     * @param fileName
     * @return file contents
     */
    string readFullFile(const char *fileName);

    void dumpFile(const char *fileName, const string& content);
}

#endif //SXTREE_FILEREAD_H
