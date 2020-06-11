#ifndef LEXER_TOKEN_H_
#define LEXER_TOKEN_H_

#include <string>
#include <tuple>
#include <map>
#include <memory>
#include <utility>
#include <variant>

#include "Symbol.h"
#include "SymbolLocation.h"

namespace symbol {
    class Token;
    using TokenPtr = std::shared_ptr<Token>;

    class Token : public Symbol {
    public:
        Token() : Token(SymbolType::UNKNOWN, nullptr, SymbolLocation(), "") {}

        Token(SymbolType type, SymbolValue value) : Token(type, std::move(value), SymbolLocation(), "") {}

        Token(SymbolType type, SymbolValue value, SymbolLocation location, std::string_view lexeme);

        bool operator==(const Token &rhs) const;

        bool operator!=(const Token &rhs) const;

        [[nodiscard]] const SymbolLocation &getLocation() const;

        [[nodiscard]] std::string getLexeme() const;

        void setLocation(const SymbolLocation &location);

        void setLexeme(std::string_view lexeme);

        [[nodiscard]] std::string toString() const override;

    private:
        SymbolLocation location_;
        std::string lexeme_;
    };
}

#endif // LEXER_TOKEN_H_