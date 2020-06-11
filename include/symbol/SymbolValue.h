#ifndef SYMBOL_SYMBOL_VALUE_H
#define SYMBOL_SYMBOL_VALUE_H

#include <variant>
#include <cstdint>

namespace symbol {
    using SymbolValue = std::variant<
        std::nullptr_t, // 关键字，运算符
        char,           // 字符字面量
        std::int32_t,   // 整型常数
        double,         // 实型常数
        std::string     // 标识符或字符串字面量
    >;
}
 
#endif //SYMBOL_SYMBOL_VALUE_H
