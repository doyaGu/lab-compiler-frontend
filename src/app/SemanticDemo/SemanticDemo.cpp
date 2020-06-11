#include <iostream>
#include <memory>

#include "Lexer.h"
#include "Parser.h"
#include "Storage.h"

using lexer::Lexer;
using parser::Parser;
using inter::Storage;

int main(int argc, char *argv[]) {
    auto input_filename = (argv[1]) ? argv[1] : "in.txt";
    auto output_filename = (argv[1] && argv[2]) ? argv[2] : "out.quad";

    auto scanner = std::make_shared<Lexer>();
    scanner->setSource(input_filename);

    auto parser = std::make_shared<Parser>();
    parser->setLexer(scanner);

    std::ofstream output(output_filename);
    if (output.fail()) {
        std::cerr << "Unable to create an output file." << std::endl;
    }

    while (true) {
        parser->parse();
        if (parser->isCompleted()) {
            std::cout << "RIGHT" << std::endl;
            Storage::instance().printQuaternions(output);
            break;
        } else if (parser->isFailed()) {
            std::cout << "ERROR" << std::endl;
            break;
        }
    }

    return 0;
}
