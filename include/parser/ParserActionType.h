#ifndef PARSER_ACTION_TYPE_H
#define PARSER_ACTION_TYPE_H

namespace parser {
    enum class ParserActionType : uint8_t {
        SHIFT,
        REDUCE,
        ACCEPT,
        FAIL
    };
}

#endif //PARSER_ACTION_TYPE_H
