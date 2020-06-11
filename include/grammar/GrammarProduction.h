#ifndef GRAMMAR_GRAMMAR_PRODUCTION_H
#define GRAMMAR_GRAMMAR_PRODUCTION_H

#include <vector>
#include <functional>

#include "SymbolType.h"
#include "GrammarSymbol.h"

namespace grammar {
    using namespace symbol;
    using SemanticAction = std::function<void(GrammarSymbolPtr, std::vector<GrammarSymbolPtr> &)>;

    class GrammarProduction {
    public:
        GrammarProduction() : GrammarProduction(SymbolType::UNKNOWN, {SymbolType::UNKNOWN},
                                                [](GrammarSymbolPtr head, std::vector<GrammarSymbolPtr> &body) {}, "") {}

        GrammarProduction(SymbolType head, std::vector<SymbolType> body, SemanticAction action, std::string description);

        [[nodiscard]] bool match(const std::vector<GrammarSymbolPtr> &symbols) const;

        [[nodiscard]] int getBodySize() const;

        [[nodiscard]] const std::string &getDescription() const;

        GrammarSymbolPtr reduce(std::vector<GrammarSymbolPtr> symbols);

    private:
        SymbolType head_;
        std::vector<SymbolType> body_;
        SemanticAction action_;
        std::string description_;
    };
}
#endif //GRAMMAR_GRAMMAR_PRODUCTION_H
