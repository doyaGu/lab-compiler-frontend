#ifndef INTER_STORAGE_H
#define INTER_STORAGE_H

#include <iostream>
#include <cstdint>
#include <string>
#include <vector>

#include "Identifier.h"
#include "Temp.h"
#include "Variable.h"
#include "Constant.h"
#include "Quaternion.h"

namespace inter {
    class Storage {
    public:
        Storage(Storage const &rhs) = delete;

        Storage &operator=(Storage const &) = delete;

        [[nodiscard]] std::int32_t lookup(const std::string &name) const;

        std::int32_t enter(const std::string &name);

        std::int32_t entry(const std::string &name);

        std::int32_t entry(const SymbolPtr &name);

        std::int32_t gen(SymbolType op, std::int32_t arg1, std::int32_t arg2, std::int32_t result);

        std::int32_t newConstant(SymbolType type, const SymbolValue& value);

        std::int32_t newTemp();

        std::ostream &printQuaternions(std::ostream& os) const;

        static Storage &instance() {
            static Storage singleton;
            return singleton;
        }

    private:
        Storage();

        ~Storage() = default;

        OperandPtr toOperand(std::int32_t index);

        std::vector<IdentifierPtr> ids_;
        std::vector<TempPtr> temps_;
        std::vector<ConstantPtr > constants_;
        std::vector<QuaternionPtr> quads_;
    };
}

#endif //INTER_STORAGE_H
