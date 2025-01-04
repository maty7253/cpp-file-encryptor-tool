#pragma once
#include <string>
#include <memory>
#include <vector>
#include "EncryptionStrategies.hpp"
#include "ProgressBar.hpp"
#include "HashVerifier.hpp"

class FileEncryptor {
private:
    std::shared_ptr<IEncryptionStrategy> strategy;
    std::string key;
    
    std::vector<unsigned char> readFile(const std::string& filename, ProgressBar& progress);
    void writeFile(const std::string& filename, const std::vector<unsigned char>& data);
    bool isFileExists(const std::string& filename);

public:
    FileEncryptor(std::shared_ptr<IEncryptionStrategy> strategy, const std::string& key);
    ~FileEncryptor();
    
    void encryptFile(const std::string& inputFile, const std::string& outputFile);
    void decryptFile(const std::string& inputFile, const std::string& outputFile);
    
    static std::shared_ptr<IEncryptionStrategy> createStrategy(const std::string& type);
};