#ifndef LEXER_TOKEN_TABLE_H_
#define LEXER_TOKEN_TABLE_H_

#include <string>
#include <map>
#include <tuple>

#include "Token.h"

namespace symbol {
    class TokenTable {
    public:
        TokenTable();

        [[nodiscard]] SymbolType lookup(const std::string &lexeme) const;

        [[nodiscard]] bool haveToken(const std::string &lexeme) const;

    private:
        std::map<std::string, SymbolType> table_;
    };
}

#endif // LEXER_TOKEN_TABLE_H_
