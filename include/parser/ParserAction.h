#ifndef PARSER_ACTION_H
#define PARSER_ACTION_H

#include <cstdint>
#include <string>

#include "ParserActionType.h"

namespace parser {
    using ParserActionTarget = uint8_t;

    struct ParserAction {
        ParserAction() : ParserAction(ParserActionType::FAIL, 0) {}

        ParserAction(ParserActionType action_type, ParserActionTarget action_target) :
            type(action_type),
            target(action_target) {};

        ParserActionType type;
        ParserActionTarget target;

        [[nodiscard]] std::string toString() const {
            std::string str;
            switch (type) {
                case ParserActionType::SHIFT:
                    str = "Shift";
                    break;
                case ParserActionType::REDUCE:
                    str = "Reduce";
                    break;
                case ParserActionType::ACCEPT:
                    str = "Accept";
                    break;
                case ParserActionType::FAIL:
                    str = "Fail";
                    break;
            }
            return str;
        }
    };

}
#endif //PARSER_ACTION_H
