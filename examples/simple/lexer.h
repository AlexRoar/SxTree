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

#include "Lexer/LexerStruct.h"
#include "Lexer/Lexer.h"

namespace SxTree::Lexer {
    using namespace SxTree::LexerStruct;

    enum class LexemeType {
	lex_NONE = 0,
	lex_lineBreak = 1,
	lex_margin = 2,
	lex_space = 3,
	lex_integer = 4,
	lex_float = 5,
	lex_def = 6,
	lex_let = 7,
	lex_assign = 8,
	lex_leftPa = 9,
	lex_rightPa = 10,
	lex_statEnd = 11,
	lex_comma = 12,
	lex_return = 13,
	lex_leftBlock = 14,
	lex_rightBlock = 15,
	lex_equal = 16,
	lex_lessEqual = 17,
	lex_moreEqual = 18,
	lex_notEqual = 19,
	lex_less = 20,
	lex_more = 21,
	lex_assignPlus = 22,
	lex_assignMinus = 23,
	lex_assignMul = 24,
	lex_assignDiv = 25,
	lex_plus = 26,
	lex_minus = 27,
	lex_mul = 28,
	lex_div = 29,
	lex_if = 30,
	lex_else = 31,
	lex_while = 32,
	lex_string = 33,
	lex_identifier = 34,
};

    extern const unsigned lexemesNumber;
    extern Lexer coreLexer;
}
