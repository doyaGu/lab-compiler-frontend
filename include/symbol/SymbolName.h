#ifndef SYMBOL_SYMBOL_NAME_H
#define SYMBOL_SYMBOL_NAME_H

#include "SymbolType.h"

namespace {
    constexpr const char * const SYMBOL_NAMES[] = {
        /*
         *  终结符号 Terminal symbols
         */

        /* 标识符 Identifier */
        "ID",         // 字母打头的字母数字串

        /* 字面量 Literals */
        "INT",            // 整型常数
        "REAL",           // 实型常数
        "CHAR",           // 字符型常量
        "STRING",         // 字符串型常量

        /* 关键字 Keywords */
        "IF",             // if
        "THEN",           // then
        "ELSE",           // else
        "FOR",            // for
        "BEGIN",          // begin
        "END",            // end

        /* 运算符 Operators */
        // 赋值运算符
        "IS",             // :=

        // 关系运算符
        "LT",             // <
        "LE",             // <=
        "EQ",             // =
        "NE",             // <>
        "GT",             // >
        "GE",             // >=

        // 算术运算符
        "PL",             // +
        "MI",             // -
        "MU",             // *
        "DI",             // /

        // 逻辑运算符
        "AND",            // &
        "OR",             // |
        "NOT",            // ~
        "XOR",            // ^
        "SHL",            // <<
        "SHR",            // >>

        /* 定界符 Delimiters */
        "LPAREN",         // (
        "RPAREN",         // )
        "COMMA",          // ,
        "SEMICOLON",      // ;

        /*
         *  非终结符号 Non-terminal symbols
         */

        "EXPR",           // 表达式
        "TERM",           // 项
        "FACTOR",         // 因式
        "OPERAND",        // 运算对象
        "OPERATOR",       // 运算符

        /*
         *  特殊符号 special symbols
         */

        "TEMP",           // 临时变量标记
        "QUAD",           // 四元式标记
        "EOF",            // 文件结束符
        "UNKNOWN"
    };
}

namespace symbol {
    constexpr const char *sym2str(SymbolType type) {
        return SYMBOL_NAMES[static_cast<uint8_t>(type)];
    }
}

#endif //SYMBOL_SYMBOL_NAME_H
