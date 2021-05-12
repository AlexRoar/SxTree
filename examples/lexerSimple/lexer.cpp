/*
 * =================================================
 * Copyright © 2021
 * Aleksandr Dremov
 *
 * This code has been written by Aleksandr Dremov
 * Check license agreement of this project to evade
 * possible illegal use.
 * =================================================
 *
 * THIS CODE WAS GENERATED, DO NOT EDIT
 *
 */

#include "Lexer/LexerStruct.h"
#include "Lexer/Lexer.h"
#include "lexer.h"

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

    string to_string(unsigned type){
        switch(SxTree::Lexer::LexemeType(type)) { {
		case SxTree::Lexer::LexemeType::lex_identifier: return "identifier";
		case SxTree::Lexer::LexemeType::lex_if: return "if";
		case SxTree::Lexer::LexemeType::lex_div: return "div";
		case SxTree::Lexer::LexemeType::lex_minus: return "minus";
		case SxTree::Lexer::LexemeType::lex_plus: return "plus";
		case SxTree::Lexer::LexemeType::lex_assignDiv: return "assignDiv";
		case SxTree::Lexer::LexemeType::lex_comma: return "comma";
		case SxTree::Lexer::LexemeType::lex_less: return "less";
		case SxTree::Lexer::LexemeType::lex_margin: return "margin";
		case SxTree::Lexer::LexemeType::lex_assignPlus: return "assignPlus";
		case SxTree::Lexer::LexemeType::lex_notEqual: return "notEqual";
		case SxTree::Lexer::LexemeType::lex_lessEqual: return "lessEqual";
		case SxTree::Lexer::LexemeType::lex_rightBlock: return "rightBlock";
		case SxTree::Lexer::LexemeType::lex_else: return "else";
		case SxTree::Lexer::LexemeType::lex_assign: return "assign";
		case SxTree::Lexer::LexemeType::lex_return: return "return";
		case SxTree::Lexer::LexemeType::lex_while: return "while";
		case SxTree::Lexer::LexemeType::lex_moreEqual: return "moreEqual";
		case SxTree::Lexer::LexemeType::lex_mul: return "mul";
		case SxTree::Lexer::LexemeType::lex_statEnd: return "statEnd";
		case SxTree::Lexer::LexemeType::lex_string: return "string";
		case SxTree::Lexer::LexemeType::lex_more: return "more";
		case SxTree::Lexer::LexemeType::lex_let: return "let";
		case SxTree::Lexer::LexemeType::lex_assignMul: return "assignMul";
		case SxTree::Lexer::LexemeType::lex_integer: return "integer";
		case SxTree::Lexer::LexemeType::lex_def: return "def";
		case SxTree::Lexer::LexemeType::lex_space: return "space";
		case SxTree::Lexer::LexemeType::lex_lineBreak: return "lineBreak";
		case SxTree::Lexer::LexemeType::lex_equal: return "equal";
		case SxTree::Lexer::LexemeType::lex_leftPa: return "leftPa";
		case SxTree::Lexer::LexemeType::lex_rightPa: return "rightPa";
		case SxTree::Lexer::LexemeType::lex_float: return "float";
		case SxTree::Lexer::LexemeType::lex_assignMinus: return "assignMinus";
		case SxTree::Lexer::LexemeType::lex_leftBlock: return "leftBlock";

        default: return "UNRECOGNIZED LEXEME";
        }
    }
}
