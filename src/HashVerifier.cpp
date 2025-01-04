#include "HashVerifier.hpp"
#include <sstream>
#include <iomanip>

std::string HashVerifier::calculateSHA256(const std::vector<unsigned char>& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.data(), data.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

bool HashVerifier::verifyHash(const std::string& expectedHash, const std::vector<unsigned char>& data) {
    return calculateSHA256(data) == expectedHash;
}