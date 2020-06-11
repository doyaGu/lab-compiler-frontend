#include "GrammarProduction.h"

#include <utility>

namespace grammar {

    GrammarProduction::GrammarProduction(SymbolType head, std::vector<SymbolType> body, SemanticAction action,
                                         std::string description) :
        head_(head),
        body_(std::move(body)),
        action_(std::move(action)),
        description_(std::move(description)) {}

    bool GrammarProduction::match(const std::vector<GrammarSymbolPtr> &symbols) const {
        auto iter = body_.cbegin();
        for (const auto &symbol : symbols) {
            if (iter == body_.cend()) {
                break;
            }
            if (*iter != symbol->getType()) {
                return false;
            }
            ++iter;
        }

        return iter == body_.cend();
    }

    SymbolType GrammarProduction::getHead() const {
        return head_;
    }

    const std::vector<SymbolType> &GrammarProduction::getBody() const {
        return body_;
    }

    int GrammarProduction::getBodySize() const {
        return body_.size();
    }

    const std::string &GrammarProduction::getDescription() const {
        return description_;
    }

    GrammarSymbolPtr GrammarProduction::reduce(std::vector<GrammarSymbolPtr> symbols) {
        auto head = std::make_shared<GrammarSymbol>(head_);
        for (auto &symbol : symbols) {
            symbol->setHead(head);
        }

        action_(head, symbols);

        head->setSymbols(std::move(symbols));
        return head;
    }
}
