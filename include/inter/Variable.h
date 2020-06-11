#ifndef INTER_VARIABLE_H
#define INTER_VARIABLE_H

#include <string>
#include <memory>

#include "Operand.h"
#include "Identifier.h"

namespace inter {
    class Variable;
    using VariablePtr = std::shared_ptr<Variable>;

    class Variable : public Operand {
    public:
        Variable() : Variable(nullptr, SymbolType::UNKNOWN, nullptr) {}

        Variable(Identifier *identifier, SymbolType type, SymbolValue value);

    private:
        Identifier *identifier_;
    };
}

#endif //INTER_VARIABLE_H
