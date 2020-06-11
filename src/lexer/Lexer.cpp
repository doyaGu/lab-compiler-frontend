#include <utility>
#include <string>

#include "Token.h"
#include "Lexer.h"

#include <spdlog/spdlog.h>

namespace {
    std::shared_ptr<spdlog::logger> logger;

    void initLogger() {
        auto console_sink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
        logger = std::make_shared<spdlog::logger>("lexer", console_sink);
        spdlog::register_logger(logger);

        logger->set_level(spdlog::level::debug);
    }
}

namespace lexer {
    Lexer::Lexer() :
        StateMachine(IDLE) {
        // 初始化日志
        initLogger();
    }

    // 设置源文件
    void Lexer::setSource(std::string_view filename) {
        if (!filename_.empty() || getCurrentState() != IDLE) {
            logger->error("While the lexical analyzer is working, you cannot set a new source file");
        }

        filename_ = std::string(filename);
        input_.open(filename_);
        if (input_.fail()) {
            logger->error("Unable to open: " + filename_);
            std::exit(EXIT_FAILURE);
        }

        logger->debug("Success to open: {}", filename_);
        startup(READY);
    }

    void Lexer::nextToken() {
        // 状态迁移表
        static const StateID TRANSITIONS[] = {
            CANNOT_HAPPEN, // <= IDLE
            START,         // <= READY
            CANNOT_HAPPEN, // <= START
            START,         // <= SUCCESS
            START,         // <= FAILED
            CANNOT_HAPPEN, // <= COMPLETED
            CANNOT_HAPPEN, // <= IDENTIFIER
            CANNOT_HAPPEN, // <= NUMBER
            CANNOT_HAPPEN, // <= STRING
            CANNOT_HAPPEN, // <= OPERATOR
            CANNOT_HAPPEN, // <= INTEGER
            CANNOT_HAPPEN, // <= FRACTION
            CANNOT_HAPPEN, // <= EXPONENT
        };
        startup(TRANSITIONS[getCurrentState()]);
    }

    bool Lexer::isReady() const {
        return getCurrentState() == READY;
    }

    bool Lexer::isFailed() const {
        return getCurrentState() == FAILED;
    }

    bool Lexer::isCompleted() const {
        return getCurrentState() == COMPLETED;
    }

    Token Lexer::getToken() const {
        return token_;
    }

    STATE_DEFINE(Lexer, Idle) {
        // empty
    }

    STATE_DEFINE(Lexer, Ready) {
//        logger->debug("Ready to scan.");
    }

    STATE_DEFINE(Lexer, Start) {
//        logger->debug("Start to scan.");

        nextChar();
        preprocess();

        if (input_.eof()) {
            transit(COMPLETED);
        } else {
            if (std::isalpha(current_char_)) {
                transit(IDENTIFIER);
            } else if (std::isdigit(current_char_) || current_char_ == '.') {
                transit(NUMBER);
            } else if (current_char_ == '\"' || current_char_ == '\'') {
                transit(STRING);
            } else {
                transit(OPERATOR);
            }
        }
    }

    STATE_DEFINE(Lexer, Success) {
        logger->debug("{} Get Token: {}", location_.toString(), token_.toString());
    }

    STATE_DEFINE(Lexer, Failed) {
        logger->error(" {} Unknown Token: {}", location_.toString(), lexeme_);
        newToken(SymbolType::UNKNOWN, location_, lexeme_);
    }

    STATE_DEFINE(Lexer, Completed) {
        logger->debug("Completed.");

        location_ = getLocation();
        newToken(SymbolType::END_OF_FILE, location_, "EOF");

        input_.close();
    }

    STATE_DEFINE(Lexer, Identifier) {
        location_ = getLocation();

        lexeme_.push_back(current_char_);
        while (std::isalnum(lookahead()) || lookahead() == '_') {
            nextChar();
            lexeme_.push_back(current_char_);
        }

        // 查表判断是否为关键字
        auto type = table_.lookup(lexeme_);
        newToken(type, lexeme_, location_, lexeme_);
        transit(SUCCESS);
    }

    STATE_DEFINE(Lexer, Number) {
        location_ = getLocation();

        // 清零
        integer_digits_ = 0;
        fraction_digits_ = 0;
        exponent_counter_ = 0;
        exponent_sign_ = true;
        real_ = 0.0;

        if (current_char_ == '.') {
            transit(FRACTION);
        } else {
            transit(INTEGER);
        }
    }

    STATE_DEFINE(Lexer, String) {
        location_ = getLocation();

        if (current_char_ == '\"') {
            do {
                nextChar();
                lexeme_.push_back(current_char_);
            } while (lookahead() != '\"');

            // 跳过第二个双引号
            nextChar();

            newToken(SymbolType::STRING, lexeme_, location_, lexeme_);
            transit(SUCCESS);
        } else if (current_char_ == '\'') {
            nextChar();
            lexeme_.push_back(current_char_);

            if (lookahead() != '\'') {
                logger->error("{} Character literal should be 1 character.", location_.toString());
                transit(FAILED);
                return;
            }

            // 跳过第二个单引号
            nextChar();

            newToken(SymbolType::CHAR, lexeme_[0], location_, lexeme_);
            transit(SUCCESS);
        }
    }

