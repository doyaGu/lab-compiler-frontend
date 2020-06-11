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

    int GrammarProduction::getBodySize() const {
        return body_.size();
    }

    const std::string &GrammarProduction::getDescription() const {
        return description_;
    }

    GrammarSymbolPtr GrammarProduction::reduce(std::vector<GrammarSymbolPtr> symbols) {
        auto head = std::make_shared<GrammarSymbol>(head_, 0, symbols.front()->getLocation(), nullptr, symbols);
        for (auto &symbol : head->getSymbols()) {
            symbol->setHead(head);
        }

        action_(head, head->getSymbols());

        return head;
    }
}
