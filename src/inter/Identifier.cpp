#include "Identifier.h"

namespace inter {
    Identifier::Identifier(const std::string &name, OperandPtr operand) :
        Operand(SymbolType::ID, name),
        operand_(std::move(operand)) {}

    bool Identifier::operator==(const Identifier &rhs) const {
        return value_ == rhs.value_;
    }

    std::string Identifier::getName() const {
        return getString();
    }

    const OperandPtr &Identifier::getOperand() const {
        return operand_;
    }

    void Identifier::setOperand(const OperandPtr &operand) {
        operand_ = operand;
    }

    std::string Identifier::toString() const {
        return getString();
    }
}

