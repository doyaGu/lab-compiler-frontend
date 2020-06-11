#include "Symbol.h"

#include <utility>

#include "SymbolName.h"

namespace symbol {
    Symbol::Symbol(SymbolType type, SymbolValue value) :
        type_(type),
        value_(std::move(value)) {}

    bool Symbol::operator==(const Symbol &rhs) const {
        return type_ == rhs.type_ &&
               value_ == rhs.value_;
    }

    bool Symbol::operator!=(const Symbol &rhs) const {
        return !(rhs == *this);
    }

    SymbolType Symbol::getType() const {
        return type_;
    }

    SymbolValue Symbol::getValue() const {
        return value_;
    }

    char Symbol::getChar() const {
        char value;
        try {
            value = std::get<char>(value_);
        }
        catch (const std::bad_variant_access &) {}
        return value;
    }

    int Symbol::getInt() const {
        int value;
        try {
            value = std::get<std::int32_t>(value_);
        }
        catch (const std::bad_variant_access &) {}
        return value;
    }

    double Symbol::getReal() const {
        double value;
        try {
            value = std::get<double>(value_);
        }
        catch (const std::bad_variant_access &) {}
        return value;
    }

    std::string Symbol::getString() const {
        std::string value;
        try {
            value = std::get<std::string>(value_);
        }
        catch (const std::bad_variant_access &) {}
        return value;
    }

    std::string Symbol::getName() const {
        return std::string(sym2str(getType()));
    }

    void Symbol::setValue(SymbolValue value) {
        value_ = std::move(value);
    }

    std::string Symbol::toString() const {
        return std::string("Symbol(" + getName() + ")");
    }

}