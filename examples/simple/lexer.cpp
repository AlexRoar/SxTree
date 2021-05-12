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

    Lexer coreLexer({
	{1, {{{ R"()", Value::VAL_SKIP,{{{ R"(\s)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{2, {{{ R"(var)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{3, {{{ R"(def)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"(define)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ANY}},
	{4, {{{ R"(o)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"()", Value::VAL_EXPRESSION,{{{ R"(k)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_OPTIONAL}},}, Expression::EXP_ONE}},
});
}
