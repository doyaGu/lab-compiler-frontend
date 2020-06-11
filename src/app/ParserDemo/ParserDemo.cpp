#include <iostream>
#include <memory>

#include "Lexer.h"
#include "Parser.h"

using lexer::Lexer;
using parser::Parser;

int main(int argc, char *argv[]) {
    auto input_filename = (argv[1]) ? argv[1] : "in.txt";

    auto scanner = std::make_shared<Lexer>();
    scanner->setSource(input_filename);

    auto parser = std::make_shared<Parser>();
    parser->setLexer(scanner);

    while (true) {
        parser->parse();
        if (parser->isCompleted()) {
            std::cout << "RIGHT" << std::endl;
            break;
        } else if (parser->isFailed()) {
            std::cout << "ERROR" << std::endl;
            break;
        }
    }

    return 0;
}
