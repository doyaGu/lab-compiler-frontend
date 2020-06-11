#include "TokenTable.h"

namespace symbol {
    TokenTable::TokenTable() {
        table_ = {
            /* 关键字 Keywords */
            {"if", SymbolType::IF},
            {"then", SymbolType::THEN},
            {"else", SymbolType::ELSE},
            {"for", SymbolType::FOR},
            {"begin", SymbolType::BEGIN},
            {"end", SymbolType::END},

            /* 运算符 Operators */
            {":=", SymbolType::IS},
            {"<", SymbolType::LT},
            {"<=", SymbolType::LE},
            {"=", SymbolType::EQ},
            {"<>", SymbolType::NE},
            {">", SymbolType::GT},
            {">=", SymbolType::GE},
            {"+", SymbolType::PL},
            {"-", SymbolType::MI},
            {"*", SymbolType::MU},
            {"/", SymbolType::DI},
            {"&", SymbolType::AND},
            {"|", SymbolType::OR},
            {"~", SymbolType::NOT},
            {"^", SymbolType::XOR},
            {"<<", SymbolType::SHL},
            {">>", SymbolType::SHR},

            /* 定界符 Delimiters */
            {"(", SymbolType::LPAREN},
            {")", SymbolType::RPAREN},
            {",", SymbolType::COMMA},
            {";", SymbolType::SEMICOLON},
        };
    }

    SymbolType TokenTable::lookup(const std::string &lexeme) const {
        SymbolType type = SymbolType::ID;
        auto iter = table_.find(lexeme);
        if (iter != table_.end()) {
            type = iter->second;
        }
        return type;
    }

    bool TokenTable::haveToken(const std::string &lexeme) const {
        auto iter = table_.find(lexeme);
        return iter != table_.end();
    }
}

