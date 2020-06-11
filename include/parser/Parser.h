#ifndef PARSER_PARSER_H
#define PARSER_PARSER_H

#include <vector>
#include <stack>
#include <cstdint>

#include "StateMachine.h"
#include "Token.h"
#include "Lexer.h"
#include "ParserTable.h"
#include "GrammarSymbol.h"

namespace parser {
    using namespace util;
    using namespace symbol;
    using namespace grammar;
    using namespace lexer;

    using ParserStateID = uint8_t;

    class Parser : public StateMachine {
    public:
        Parser();

        void setLexer(const std::shared_ptr<Lexer> &lexer);

        void parse();

        [[nodiscard]] bool isReady() const;

        [[nodiscard]] bool isFailed() const;

        [[nodiscard]] bool isCompleted() const;

    private:
        enum State : StateID {
            // Parser State
            IDLE = 0,
            READY,
            START,
            SUCCESS,
            FAILED,
            COMPLETED,
            SHIFT,
            REDUCE,
            ACCEPT,
        };

        STATE_DECLARE(Parser, Idle)

        STATE_DECLARE(Parser, Ready)

        STATE_DECLARE(Parser, Start)

        STATE_DECLARE(Parser, Success)

        STATE_DECLARE(Parser, Failed)

        STATE_DECLARE(Parser, Completed)

        STATE_DECLARE(Parser, Shift)

        STATE_DECLARE(Parser, Reduce)

        STATE_DECLARE(Parser, Accept)

        StateMap getStateMap() override {
            static const StateMapRow STATE_MAP[] = {
                {&Idle},
                {&Ready},
                {&Start},
                {&Success},
                {&Failed},
                {&Completed},
                {&Shift},
                {&Reduce},
                {&Accept},
            };
            return &STATE_MAP[0];
        }

        void nextGrammarSymbol();

        LexerPtr lexer_;

        GrammarSymbolPtr grammar_symbol_;
        std::stack<GrammarSymbolPtr> symbols_;
        std::stack<ParserStateID> stack_;

        ParserAction action_;
        ParserTable table_;
    };
}

#endif //PARSER_PARSER_H
