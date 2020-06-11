#include "GrammarSymbol.h"

namespace grammar {
    GrammarSymbol::GrammarSymbol(Token token) : Token(std::move(token)) {}

    GrammarSymbol::GrammarSymbol(SymbolType type, SymbolValue value, GrammarSymbolPtr head, std::vector<GrammarSymbolPtr> symbols) :
        Token(type, std::move(value)),
        head_(std::move(head)),
        symbols_(std::move(symbols)) {}

    bool GrammarSymbol::operator==(const GrammarSymbol &rhs) const {
        return static_cast<const Symbol &>(*this) == static_cast<const Symbol &>(rhs) &&
               head_ == rhs.head_ &&
               symbols_ == rhs.symbols_;
    }

    bool GrammarSymbol::operator!=(const GrammarSymbol &rhs) const {
        return !(rhs == *this);
    }

    GrammarSymbolPtr &GrammarSymbol::getHead() {
        return head_;
    }

    std::vector<GrammarSymbolPtr> &GrammarSymbol::getSymbols() {
        return symbols_;
    }

    void GrammarSymbol::setHead(GrammarSymbolPtr head) {
        head_ = std::move(head);
    }

    void GrammarSymbol::setSymbols(std::vector<GrammarSymbolPtr> symbols) {
        symbols_ = std::move(symbols);
    }
}
