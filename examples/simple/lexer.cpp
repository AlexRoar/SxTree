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
	{R"(lineBreak)" , {{{ R"(\r\n)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"(\n)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"(\r)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ANY}},
	{R"(margin)" , {{{ R"(^\t)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"(\s{4})", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ANY}},
	{R"(space)" , {{{ R"()", Value::VAL_SKIP,{{{ R"(\s)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(integer)" , {{{ R"(^[-+]?[0-9]\d*)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(float)" , {{{ R"(^[+-]?([0-9]*[.])?[0-9]+)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(def)" , {{{ R"(def)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(let)" , {{{ R"(let)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(assign)" , {{{ R"(=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(leftPa)" , {{{ R"(\()", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(rightPa)" , {{{ R"(\))", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(statEnd)" , {{{ R"(;)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(comma)" , {{{ R"(,)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(return)" , {{{ R"(ret)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(leftBlock)" , {{{ R"(\{)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(rightBlock)" , {{{ R"(\})", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(equal)" , {{{ R"(==)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(lessEqual)" , {{{ R"(<=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(moreEqual)" , {{{ R"(>=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(notEqual)" , {{{ R"(!=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(less)" , {{{ R"(<)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(more)" , {{{ R"(>)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(assignPlus)" , {{{ R"(\+=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(assignMinus)" , {{{ R"(-=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(assignMul)" , {{{ R"(\*=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(assignDiv)" , {{{ R"(/=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(plus)" , {{{ R"(\+)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(minus)" , {{{ R"(-)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(mul)" , {{{ R"(\*)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(div)" , {{{ R"(/)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(if)" , {{{ R"(if)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(else)" , {{{ R"(else)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(while)" , {{{ R"(while)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(string)" , {{{ R"(([\"'])(?:(?=(\\?))\2.)*?\1)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{R"(identifier)" , {{{ R"(^[a-zA-Z_$][a-zA-Z_$0-9]*)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
});
}