    STATE_DEFINE(Lexer, Operator) {
        location_ = getLocation();
        lexeme_.push_back(current_char_);

        if (table_.haveToken(lexeme_)) {
            lexeme_.push_back(lookahead());
            if (table_.haveToken(lexeme_)) {
                nextChar();
            } else {
                lexeme_.pop_back();
            }
        } else {
            lexeme_.push_back(lookahead());
            if (!table_.haveToken(lexeme_)) {
                lexeme_.pop_back();
                transit(FAILED);
                return;
            }
            nextChar();
        }

        auto type = table_.lookup(lexeme_);
        newToken(type, location_, lexeme_);
        transit(SUCCESS);
    }

    STATE_DEFINE(Lexer, Integer) {
        lexeme_.push_back(current_char_);
        integer_digits_ = 10 * integer_digits_ + (current_char_ - '0');

        while (std::isdigit(lookahead())) {
            nextChar();
            lexeme_.push_back(current_char_);
            integer_digits_ = 10 * integer_digits_ + (current_char_ - '0');
        }

        if (lookahead() == '.') {
            nextChar();
            transit(FRACTION);
            return;
        } else if (std::tolower(lookahead()) == 'e') {
            nextChar();
            transit(EXPONENT);
            return;
        }

        newToken(SymbolType::INT, integer_digits_, location_, lexeme_);
        transit(SUCCESS);
    }

    STATE_DEFINE(Lexer, Fraction) {
        lexeme_.push_back(current_char_);

        while (std::isdigit(lookahead())) {
            nextChar();
            lexeme_.push_back(current_char_);
            fraction_digits_ = 10 * fraction_digits_ + (current_char_ - '0');
            --exponent_counter_;
        }

        if (tolower(lookahead()) == 'e') {
            nextChar();
            transit(EXPONENT);
            return;
        }

        real_ = integer_digits_ + fraction_digits_ * std::pow(10, exponent_counter_);
        newToken(SymbolType::REAL, real_, location_, lexeme_);
        transit(SUCCESS);
    }

    STATE_DEFINE(Lexer, Exponent) {
        // 读入 E/e
        lexeme_.push_back(current_char_);

        // 暂存当前实数结果
        real_ = integer_digits_ + fraction_digits_ * std::pow(10, exponent_counter_);

        if (lookahead() != '+' && lookahead() != '-' && !std::isdigit(lookahead())) {
            logger->error("{} Exponent part should be + / - or digits.", location_.toString());
            transit(FAILED);
            return;
        }

        if (lookahead() == '+') {
            nextChar();
            lexeme_.push_back(current_char_);
            exponent_sign_ = true;
        } else if (lookahead() == '-') {
            nextChar();
            lexeme_.push_back(current_char_);
            exponent_sign_ = false;
        }

        int counter = 0;
        while (std::isdigit(lookahead())) {
            nextChar();
            lexeme_.push_back(current_char_);

            counter = 10 * counter + (current_char_ - '0');
        }

        if (exponent_sign_) {
            exponent_counter_ += counter;
        } else {
            exponent_counter_ -= counter;
        }

        real_ = real_ * std::pow(10, exponent_counter_);
        newToken(SymbolType::REAL, real_, location_, lexeme_);
        transit(SUCCESS);
    }

    void Lexer::nextChar() {
        current_char_ = input_.get();

        if (current_char_ != '\n') {
            column_++;
        } else {
            row_++;
            column_ = 0;
        }
    }

    char Lexer::lookahead() {
        return input_.peek();
    }

    void Lexer::preprocess() {
        do {
            while (std::isspace(current_char_)) {
                nextChar();
            }
            processComment();

        } while (std::isspace(current_char_));
    }

    void Lexer::processComment() {
        if (current_char_ == '/' && lookahead() == '/') {
            location_ = getLocation();

            // 跳过注释符 "//"
            nextChar();
            nextChar();

            while (current_char_ != '\n') {
                // 跳过注释内容
                nextChar();

                // 如果到达文件结尾
                if (input_.eof())
                    break;
            }

            logger->debug("{} Skipping the comment.", location_.toString());
        }
    }

    void Lexer::newToken(SymbolType type, SymbolValue value, const SymbolLocation &location, const std::string &lexeme) {
        token_ = Token(type, std::move(value), location, lexeme);
        lexeme_.clear();
    }

    void Lexer::newToken(SymbolType type, const SymbolLocation &location, const std::string &lexeme) {
        newToken(type, nullptr, location, lexeme);
    }

    SymbolLocation Lexer::getLocation() const {
        return SymbolLocation(filename_, row_, column_);
    }
}