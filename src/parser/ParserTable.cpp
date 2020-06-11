#include "ParserTable.h"

namespace parser {
    ParserTable::ParserTable() {
        /*
         *        STATE	ACTION                          GOTO
         *              (	)   +	-	*	/	i	#	E	T	F
         *        0     S4	F1	F2	F3	F4	F5	S5	F6	1	2	3
         *        1             S6	S7				Acc
         *        2	    	R3	R3	R3	S8	S9		R3
         *        3     	R6	R6	R6	R6	R6		R6
         *        4     S4						S5		10	2	3
         *        5         R8	R8	R8	R8	R8		R8
         *        6     S4						S5			11	3
         *        7     S4						S5			12	3
         *        8     S4						S5				13
         *        9     S4						S5				14
         *        10        S15	S6	S7
         *        11        R1	R1	R1	S8	S9		R1
         *        12        R2	R2	R2	S8	S9		R2
         *        13        R4	R4	R4	R4	R4		R4
         *        14        R5	R5	R5	R5	R5		R5
         *        15		R7	R7	R7	R7	R7		R7
         */

        actions_ = {
            {
                0, // STATE 0
                {
                    {SymbolType::LPAREN, {ParserActionType::SHIFT,  4}},
                    {SymbolType::RPAREN, {ParserActionType::FAIL, 1}},
                    {SymbolType::PL, {ParserActionType::FAIL, 2}},
                    {SymbolType::MI, {ParserActionType::FAIL, 3}},
                    {SymbolType::MU, {ParserActionType::FAIL,  4}},
                    {SymbolType::DI, {ParserActionType::FAIL,  5}},
                    {SymbolType::OPERAND, {ParserActionType::SHIFT, 5}},
                    {SymbolType::END_OF_FILE, {ParserActionType::FAIL, 6}}
                }
            },
            {
                1,  // STATE 1
                {
                    {SymbolType::PL,     {ParserActionType::SHIFT,  6}},
                    {SymbolType::MI,      {ParserActionType::SHIFT,  7}},
                    {SymbolType::END_OF_FILE, {ParserActionType::ACCEPT, 1}}
                }
            },
            {
                2,  // STATE 2
                {
                    {SymbolType::RPAREN, {ParserActionType::REDUCE, 3}},
                    {SymbolType::PL,      {ParserActionType::REDUCE, 3}},
                    {SymbolType::MI,          {ParserActionType::REDUCE, 3}},
                    {SymbolType::MU, {ParserActionType::SHIFT,  8}},
                    {SymbolType::DI, {ParserActionType::SHIFT,  9}},
                    {SymbolType::END_OF_FILE, {ParserActionType::REDUCE, 3}}
                }
            },
            {
                3,  // STATE 3
                {
                    {SymbolType::RPAREN, {ParserActionType::REDUCE, 6}},
                    {SymbolType::PL,      {ParserActionType::REDUCE, 6}},
                    {SymbolType::MI,          {ParserActionType::REDUCE, 6}},
                    {SymbolType::MU, {ParserActionType::REDUCE, 6}},
                    {SymbolType::DI, {ParserActionType::REDUCE, 6}},
                    {SymbolType::END_OF_FILE, {ParserActionType::REDUCE, 6}}
                }
            },
            {
                4,  // STATE 4
                {
                    {SymbolType::LPAREN, {ParserActionType::SHIFT,  4}},
                    {SymbolType::OPERAND, {ParserActionType::SHIFT,  5}}
                }
            },
            {
                5,  // STATE 5
                {
                    {SymbolType::RPAREN, {ParserActionType::REDUCE, 8}},
                    {SymbolType::PL,      {ParserActionType::REDUCE, 8}},
                    {SymbolType::MI,          {ParserActionType::REDUCE, 8}},
                    {SymbolType::MU, {ParserActionType::REDUCE, 8}},
                    {SymbolType::DI, {ParserActionType::REDUCE, 8}},
                    {SymbolType::END_OF_FILE, {ParserActionType::REDUCE, 8}}
                }
            },
            {
                6,  // STATE 6
                {
                    {SymbolType::LPAREN, {ParserActionType::SHIFT,  4}},
                    {SymbolType::OPERAND, {ParserActionType::SHIFT,  5}}
                }
            },
            {
                7,  // STATE 7
                {
                    {SymbolType::LPAREN, {ParserActionType::SHIFT,  4}},
                    {SymbolType::OPERAND, {ParserActionType::SHIFT,  5}}
                }
            },
            {
                8,  // STATE 8
                {
                    {SymbolType::LPAREN, {ParserActionType::SHIFT,  4}},
                    {SymbolType::OPERAND, {ParserActionType::SHIFT,  5}}
                }
            },
            {
                9,  // STATE 9
                {
                    {SymbolType::LPAREN, {ParserActionType::SHIFT,  4}},
                    {SymbolType::OPERAND, {ParserActionType::SHIFT,  5}}
                }
            },
            {
                10,  // STATE 10
                {
                    {SymbolType::RPAREN, {ParserActionType::SHIFT,  15}},
                    {SymbolType::PL,      {ParserActionType::SHIFT,  6}},
                    {SymbolType::MI,          {ParserActionType::SHIFT,  7}}
                }
            },
            {
                11,  // STATE 11
                {
                    {SymbolType::RPAREN, {ParserActionType::REDUCE, 1}},
                    {SymbolType::PL,      {ParserActionType::REDUCE, 1}},
                    {SymbolType::MI,          {ParserActionType::REDUCE, 1}},
                    {SymbolType::MU, {ParserActionType::SHIFT,  8}},
                    {SymbolType::DI, {ParserActionType::SHIFT,  9}},
                    {SymbolType::END_OF_FILE, {ParserActionType::REDUCE, 1}}
                }
            },
            {
                12,  // STATE 12
                {
                    {SymbolType::RPAREN, {ParserActionType::REDUCE, 2}},
                    {SymbolType::PL,      {ParserActionType::REDUCE, 2}},
                    {SymbolType::MI,          {ParserActionType::REDUCE, 2}},
                    {SymbolType::MU, {ParserActionType::SHIFT,  8}},
                    {SymbolType::DI, {ParserActionType::SHIFT,  9}},
                    {SymbolType::END_OF_FILE, {ParserActionType::REDUCE, 2}}
                }
            },
            {
                13,  // STATE 13
                {
                    {SymbolType::RPAREN, {ParserActionType::REDUCE, 4}},
                    {SymbolType::PL,      {ParserActionType::REDUCE, 4}},
                    {SymbolType::MI,          {ParserActionType::REDUCE, 4}},
                    {SymbolType::MU, {ParserActionType::REDUCE, 4}},
                    {SymbolType::DI, {ParserActionType::REDUCE, 4}},
                    {SymbolType::END_OF_FILE, {ParserActionType::REDUCE, 4}}
                }
            },
            {
                14,  // STATE 14
                {
                    {SymbolType::RPAREN, {ParserActionType::REDUCE, 5}},
                    {SymbolType::PL,      {ParserActionType::REDUCE, 5}},
                    {SymbolType::MI,          {ParserActionType::REDUCE, 5}},
                    {SymbolType::MU, {ParserActionType::REDUCE, 5}},
                    {SymbolType::DI, {ParserActionType::REDUCE, 5}},
                    {SymbolType::END_OF_FILE, {ParserActionType::REDUCE, 5}}
                }
            },
            {
                15,  // STATE 15
                {
                    {SymbolType::RPAREN, {ParserActionType::REDUCE, 7}},
                    {SymbolType::PL,      {ParserActionType::REDUCE, 7}},
                    {SymbolType::MI,          {ParserActionType::REDUCE, 7}},
                    {SymbolType::MU, {ParserActionType::REDUCE, 7}},
                    {SymbolType::DI, {ParserActionType::REDUCE, 7}},
                    {SymbolType::END_OF_FILE, {ParserActionType::REDUCE, 7}}
                }
            },
        };

        transitions_ = {
            {
                0,  // STATE 0
                {
                    {SymbolType::EXPR,   1},
                    {SymbolType::TERM,   2},
                    {SymbolType::FACTOR, 3},
                }
            },
            {
                4,  // STATE 4
                {
                    {SymbolType::EXPR,   10},
                    {SymbolType::TERM,   2},
                    {SymbolType::FACTOR, 3},
                }
            },
            {
                6,  // STATE 6
                {
                    {SymbolType::TERM,   11},
                    {SymbolType::FACTOR, 3},
                }
            },
            {
                7,  // STATE 7
                {
                    {SymbolType::TERM,   12},
                    {SymbolType::FACTOR, 3}
                }
            },
            {
                8,  // STATE 8
                {
                    {SymbolType::FACTOR, 13}
                }
            },
            {
                9,  // STATE 9
                {
                    {SymbolType::FACTOR, 14}
                }
            },
        };

        errors_ = {
            "Unknown error happened.",
            "Expression cannot start with ')'.",
            "Expression cannot start with '+'.",
            "Expression cannot start with '-'.",
            "Expression cannot start with '*'.",
            "Expression cannot start with '/'.",
            "Expression cannot be empty."
        };
    }

