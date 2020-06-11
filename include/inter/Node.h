#ifndef INTER_NODE_H
#define INTER_NODE_H

#include <string>
#include <memory>

#include "Symbol.h"
#include "SymbolType.h"

namespace inter {
    using namespace symbol;

    class Node;
    using NodePtr = std::shared_ptr<Node>;

    class Node {
    public:
        virtual ~Node() = default;

        [[nodiscard]] virtual std::string toString() const;

        static void error(const std::string &msg);
    };
}

#endif //INTER_NODE_H
