#ifndef SYMBOL_TOKEN_LOCATION_H
#define SYMBOL_TOKEN_LOCATION_H

#include <string>
#include <string_view>

namespace symbol {
    class SymbolLocation {
    public:
        SymbolLocation() : SymbolLocation("", 0, 0) {}

        SymbolLocation(std::string_view filename, int line, int column);

        bool operator==(const SymbolLocation &rhs) const;

        bool operator!=(const SymbolLocation &rhs) const;

        [[nodiscard]] long getRow() const;

        [[nodiscard]] long getColumn() const;

        void setRow(long row);

        void setColumn(long column);

        void setPosition(long row, long column);

        [[nodiscard]] std::string toString() const;

    private:
        std::string_view filename_;
        long row_;
        long column_;
    };
}

#endif //SYMBOL_SYMBOL_LOCATION_H
