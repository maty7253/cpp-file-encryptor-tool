#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

class FileEncryptor {
private:
    std::string key;

    bool isFileExists(const std::string& filename) {
        std::ifstream file(filename);
        return file.good();
    }

    std::vector<char> readFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Unable to open input file: " + filename);
        }

        return std::vector<char>(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>()
        );
    }

    void writeFile(const std::string& filename, const std::vector<char>& data) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Unable to create output file: " + filename);
        }

        file.write(data.data(), data.size());
    }

    std::vector<char> processData(const std::vector<char>& data) {
        std::vector<char> result(data.size());
        for (size_t i = 0; i < data.size(); i++) {
            result[i] = data[i] ^ key[i % key.length()];
        }
        return result;
    }

public:
    FileEncryptor(const std::string& encryptionKey) : key(encryptionKey) {
        if (key.empty()) {
            throw std::invalid_argument("Encryption key cannot be empty");
        }
    }

    void encryptFile(const std::string& inputFile, const std::string& outputFile) {
        try {
            if (!isFileExists(inputFile)) {
                throw std::runtime_error("Input file does not exist: " + inputFile);
            }

            std::vector<char> data = readFile(inputFile);
            std::vector<char> encryptedData = processData(data);
            writeFile(outputFile, encryptedData);

            std::cout << "File encrypted successfully!" << std::endl;
            std::cout << "Output file: " << outputFile << std::endl;

        } catch (const std::exception& e) {
            throw std::runtime_error("Encryption failed: " + std::string(e.what()));
        }
    }

    void decryptFile(const std::string& inputFile, const std::string& outputFile) {
        try {
            if (!isFileExists(inputFile)) {
                throw std::runtime_error("Input file does not exist: " + inputFile);
            }

            std::vector<char> data = readFile(inputFile);
            std::vector<char> decryptedData = processData(data);
            writeFile(outputFile, decryptedData);

            std::cout << "File decrypted successfully!" << std::endl;
            std::cout << "Output file: " << outputFile << std::endl;

        } catch (const std::exception& e) {
            throw std::runtime_error("Decryption failed: " + std::string(e.what()));
        }
    }
};

void printUsage() {
    std::cout << "Usage: " << std::endl;
    std::cout << "  Encrypt: program -e <input_file> <output_file> <key>" << std::endl;
    std::cout << "  Decrypt: program -d <input_file> <output_file> <key>" << std::endl;
}

int main(int argc, char* argv[]) {
    try {
        if (argc != 5) {
            printUsage();
            return 1;
        }

        std::string operation = argv[1];
        std::string inputFile = argv[2];
        std::string outputFile = argv[3];
        std::string key = argv[4];

        FileEncryptor encryptor(key);

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
