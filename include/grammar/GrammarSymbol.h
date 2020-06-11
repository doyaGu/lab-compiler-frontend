#ifndef GRAMMAR_GRAMMAR_SYMBOL_H
#define GRAMMAR_GRAMMAR_SYMBOL_H

#include <vector>
#include <memory>

#include "Token.h"

namespace grammar {
    using namespace symbol;

    class GrammarSymbol;
    using GrammarSymbolPtr = std::shared_ptr<GrammarSymbol>;

    class GrammarSymbol : public Token {
    public:
        GrammarSymbol() : GrammarSymbol(SymbolType::UNKNOWN, nullptr, SymbolLocation(), nullptr, {}) {}

        explicit GrammarSymbol(Token token);

        GrammarSymbol(SymbolType type, SymbolValue value, SymbolLocation location, GrammarSymbolPtr head, std::vector<GrammarSymbolPtr> symbols);

        bool operator==(const GrammarSymbol &rhs) const;

        bool operator!=(const GrammarSymbol &rhs) const;

        GrammarSymbolPtr &getHead();

        std::vector<GrammarSymbolPtr> &getSymbols();

        void setHead(GrammarSymbolPtr head);

        void setSymbols(std::vector<GrammarSymbolPtr> symbols);

    private:
        GrammarSymbolPtr head_;
        std::vector<GrammarSymbolPtr> symbols_;
    };
}
#endif //GRAMMAR_GRAMMAR_SYMBOL_H
