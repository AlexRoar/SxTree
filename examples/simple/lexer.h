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

#include <vector>
#include "Lexer/LexerStruct.h"
#include "Lexer/Lexer.h"

namespace SxTree::Lexer {
    using namespace SxTree::LexerStruct;

    enum LexemeType {
	lex_NONE = 0,
	lex_space = 1,
	lex_var = 2,
	lex_funcDecl = 3,
	lex_ok = 4,
};

    extern Lexer coreLexer;
}
