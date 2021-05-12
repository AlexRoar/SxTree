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

    Lexer coreLexer({
	{1, {{{ R"(\r\n)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"(\n)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"(\r)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ANY}},
	{2, {{{ R"(^\t)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},{ R"(\s{4})", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ANY}},
	{3, {{{ R"()", Value::VAL_SKIP,{{{ R"(\s)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{4, {{{ R"(^[-+]?[0-9]\d*)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{5, {{{ R"(^[+-]?([0-9]*[.])?[0-9]+)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{6, {{{ R"(def)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{7, {{{ R"(let)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{8, {{{ R"(=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{9, {{{ R"(\()", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{10, {{{ R"(\))", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{11, {{{ R"(;)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{12, {{{ R"(,)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{13, {{{ R"(ret)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{14, {{{ R"(\{)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{15, {{{ R"(\})", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{16, {{{ R"(==)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{17, {{{ R"(<=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{18, {{{ R"(>=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{19, {{{ R"(!=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{20, {{{ R"(<)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{21, {{{ R"(>)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{22, {{{ R"(\+=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{23, {{{ R"(-=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{24, {{{ R"(\*=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{25, {{{ R"(/=)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{26, {{{ R"(\+)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{27, {{{ R"(-)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{28, {{{ R"(\*)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{29, {{{ R"(/)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{30, {{{ R"(if)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{31, {{{ R"(else)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{32, {{{ R"(while)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{33, {{{ R"(([\"'])(?:(?=(\\?))\2.)*?\1)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
	{34, {{{ R"(^[a-zA-Z_$][a-zA-Z_$0-9]*)", Value::VAL_REGEXP,{{}, Expression::EXP_ONE}},}, Expression::EXP_ONE}},
});

    const unsigned lexemesNumber = 34;
}
