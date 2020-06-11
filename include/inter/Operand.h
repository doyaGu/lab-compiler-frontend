#ifndef INTER_OPERAND_H
#define INTER_OPERAND_H

#include <memory>

#include "Expression.h"

namespace inter {
    class Operand;
    using OperandPtr = std::shared_ptr<Operand>;

    class Operand : public Expression {
    public:
        Operand() : Operand(SymbolType::OPERAND, nullptr) {}

        Operand(SymbolType type, SymbolValue value);

        [[nodiscard]] char getChar() const;

        [[nodiscard]] int getInt() const;

        [[nodiscard]] double getReal() const;

        [[nodiscard]] std::string getString() const;

        [[nodiscard]] SymbolValue getValue() const;

        virtual void setValue(const SymbolValue &value);

        [[nodiscard]] std::string toString() const override;

    protected:
        SymbolValue value_;

    };
};

#endif //INTER_OPERAND_H