# File Encryption Tool

A command-line file encryption and decryption tool written in C++. This tool uses XOR cipher to encrypt and decrypt files, demonstrating object-oriented programming principles, file handling, and error management in C++.

## Features

- File encryption using XOR cipher
- File decryption
- Command-line interface
- Error handling and input validation
- Binary file support
- Cross-platform compatibility

## Building the Project

### Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- CMake (optional)
- Make (optional)

### Compilation

```bash
# Using g++
g++ -o file_encryptor file_encryptor.cpp -std=c++11

# Or using clang++
clang++ -o file_encryptor file_encryptor.cpp -std=c++11
```

## Usage

The tool supports two operations: encryption (-e) and decryption (-d).

### Encrypting a file:

```shellscript
./file_encryptor -e input.txt encrypted.bin mypassword
```

### Decrypting a file:

```shellscript
./file_encryptor -d encrypted.bin decrypted.txt mypassword
```

## Security Note

This is a demonstration project using a simple XOR cipher. For production use, please use established cryptographic libraries like OpenSSL or Crypto++.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.


<hr/>


This project demonstrates several important programming concepts:

1. Object-Oriented Programming
   - Encapsulation using classes
   - Private helper methods
   - Clean public interface

2. Error Handling
   - Exception handling
   - Input validation
   - File existence checks

3. File Operations
   - Binary file reading/writing
   - Stream operations
   - Buffer handling

4. Modern C++ Features
   - Standard library containers (vector)
   - RAII principles
   - String handling

To make this project even better for your GitHub profile, you could:

1. Add unit tests
2. Implement more advanced encryption algorithms
3. Add a progress bar for large files
4. Support for directory encryption
5. Add file integrity verification
6. Create a CMake build system
