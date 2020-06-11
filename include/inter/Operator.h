#ifndef INTER_OPERATOR_H
#define INTER_OPERATOR_H

#include "Expression.h"
#include "Token.h"

namespace inter {
    class Operator : public Expression {
    public:
        Operator() : Operator(SymbolType::OPERATOR) {}

        explicit Operator(SymbolType type);

        [[nodiscard]] std::string toString() const override;
    };
};

#endif //INTER_OPERATOR_H
