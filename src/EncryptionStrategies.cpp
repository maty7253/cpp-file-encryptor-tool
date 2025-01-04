#include "EncryptionStrategies.hpp"
#include <stdexcept>
#include <openssl/rand.h>
#include <openssl/evp.h>

std::vector<unsigned char> XORStrategy::encrypt(const std::vector<unsigned char>& data, const std::string& key) {
    std::vector<unsigned char> result(data.size());
    for (size_t i = 0; i < data.size(); i++) {
        result[i] = data[i] ^ key[i % key.length()];
    }
    return result;
}

std::vector<unsigned char> XORStrategy::decrypt(const std::vector<unsigned char>& data, const std::string& key) {
    return encrypt(data, key); // XOR encryption is symmetric
}

std::vector<unsigned char> AESStrategy::generateIV() {
    std::vector<unsigned char> iv(BLOCK_SIZE);
    if (RAND_bytes(iv.data(), BLOCK_SIZE) != 1) {
        throw std::runtime_error("Failed to generate IV");
    }
    return iv;
}

std::vector<unsigned char> AESStrategy::deriveKey(const std::string& password) {
    std::vector<unsigned char> key(KEY_SIZE);
    if (EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), nullptr,
                       reinterpret_cast<const unsigned char*>(password.c_str()),
                       password.length(), 1, key.data(), nullptr) != KEY_SIZE) {
        throw std::runtime_error("Key derivation failed");
    }
    return key;
}

std::vector<unsigned char> AESStrategy::encrypt(const std::vector<unsigned char>& data, const std::string& key) {
    auto iv = generateIV();
    auto derived_key = deriveKey(key);
    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create cipher context");
    
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, derived_key.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize encryption");
    }
    
    std::vector<unsigned char> ciphertext(data.size() + EVP_MAX_BLOCK_LENGTH);
    int len1, len2;
    
    if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len1, data.data(), data.size()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to encrypt data");
    }
    
    if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len1, &len2) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to finalize encryption");
    }
    
    EVP_CIPHER_CTX_free(ctx);
    
    ciphertext.resize(len1 + len2);
    std::vector<unsigned char> result;
    result.reserve(iv.size() + ciphertext.size());
    result.insert(result.end(), iv.begin(), iv.end());
    result.insert(result.end(), ciphertext.begin(), ciphertext.end());
    
    return result;
}

std::vector<unsigned char> AESStrategy::decrypt(const std::vector<unsigned char>& data, const std::string& key) {
    if (data.size() < BLOCK_SIZE) throw std::runtime_error("Invalid encrypted data");
    
    std::vector<unsigned char> iv(data.begin(), data.begin() + BLOCK_SIZE);
    auto derived_key = deriveKey(key);
    
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) throw std::runtime_error("Failed to create cipher context");
    
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, derived_key.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to initialize decryption");
    }
    
    std::vector<unsigned char> plaintext(data.size() - BLOCK_SIZE);
    int len1, len2;
    
    if (EVP_DecryptUpdate(ctx, plaintext.data(), &len1,
                         data.data() + BLOCK_SIZE,
                         data.size() - BLOCK_SIZE) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to decrypt data");
    }
    
    if (EVP_DecryptFinal_ex(ctx, plaintext.data() + len1, &len2) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("Failed to finalize decryption");
    }
    
    EVP_CIPHER_CTX_free(ctx);
    plaintext.resize(len1 + len2);
    
    return plaintext;
}