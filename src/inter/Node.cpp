#include "Node.h"

#include <stdexcept>

namespace inter {
    void Node::error(const std::string &msg) {
        throw std::runtime_error(msg);
    }

    std::string Node::toString() const {
        return "Node";
    }
}

