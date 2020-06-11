#ifndef PARSER_PARSER_TABLE_H
#define PARSER_PARSER_TABLE_H

#include <map>
#include <cstdint>

#include "SymbolType.h"
#include "ParserAction.h"
#include "GrammarProductionTable.h"

namespace parser {
    using namespace symbol;
    using namespace grammar;
    using ParserStateID = uint8_t;

    class ParserTable {
    public:
        using ActionTable = std::map<SymbolType, ParserAction>;
        using GotoTable = std::map<SymbolType, ParserStateID>;

        ParserTable();

        [[nodiscard]] bool haveAction(ParserStateID id, SymbolType type) const;

        [[nodiscard]] ParserAction getAction(ParserStateID id, SymbolType type) const;

        [[nodiscard]] ParserStateID getNextStateID(ParserStateID id, SymbolType type) const;

        [[nodiscard]] const GrammarProduction &getProduction(int index) const;

        [[nodiscard]] const std::string &getError(int index) const;

    private:
        std::map<ParserStateID, ActionTable> actions_;
        std::map<ParserStateID, GotoTable> transitions_;
        GrammarProductionTable productions_;
        std::vector<std::string> errors_;
    };
}

#endif //PARSER_PARSER_TABLE_H
