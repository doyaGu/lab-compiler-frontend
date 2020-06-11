#include "Parser.h"

#include "ParserActionType.h"

#include <spdlog/spdlog.h>

namespace {
    std::shared_ptr<spdlog::logger> logger;

    void initLogger() {
        auto console_sink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
        logger = std::make_shared<spdlog::logger>("parser", console_sink);
        spdlog::register_logger(logger);

        logger->set_level(spdlog::level::debug);
    }
}

namespace parser {
    Parser::Parser() :
        StateMachine(IDLE) {
        // 初始化日志
        initLogger();
    }

    void Parser::setLexer(const std::shared_ptr<lexer::Lexer> &lexer) {
        if (!lexer->isReady()) {
            logger->error("Only the lexer that is ready accepted.");
            return;
        }
        lexer_ = lexer;

        if (getCurrentState() == IDLE) {
            logger->debug("Success to bind to a lexical analyzer.");
            startup(READY);
        } else {
            logger->error("While the grammar parser is working, you cannot set new lexical analyzer.");
        }
    }

    void Parser::parse() {
        // 状态迁移表
        static const StateID TRANSITIONS[] = {
            CANNOT_HAPPEN, // <= IDLE
            START,         // <= READY
            CANNOT_HAPPEN, // <= START
            START,         // <= SUCCESS
            CANNOT_HAPPEN, // <= FAILED
            CANNOT_HAPPEN, // <= COMPLETED
            CANNOT_HAPPEN, // <= SHIFT
            CANNOT_HAPPEN, // <= REDUCE
            CANNOT_HAPPEN  // <= ACCEPT
        };
        startup(TRANSITIONS[getCurrentState()]);
    }

    bool Parser::isReady() const {
        return getCurrentState() == READY;
    }

    bool Parser::isFailed() const {
        return getCurrentState() == FAILED;
    }

    bool Parser::isCompleted() const {
        return getCurrentState() == COMPLETED;
    }

    STATE_DEFINE(Parser, Idle) {
        // empty
    }

    STATE_DEFINE(Parser, Ready) {
        logger->debug("Ready to parse.");
        stack_.push(0);
        symbols_.push(std::make_shared<GrammarSymbol>());
        nextGrammarSymbol();
    }

    STATE_DEFINE(Parser, Start) {
        logger->debug("Start to parse.");

        auto id = stack_.top();
        auto type = grammar_symbol_->getType();

        logger->debug("Stack TOP: {}", id);
        logger->debug("Current Symbol: {}", symbols_.top()->toString());
        logger->debug("Next Symbol: {}", grammar_symbol_->toString());

        if (!table_.haveAction(id, type)) {
            transit(FAILED);
        }

        action_ = table_.getAction(id, type);
        logger->debug("Current Action: {} Target: {}", action_.toString(), action_.target);

        switch (action_.type) {
            case ParserActionType::SHIFT:
                transit(SHIFT);
                break;
            case ParserActionType::REDUCE:
                transit(REDUCE);
                break;
            case ParserActionType::ACCEPT:
                transit(ACCEPT);
                break;
            case ParserActionType::FAIL:
                transit(FAILED);
                break;
        }
    }

    STATE_DEFINE(Parser, Success) {
        logger->debug("Success to parse: {}", symbols_.top()->toString());
    }

    STATE_DEFINE(Parser, Failed) {
        logger->error("Failed to parse: {}", table_.getError(action_.target));
    }

    STATE_DEFINE(Parser, Completed) {
        logger->debug("Completed.");
    }

    STATE_DEFINE(Parser, Shift) {
        logger->debug("Shifted {}, state: {} -> {}", grammar_symbol_->getName(), stack_.top(), action_.target);

        symbols_.push(grammar_symbol_);
        stack_.push(action_.target);

        nextGrammarSymbol();

        transit(SUCCESS);
    }

    STATE_DEFINE(Parser, Reduce) {
        auto production = table_.getProduction(action_.target);
        logger->debug("Reduced by: {}", production.getDescription());

        std::vector<GrammarSymbolPtr> body;
        for (auto i = 0; i < production.getBodySize(); ++i) {
            stack_.pop();
            body.insert(body.begin(), symbols_.top());
            symbols_.pop();
        }

//        logger->debug("Before: [");
//        for (auto &sym : body) {
//            logger->debug("\t{},", sym->toString());
//        }
//        logger->debug("]");

        auto grammar_symbol = production.reduce(body);
//        logger->debug("After: [ {} ]", grammar_symbol->toString());

        stack_.push(table_.getNextStateID(stack_.top(), grammar_symbol->getType()));
        symbols_.push(grammar_symbol);

        transit(SUCCESS);
    }

    STATE_DEFINE(Parser, Accept) {
        logger->debug("Accept.");
        transit(COMPLETED);
    }

    void Parser::nextGrammarSymbol() {
        lexer_->nextToken();
        auto token = lexer_->getToken();

        if (lexer_->isFailed()) {
            logger->error("Parsing an unknown token: {}", token.toString());
        }

        grammar_symbol_ = std::make_shared<GrammarSymbol>(token);
    }


}
