#include <Temp.h>

#include <utility>

namespace inter {
    int Temp::nxt_ = 0;

    Temp::Temp(SymbolType type, SymbolValue value) : Operand(type, std::move(value)), index_(nxt_++) {}

    void Temp::set(SymbolValue value) {
        value_ = std::move(value);
    }

    std::string Temp::toString() const {
        return "T" + std::to_string(index_ + 1);
    }
}

