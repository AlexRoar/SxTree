
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

#include "Lexer/Lexer.h"

namespace SxTree::Lexer {
    Lexer::Lexer(const vector<Rule> &rulesNew) :
            lexPos(nullptr),
            rules(rulesNew){}

    vector<Lexeme> Lexer::parse(const string &parseContent) {
        vector<Lexeme> lexemes;
        content = parseContent;
        lexPos.storage = &content;
        lexPos.posNow = 0;

        while (!lexPos.isEnded()) {
            bool resolved = false;
            for (const auto& rule: rules) {
                auto lexeme = rule.parse(lexPos);
                if (lexeme.has_value()){
                    resolved = true;
                    if(lexeme.value() != Lexeme::zero())
                        lexemes.push_back(std::move(lexeme.value()));
                    break;
                }
            }

            if (!resolved) {
                addError("Unresolved sequence");
                break;
            }
        }
        return lexemes;
    }

    void Lexer::addError(const char *msg) {
        errors.push_back({msg, lexPos.posNow});
    }

    const vector<LexerError> &Lexer::getErrors() const {
        return errors;
    }
}