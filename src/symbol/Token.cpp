#include "Token.h"

namespace symbol {
    Token::Token(SymbolType type, SymbolValue value, SymbolLocation location, std::string_view lexeme) :
        Symbol(type, std::move(value)),
        location_(location),
        lexeme_(lexeme) {}

    bool Token::operator==(const Token &rhs) const {
        return static_cast<const Symbol &>(*this) == static_cast<const Symbol &>(rhs) &&
               lexeme_ == rhs.lexeme_;
    }

    bool Token::operator!=(const Token &rhs) const {
        return !(rhs == *this);
    }

    const SymbolLocation &Token::getLocation() const {
        return location_;
    }

    std::string Token::getLexeme() const {
        return lexeme_;
    }

    void Token::setLocation(const SymbolLocation &location) {
        location_ = location;
    }

    void Token::setLexeme(std::string_view lexeme) {
        lexeme_ = std::string(lexeme);
    }

    std::string Token::toString() const {
        std::string value;
        switch (getType()) {
            case SymbolType::ID:
                value = std::string("'" + getString() + "'");
                break;
            case SymbolType::INT:
                value = std::to_string(getInt());
                break;
            case SymbolType::REAL:
                value = std::to_string(getReal());
                break;
            case SymbolType::CHAR:
                value.push_back(getChar());
                break;
            case SymbolType::STRING:
                value = getString();
                break;
            case SymbolType::UNKNOWN:
                value = getLexeme();
                break;
            default:
                value = " ";
                break;
        }

        return std::string("(" + getName() + ", " + value + ")");
    }
}