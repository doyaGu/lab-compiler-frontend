#ifndef GRAMMAR_GRAMMAR_PRODUCTION_TABLE_H
#define GRAMMAR_GRAMMAR_PRODUCTION_TABLE_H

#include <vector>

#include "GrammarProduction.h"

namespace grammar {
    class GrammarProductionTable {
    public:
        GrammarProductionTable();

        [[nodiscard]] const GrammarProduction &lookup(int index) const;

    private:
        std::vector<GrammarProduction> table_;
    };
}

#endif //GRAMMAR_GRAMMAR_PRODUCTION_TABLE_H
