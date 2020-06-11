#include "Operator.h"

#include <map>

namespace inter {
    Operator::Operator(SymbolType type) : Expression(type) {}

    std::string Operator::toString() const {
        static std::map<SymbolType, std::string> names = {
            {SymbolType::PL, "+"},
            {SymbolType::MI, "-"},
            {SymbolType::MU, "*"},
            {SymbolType::DI, "/"}
        };
        return names[type_];
    }
}