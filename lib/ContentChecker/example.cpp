#include "contentChecker.hpp"

int main(int argc, char* argv[]) {
    FileParser fileParser;

    if (argc < 2 || argc > 4) {
        std::cout << "Usage: parser file.txt [log.txt]\n";
        return 0;
    }

    std::string logFileName = (argc == 3) ? argv[2] : "";

    fileParser.processFile(argv[1], logFileName);

    return 0;
}