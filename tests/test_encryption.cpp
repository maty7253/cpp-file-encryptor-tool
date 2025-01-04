#include <gtest/gtest.h>
#include "FileEncryptor.hpp"
#include <vector>
#include <string>

class EncryptionTest : public ::testing::Test {
protected:
    std::shared_ptr<IEncryptionStrategy> xorStrategy;
    std::shared_ptr<IEncryptionStrategy> aesStrategy;
    const std::string testKey = "testkey123";
    
    void SetUp() override {
        xorStrategy = std::make_shared<XORStrategy>();
        aesStrategy = std::make_shared<AESStrategy>();
    }
};

TEST_F(EncryptionTest, XOREncryptionDecryption) {
    std::vector<unsigned char> testData = {'H', 'e', 'l', 'l', 'o'};
    
    auto encrypted = xorStrategy->encrypt(testData, testKey);
    auto decrypted = xorStrategy->decrypt(encrypted, testKey);
    
    ASSERT_EQ(testData, decrypted);
}

TEST_F(EncryptionTest, AESEncryptionDecryption) {
    std::vector<unsigned char> testData = {'H', 'e', 'l', 'l', 'o'};
    
    auto encrypted = aesStrategy->encrypt(testData, testKey);
    auto decrypted = aesStrategy->decrypt(encrypted, testKey);
    
    ASSERT_EQ(testData, decrypted);
}

TEST_F(EncryptionTest, EmptyData) {
    std::vector<unsigned char> emptyData;
    
    auto encryptedXOR = xorStrategy->encrypt(emptyData, testKey);
    auto decryptedXOR = xorStrategy->decrypt(encryptedXOR, testKey);
    
    ASSERT_EQ(emptyData, decryptedXOR);
    
    auto encryptedAES = aesStrategy->encrypt(emptyData, testKey);
    auto decryptedAES = aesStrategy->decrypt(encryptedAES, testKey);
    
    ASSERT_EQ(emptyData, decryptedAES);
}