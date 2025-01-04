# Find GTest package
find_package(GTest REQUIRED)

# Add test executable
add_executable(encryption_tests
    test_encryption.cpp
    test_hash.cpp
)

# Link libraries
target_link_libraries(encryption_tests
    PRIVATE
    GTest::GTest
    GTest::Main
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Add tests to CTest
add_test(NAME encryption_tests COMMAND encryption_tests)