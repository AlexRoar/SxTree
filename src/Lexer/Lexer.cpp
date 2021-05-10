
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
            rules(rulesNew),
            lexPos(nullptr),
            lexemes() {}

    void Lexer::parse(const string &parseContent) {
        content = parseContent;
        lexPos.storage = &content;
        lexPos.posNow = 0;

        while (!lexPos.isEnded()) {
            bool resolved = false;
            for (const auto& rule: rules) {
                auto lexeme = rule.parse(lexPos);
                if (lexeme.has_value()){
                    resolved = true;
                    lexemes.push_back(std::move(lexeme.value()));
                    break;
                }
            }

            if (!resolved) {
                addError("Unresolved sequence");
                break;
            }
        }
    }

    void Lexer::addError(const char *msg) {
        errors.push_back({msg, lexPos.posNow});
    }

    const vector<Lexeme> &Lexer::getLexemes() {
        return lexemes;
    }

    const vector<LexerError> &Lexer::getErrors() const {
        return errors;
    }
}