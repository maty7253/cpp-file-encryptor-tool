#pragma once
#include <vector>
#include <string>
#include <memory>
#include <openssl/aes.h>
#include <openssl/evp.h>

class IEncryptionStrategy {
public:
    virtual ~IEncryptionStrategy() = default;
    virtual std::vector<unsigned char> encrypt(const std::vector<unsigned char>& data, const std::string& key) = 0;
    virtual std::vector<unsigned char> decrypt(const std::vector<unsigned char>& data, const std::string& key) = 0;
    virtual std::string getName() const = 0;
};

class XORStrategy : public IEncryptionStrategy {
public:
    std::vector<unsigned char> encrypt(const std::vector<unsigned char>& data, const std::string& key) override;
    std::vector<unsigned char> decrypt(const std::vector<unsigned char>& data, const std::string& key) override;
    std::string getName() const override { return "XOR"; }
};

class AESStrategy : public IEncryptionStrategy {
private:
    static const int KEY_SIZE = 32; // 256 bits
    static const int BLOCK_SIZE = 16; // 128 bits
    
    std::vector<unsigned char> generateIV();
    std::vector<unsigned char> deriveKey(const std::string& password);

public:
    std::vector<unsigned char> encrypt(const std::vector<unsigned char>& data, const std::string& key) override;
    std::vector<unsigned char> decrypt(const std::vector<unsigned char>& data, const std::string& key) override;
    std::string getName() const override { return "AES-256"; }
};