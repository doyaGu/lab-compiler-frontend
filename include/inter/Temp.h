#ifndef INTER_TEMP_H
#define INTER_TEMP_H

#include <memory>

#include "Operand.h"

namespace inter {
    class Temp;
    using TempPtr = std::shared_ptr<Temp>;

    class Temp : public Operand {
    public:
        Temp() : Temp(SymbolType::TEMP, nullptr) {}

        explicit Temp(SymbolType type, SymbolValue value);

        void set(SymbolValue value);

        [[nodiscard]] std::string toString() const override;

    private:
        int index_;

        static int nxt_;
    };
}

#endif //INTER_TEMP_H
