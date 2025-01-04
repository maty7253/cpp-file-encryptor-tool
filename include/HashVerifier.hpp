#pragma once
#include <string>
#include <vector>
#include <openssl/sha.h>

class HashVerifier {
public:
    static std::string calculateSHA256(const std::vector<unsigned char>& data);
    static bool verifyHash(const std::string& expectedHash, const std::vector<unsigned char>& data);
};