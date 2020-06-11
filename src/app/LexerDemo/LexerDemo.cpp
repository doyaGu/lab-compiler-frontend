#include <iostream>
#include <memory>

#include "Lexer.h"

using namespace lexer;

int main(int argc, char *argv[]) {
    auto input_filename = (argv[1]) ? argv[1] : "in.txt";
    auto output_filename = (argv[1] && argv[2]) ? argv[2] : "out.txt";

    auto scanner = std::make_shared<Lexer>();
    scanner->setSource(input_filename);

    std::ofstream output(output_filename);
    if (output.fail()) {
        std::cerr << "Unable to create an output file." << std::endl;
    }

    while (!scanner->isCompleted()) {
        scanner->nextToken();
        auto token = scanner->getToken();
        output << token.toString() << std::endl;
    }
    output.close();

    return 0;
}
