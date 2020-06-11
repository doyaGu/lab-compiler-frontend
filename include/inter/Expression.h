#ifndef INTER_EXPRESSION_H
#define INTER_EXPRESSION_H

#include "Node.h"
#include "Token.h"

namespace inter {
    class Expression : public Node {
    public:
        explicit Expression(SymbolType type);

        bool operator==(const Expression &rhs) const;

        bool operator!=(const Expression &rhs) const;

    protected:
        SymbolType type_;
    };
}

#endif //INTER_EXPRESSION_H
