cmake_minimum_required(VERSION 3.12)
project(FileEncryptionTool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link OpenSSL libraries
target_link_libraries(${PROJECT_NAME} 
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Enable testing
enable_testing()
add_subdirectory(tests)