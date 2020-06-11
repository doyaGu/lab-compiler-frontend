#include "Variable.h"

#include <utility>

namespace inter {
    Variable::Variable(Identifier *identifier, SymbolType type, SymbolValue value) :
        Operand(type,std::move(value)),
        identifier_(identifier) {

    }
}