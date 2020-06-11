#ifndef INTER_IDENTIFIER_H
#define INTER_IDENTIFIER_H

#include <string>
#include <memory>

#include "Operand.h"

namespace inter {
    class Identifier;

    using IdentifierPtr = std::shared_ptr<Identifier>;

    class Identifier : public Operand {
    public:
        explicit Identifier(const std::string &name) : Identifier(name, nullptr) {}

        Identifier(const std::string &name, OperandPtr operand);

        bool operator==(const Identifier &rhs) const;

        [[nodiscard]] std::string getName() const;

        [[nodiscard]] const OperandPtr &getOperand() const;

        void setOperand(const OperandPtr &operand);

        [[nodiscard]] std::string toString() const override;

    private:
        OperandPtr operand_;
    };
}

#endif //INTER_IDENTIFIER_H
