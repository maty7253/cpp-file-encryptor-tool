#include "FileEncryptor.hpp"
#include <iostream>

void printUsage() {
    std::cout << "Usage: " << std::endl;
    std::cout << "  Encrypt: program -e <algorithm> <input_file> <output_file> <key>" << std::endl;
    std::cout << "  Decrypt: program -d <algorithm> <input_file> <output_file> <key>" << std::endl;
    std::cout << "Algorithms: xor, aes" << std::endl;
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 6) {
            printUsage();
            return 1;
        }

        std::string operation = argv[1];
        std::string algorithm = argv[2];
        std::string inputFile = argv[3];
        std::string outputFile = argv[4];
        std::string key = argv[5];

        auto strategy = FileEncryptor::createStrategy(algorithm);
        FileEncryptor encryptor(strategy, key);

        if (operation == "-e") {
            encryptor.encryptFile(inputFile, outputFile);
        } else if (operation == "-d") {
            encryptor.decryptFile(inputFile, outputFile);
        } else {
            std::cout << "Invalid operation. Use -e for encrypt or -d for decrypt." << std::endl;
            printUsage();
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}