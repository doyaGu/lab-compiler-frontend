#include "Expression.h"

namespace inter {
    Expression::Expression(SymbolType type) : type_(type) {}

    bool Expression::operator==(const Expression &rhs) const {
        return type_ == rhs.type_;
    }

    bool Expression::operator!=(const Expression &rhs) const {
        return !(rhs == *this);
    }
}

