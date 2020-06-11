#include "Quaternion.h"

#include <utility>

namespace inter {
    int Quaternion::nxq_ = 0;

    Quaternion::Quaternion(Operator op, OperandPtr arg1, OperandPtr arg2, OperandPtr result) :
        Operand(SymbolType::QUAD, nxq_++),
        op_(std::move(op)),
        arg1_(std::move(arg1)),
        arg2_(std::move(arg2)),
        result_(std::move(result)) {}

    std::string Quaternion::toString() const {
        return std::string("(" + op_.toString() + ","
                           + arg1_->toString() + ","
                           + arg2_->toString() + ","
                           + result_->toString() + ")"
        );
    }
}


