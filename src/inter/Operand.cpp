#include "Operand.h"

#include <cstdint>

#include "SymbolName.h"

namespace inter {
    Operand::Operand(SymbolType type, SymbolValue value) : Expression(type), value_(std::move(value)) {}

    char Operand::getChar() const {
        char value;
        try {
            value = std::get<char>(value_);
        }
        catch (const std::bad_variant_access &) {}
        return value;
    }

    int Operand::getInt() const {
        int value;
        try {
            value = std::get<std::int32_t>(value_);
        }
        catch (const std::bad_variant_access &) {}
        return value;
    }

    double Operand::getReal() const {
        double value;
        try {
            value = std::get<double>(value_);
        }
        catch (const std::bad_variant_access &) {}
        return value;
    }

    std::string Operand::getString() const {
        std::string value;
        try {
            value = std::get<std::string>(value_);
        }
        catch (const std::bad_variant_access &) {}
        return value;
    }

    SymbolValue Operand::getValue() const {
        return value_;
    }

    void Operand::setValue(const SymbolValue &value) {
        value_ = value;
    }

    std::string Operand::toString() const {
        std::string value;
        switch (type_) {
            case SymbolType::INT:
                value = std::to_string(getInt());
                break;
            case SymbolType::REAL:
                value = std::to_string(getReal());
                break;
            case SymbolType::CHAR:
                value.push_back('\'');
                value.push_back(getChar());
                value.push_back('\'');
                break;
            case SymbolType::STRING:
                value = "\"" + getString() + "\"";
                break;
            default:
                value = " ";
                break;
        }

        return value;
    }
}