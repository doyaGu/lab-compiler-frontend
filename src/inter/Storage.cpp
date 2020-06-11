#include "Storage.h"

#include <algorithm>
#include <iostream>

#include "SymbolType.h"

namespace inter {
    Storage::Storage() = default;

    std::int32_t Storage::lookup(const std::string &name) const {
        auto result = std::find_if(ids_.cbegin(), ids_.cend(),
                                   [name](const IdentifierPtr &identifier) { return identifier->getName() == name; });
        return (result != ids_.cend()) ? (0x40000000u + static_cast<std::uint32_t>(result - ids_.cbegin())) : 0;
    }

    std::int32_t Storage::enter(const std::string &name) {
        auto id = std::make_shared<Identifier>(name);
        ids_.push_back(id);
        return 0x40000000u + static_cast<std::uint32_t>(ids_.size() - 1u);
    }

    std::int32_t Storage::entry(const std::string &name) {
        auto id = lookup(name);
        return (id) ? id : enter(name);
    }

    std::int32_t Storage::entry(const SymbolPtr &symbol) {
        std::int32_t id = 0;
        switch (symbol->getType()) {
            case SymbolType::ID:
                id = entry(symbol->getString());
                break;
            case SymbolType::INT:
            case SymbolType::REAL:
            case SymbolType::CHAR:
            case SymbolType::STRING:
                id = newConstant(symbol->getType(), symbol->getValue());
                break;
            default:
                break;
        }
        return id;
    }

    std::int32_t Storage::gen(SymbolType op, std::int32_t arg1, std::int32_t arg2, std::int32_t result) {
        auto quad = std::make_shared<Quaternion>(Operator(op), toOperand(arg1), toOperand(arg2), toOperand(result));
        quads_.push_back(quad);
        return quads_.size();
    }

    std::int32_t Storage::newTemp() {
        auto temp = std::make_shared<Temp>();
        temps_.push_back(temp);
        return 0xC0000000u + static_cast<std::uint32_t>(temps_.size() - 1u);
    }

    std::int32_t Storage::newConstant(SymbolType type, const SymbolValue &value) {
        auto constant = std::make_shared<Constant>(type, value);
        constants_.push_back(constant);
        return 0x80000000u + static_cast<std::uint32_t>(constants_.size() - 1u);
    }

    std::ostream &Storage::printQuaternions(std::ostream& os) const {
        for (const auto &quad : quads_) {
            os << quad->toString() << std::endl;
        }
        return os;
    }

    OperandPtr Storage::toOperand(std::int32_t index) {
        /*
         *     0x00000000               undefined
         *     0x00000001 - 0x3FFFFFFF  quaternion
         *     0x40000000 - 0x7FFFFFFF  identifier
         *     0x80000000 - 0xBFFFFFFF  constant
         *     0xC0000000 - 0xFFFFFFFF  temp
         */
        OperandPtr operand = nullptr;
        auto i = static_cast<std::uint32_t>(index);
        if (0u < i && i < 0x40000000u) {
            operand = quads_.at(i - 1u);
        } else if (0x40000000u <= i && i < 0x80000000u) {
            operand = ids_.at(i - 0x40000000u);
        } else if (0x80000000u <= i && i < 0xC0000000u) {
            operand = constants_.at(i - 0x80000000u);
        } else if (0xC0000000u <= i && i <= 0xFFFFFFFFu) {
            operand = temps_.at(i - 0xC0000000u);
        }
        return operand;
    }
}