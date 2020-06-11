#include "Constant.h"

namespace inter {
    Constant::Constant(SymbolType type, SymbolValue value) : Operand(type, std::move(value)) {}

    void Constant::setValue(const SymbolValue &value) {}
}