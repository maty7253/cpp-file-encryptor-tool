#include <gtest/gtest.h>
#include "HashVerifier.hpp"
#include <vector>
#include <string>

TEST(HashTest, ConsistentHashing) {
    std::vector<unsigned char> testData = {'H', 'e', 'l', 'l', 'o'};
    
    std::string hash1 = HashVerifier::calculateSHA256(testData);
    std::string hash2 = HashVerifier::calculateSHA256(testData);
    
    ASSERT_EQ(hash1, hash2);
}

TEST(HashTest, DifferentDataDifferentHash) {
    std::vector<unsigned char> testData1 = {'H', 'e', 'l', 'l', 'o'};
    std::vector<unsigned char> testData2 = {'W', 'o', 'r', 'l', 'd'};
    
    std::string hash1 = HashVerifier::calculateSHA256(testData1);
    std::string hash2 = HashVerifier::calculateSHA256(testData2);
    
    ASSERT_NE(hash1, hash2);
}

TEST(HashTest, EmptyData) {
    std::vector<unsigned char> emptyData;
    std::string hash = HashVerifier::calculateSHA256(emptyData);
    ASSERT_FALSE(hash.empty());
}