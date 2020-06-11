#include "SymbolLocation.h"

namespace symbol {
    SymbolLocation::SymbolLocation(std::string_view filename, int line, int column) :
        filename_(filename),
        row_(line),
        column_(column) {}

    bool SymbolLocation::operator==(const SymbolLocation &rhs) const {
        return filename_ == rhs.filename_ &&
               row_ == rhs.row_ &&
               column_ == rhs.column_;
    }

    bool SymbolLocation::operator!=(const SymbolLocation &rhs) const {
        return !(rhs == *this);
    }

    long SymbolLocation::getRow() const {
        return row_;
    }

    long SymbolLocation::getColumn() const {
        return column_;
    }

    void SymbolLocation::setRow(long row) {
        row_ = row;
    }

    void SymbolLocation::setColumn(long column) {
        column_ = column;
    }

    void SymbolLocation::setPosition(long row, long column) {
        row_ = row;
        column_ = column;
    }

    std::string SymbolLocation::toString() const {
        return std::string(filename_) + ":" + std::to_string(row_) + ":" + std::to_string(column_) + ":";
    }

}
