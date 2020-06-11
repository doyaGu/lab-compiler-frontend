#ifndef LEXER_LEXER_H_
#define LEXER_LEXER_H_

#include <string>
#include <string_view>
#include <sstream>
#include <fstream>
#include <memory>

#include "StateMachine.h"
#include "Token.h"
#include "TokenTable.h"

namespace lexer {
    using namespace util;
    using namespace symbol;

    class Lexer;
    using LexerPtr = std::shared_ptr<Lexer>;

    class Lexer : public StateMachine {
    public:
        Lexer();

        void setSource(std::string_view filename);

        void nextToken();

        Token getToken() const;

        [[nodiscard]] bool isReady() const;

        [[nodiscard]] bool isFailed() const;

        [[nodiscard]] bool isCompleted() const;

    private:
        enum State : StateID {
            // Lexer State
            IDLE = 0,
            READY,
            START,
            SUCCESS,
            FAILED,
            COMPLETED,
            // Token State
            IDENTIFIER,
            NUMBER,
            STRING,
            OPERATOR,
            // Number State
            INTEGER,
            FRACTION,
            EXPONENT
        };

        STATE_DECLARE(Lexer, Idle)

        STATE_DECLARE(Lexer, Ready)

        STATE_DECLARE(Lexer, Start)

        STATE_DECLARE(Lexer, Success)

        STATE_DECLARE(Lexer, Failed)

        STATE_DECLARE(Lexer, Completed)

        STATE_DECLARE(Lexer, Identifier)

        STATE_DECLARE(Lexer, Number)

        STATE_DECLARE(Lexer, String)

        STATE_DECLARE(Lexer, Operator)

        STATE_DECLARE(Lexer, Integer)

        STATE_DECLARE(Lexer, Fraction)

        STATE_DECLARE(Lexer, Exponent)

        StateMap getStateMap() override {
            static const StateMapRow STATE_MAP[] = {
                    {&Idle},
                    {&Ready},
                    {&Start},
                    {&Success},
                    {&Failed},
                    {&Completed},
                    {&Identifier},
                    {&Number},
                    {&String},
                    {&Operator},
                    {&Integer},
                    {&Fraction},
                    {&Exponent},
            };
            return &STATE_MAP[0];
        }

        void nextChar();

        char lookahead();

        void preprocess();

        void processComment();

        void newToken(SymbolType type, SymbolValue value, const SymbolLocation &location,
                      const std::string &lexeme);

        void newToken(SymbolType type, const SymbolLocation &location,
                      const std::string &lexeme);

        SymbolLocation getLocation() const;

        std::string filename_;
        std::ifstream input_;

        std::string lexeme_;
        char current_char_ = '\0';
        long row_ = 1;
        long column_ = 0;

        // 用于无符号数的识别
        int current_digit_ = 0; // 当前数字
        int integer_digits_ = 0; // 整数累加器
        int fraction_digits_ = 0; // 小数累加器
        int exponent_counter_ = 0; // 指数累加器
        bool exponent_sign_ = true; // 指数符号 [true -> +] [false -> -]
        double real_ = 0.0; // 实数结果

        Token token_;
        SymbolLocation location_;
        TokenTable table_;
    };
}

#endif // LEXER_LEXER_H_
