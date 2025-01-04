# Advanced File Encryption Tool

A robust command-line file encryption and decryption tool written in modern C++. This tool implements industry-standard encryption algorithms and demonstrates advanced programming concepts including object-oriented design, secure file handling, and modern C++ features.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![OpenSSL](https://img.shields.io/badge/OpenSSL-3.0-green.svg)

## Features

- Multiple encryption algorithms:
  - AES-256 (Advanced Encryption Standard)
  - XOR cipher (for educational purposes)
- File integrity verification using SHA-256
- Real-time progress tracking with progress bar
- Comprehensive error handling and input validation
- Binary file support
- Cross-platform compatibility
- Modern C++ implementation (C++17)

## Security Features

- Secure key derivation using OpenSSL
- Random IV generation for AES encryption
- File integrity verification using SHA-256 hashing
- Memory-safe operations
- Proper cleanup of sensitive data

## Project Structure

```
FileEncryptionTool/
├── src/                    # Source files
│   ├── main.cpp
│   ├── FileEncryptor.cpp
│   ├── EncryptionStrategies.cpp
│   ├── HashVerifier.cpp
│   └── ProgressBar.cpp
├── include/                # Header files
│   ├── FileEncryptor.hpp
│   ├── EncryptionStrategies.hpp
│   ├── HashVerifier.hpp
│   └── ProgressBar.hpp
├── tests/                  # Test files
│   ├── test_encryption.cpp
│   └── test_hash.cpp
├── CMakeLists.txt         # CMake configuration
└── README.md              # Documentation
```

## Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, or MSVC 2017+)
- CMake 3.12 or higher
- OpenSSL development libraries
- Google Test (for running tests)

### Installing Dependencies

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential cmake libssl-dev libgtest-dev
```

#### macOS
```bash
brew install cmake openssl
```

#### Windows
Install using vcpkg:
```bash
vcpkg install openssl:x64-windows gtest:x64-windows
```

## Building the Project

1. Clone the repository:
```bash
git clone https://github.com/maty7253/file-encryptor-tool.git
cd file-encryptor-tool
```

2. Create and enter build directory:
```bash
mkdir build && cd build
```

3. Configure and build:
```bash
cmake ..
cmake --build .
```

4. (Optional) Run tests:
```bash
ctest --output-on-failure
```

## Usage

The tool supports two operations (encryption and decryption) with multiple algorithms.

### Encrypting a file:
```bash
./FileEncryptionTool -e <algorithm> <input_file> <output_file> <key>

# Example using AES:
./FileEncryptionTool -e aes secret.txt secret.enc mypassword

# Example using XOR:
./FileEncryptionTool -e xor secret.txt secret.enc mypassword
```

### Decrypting a file:
```bash
./FileEncryptionTool -d <algorithm> <input_file> <output_file> <key>

# Example:
./FileEncryptionTool -d aes secret.enc decrypted.txt mypassword
```

## Design Patterns Used

- Strategy Pattern: For different encryption algorithms
- RAII: For resource management
- Factory Method: For creating encryption strategies
- Command Pattern: For encryption/decryption operations

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## Testing

The project includes comprehensive unit tests using Google Test framework. To run the tests:

```bash
cd build
ctest --output-on-failure
```

## Security Note

While this tool implements strong encryption algorithms, please note:

1. Always use strong, random passwords
2. Keep your encryption keys secure
3. Update OpenSSL to the latest version
4. For production use, consider additional security measures like key stretching
5. The XOR cipher is included for educational purposes only and should not be used for sensitive data

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- OpenSSL team for their cryptographic library
- Google Test team for the testing framework
- C++ community for modern C++ guidelines and best practices