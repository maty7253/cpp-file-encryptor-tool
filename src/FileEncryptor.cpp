#include "FileEncryptor.hpp"
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <openssl/err.h>
#include <openssl/ssl.h>

FileEncryptor::FileEncryptor(std::shared_ptr<IEncryptionStrategy> strategy, const std::string& key)
    : strategy(strategy), key(key) {
    if (!strategy) throw std::invalid_argument("Strategy cannot be null");
    if (key.empty()) throw std::invalid_argument("Key cannot be empty");
    
    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
}

FileEncryptor::~FileEncryptor() {
    // Cleanup OpenSSL
    EVP_cleanup();
    ERR_free_strings();
}

bool FileEncryptor::isFileExists(const std::string& filename) {
    if (filename.empty()) {
        throw std::invalid_argument("Filename cannot be empty");
    }
    return std::filesystem::exists(filename);
}

std::vector<unsigned char> FileEncryptor::readFile(const std::string& filename, ProgressBar& progress) {
    if (!isFileExists(filename)) {
        throw std::runtime_error("File does not exist: " + filename);
    }
    
    auto fileSize = std::filesystem::file_size(filename);
    if (fileSize > std::numeric_limits<std::size_t>::max()) {
        throw std::runtime_error("File is too large to process");
    }
    
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open input file: " + filename);
    }
    
    std::vector<unsigned char> buffer(fileSize);
    
    size_t bytesRead = 0;
    const size_t chunkSize = 8192;
    
    while (bytesRead < fileSize) {
        if (file.fail()) {
            throw std::runtime_error("Error occurred while reading file");
        }
        
        size_t toRead = std::min(chunkSize, fileSize - bytesRead);
        file.read(reinterpret_cast<char*>(buffer.data() + bytesRead), toRead);
        bytesRead += toRead;
        progress.update(bytesRead);
    }
    
    return buffer;
}

void FileEncryptor::writeFile(const std::string& filename, const std::vector<unsigned char>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Unable to create output file: " + filename);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

void FileEncryptor::encryptFile(const std::string& inputFile, const std::string& outputFile) {
    if (!isFileExists(inputFile)) {
        throw std::runtime_error("Input file does not exist: " + inputFile);
    }
    
    std::cout << "Starting encryption using " << strategy->getName() << " algorithm..." << std::endl;
    
    auto fileSize = std::filesystem::file_size(inputFile);
    ProgressBar progress(fileSize, "Reading");
    
    auto data = readFile(inputFile, progress);
    progress.finish();
    
    std::cout << "Calculating input file hash..." << std::endl;
    std::string inputHash = HashVerifier::calculateSHA256(data);
    
    std::cout << "Encrypting data..." << std::endl;
    auto encryptedData = strategy->encrypt(data, key);
    
    std::cout << "Writing encrypted file..." << std::endl;
    writeFile(outputFile, encryptedData);
    
    std::cout << "Encryption completed successfully!" << std::endl;
    std::cout << "Input file hash: " << inputHash << std::endl;
}

void FileEncryptor::decryptFile(const std::string& inputFile, const std::string& outputFile) {
    if (!isFileExists(inputFile)) {
        throw std::runtime_error("Input file does not exist: " + inputFile);
    }
    
    std::cout << "Starting decryption using " << strategy->getName() << " algorithm..." << std::endl;
    
    auto fileSize = std::filesystem::file_size(inputFile);
    ProgressBar progress(fileSize, "Reading");
    
    auto encryptedData = readFile(inputFile, progress);
    progress.finish();
    
    std::cout << "Decrypting data..." << std::endl;
    auto decryptedData = strategy->decrypt(encryptedData, key);
    
    std::cout << "Writing decrypted file..." << std::endl;
    writeFile(outputFile, decryptedData);
    
    std::cout << "Calculating decrypted file hash..." << std::endl;
    std::string outputHash = HashVerifier::calculateSHA256(decryptedData);
    
    std::cout << "Decryption completed successfully!" << std::endl;
    std::cout << "Decrypted file hash: " << outputHash << std::endl;
}

std::shared_ptr<IEncryptionStrategy> FileEncryptor::createStrategy(const std::string& type) {
    if (type == "xor") return std::make_shared<XORStrategy>();
    if (type == "aes") return std::make_shared<AESStrategy>();
    throw std::invalid_argument("Unknown encryption strategy: " + type);
}