    bool ParserTable::haveAction(ParserStateID id, SymbolType type) const {
        auto outer = actions_.find(id);
        if (outer != actions_.end()) {
            const auto &table = outer->second;
            auto inner = table.find(type);
            return inner != table.end();
        }
        return false;
    }

    ParserAction ParserTable::getAction(ParserStateID id, SymbolType type) const {
        ParserAction action{ParserActionType::FAIL, 0};

        auto t = type;
        if (type == SymbolType::ID ||
            type == SymbolType::INT ||
            type == SymbolType::REAL) {
            t = SymbolType::OPERAND;
        }

        auto outer = actions_.find(id);
        if (outer != actions_.end()) {
            const auto &table = outer->second;
            auto inner = table.find(t);
            if (inner != table.end()) {
                action = inner->second;
            }
        }

        return action;
    }

    ParserStateID ParserTable::getNextStateID(ParserStateID id, SymbolType type) const {
        auto iter1 = transitions_.find(id);
        if (iter1 != transitions_.end()) {
            const auto &table = iter1->second;
            auto iter2 = table.find(type);
            if (iter2 != table.end()) {
                return iter2->second;
            }
        }
        return id;
    }

    const GrammarProduction &ParserTable::getProduction(int index) const {
        return productions_.lookup(index);
    }

    const std::string &ParserTable::getError(int index) const {
        return errors_.at(index);
    }
}
