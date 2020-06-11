#ifndef SYMBOL_SYMBOL_H
#define SYMBOL_SYMBOL_H

#include <cstdint>
#include <string>
#include <memory>
#include <variant>

#include "SymbolType.h"
#include "SymbolValue.h"

namespace symbol {
    class Symbol;
    using SymbolPtr = std::shared_ptr<Symbol>;

    class Symbol {
    public:
        Symbol() : Symbol(SymbolType::UNKNOWN, nullptr) {}

        Symbol(SymbolType type, SymbolValue value);

        virtual ~Symbol() = default;

        bool operator==(const Symbol &rhs) const;

        bool operator!=(const Symbol &rhs) const;

        [[nodiscard]] virtual SymbolType getType() const;

        [[nodiscard]] SymbolValue getValue() const;

        [[nodiscard]] char getChar() const;

        [[nodiscard]] int getInt() const;

        [[nodiscard]] double getReal() const;

        [[nodiscard]] std::string getString() const;

        [[nodiscard]] std::string getName() const;

        void setValue(SymbolValue value);

        [[nodiscard]] virtual std::string toString() const;

    private:
        SymbolType type_;
        SymbolValue value_;
    };
}

#endif //SYMBOL_SYMBOL_H
