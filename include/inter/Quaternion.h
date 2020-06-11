#ifndef INTER_QUATERNION_H
#define INTER_QUATERNION_H

#include <tuple>
#include <utility>
#include <string>
#include <memory>
#include <cstdint>

#include "Operator.h"
#include "Operand.h"

namespace inter {
    class Quaternion;
    using QuaternionPtr = std::shared_ptr<Quaternion>;

    class Quaternion : public Operand {
    public:
        Quaternion(Operator op, OperandPtr arg1, OperandPtr arg2, OperandPtr result);

        [[nodiscard]] std::string toString() const override;

    private:
        Operator op_;
        OperandPtr arg1_;
        OperandPtr arg2_;
        OperandPtr result_;

        static int nxq_;
    };
};

#endif //INTER_QUATERNION_H
