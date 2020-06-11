#ifndef INTER_CONSTANT_H
#define INTER_CONSTANT_H

#include <memory>

#include "Operand.h"

namespace inter {
    class Constant;
    using ConstantPtr = std::shared_ptr<Constant>;

    class Constant : public Operand {
    public:
        Constant() : Constant(SymbolType::UNKNOWN, nullptr) {}

        Constant(SymbolType type, SymbolValue value);

        void setValue(const SymbolValue &value) override;
    };
}

#endif //INTER_CONSTANT_H
