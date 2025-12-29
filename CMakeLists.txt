cmake_minimum_required(VERSION 3.20)

project(game_server
    VERSION 0.1.0
    LANGUAGES CXX
)

# ----------------------------
# C++ standard
# ----------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ----------------------------
# Find Boost
# ----------------------------
find_package(Boost REQUIRED COMPONENTS system)

# ----------------------------
# Server executable
# ----------------------------
add_executable(server
    main.cpp
    protocol/dispatcher.cpp
    server/map_generator.cpp
)

# ----------------------------
# Include directories
# ----------------------------
target_include_directories(server
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/third_party/FastNoiseLite/Cpp
)

# ----------------------------
# Link libraries
# ----------------------------
target_link_libraries(server
    PRIVATE
        Boost::system
        pthread
)

# ----------------------------
# Warnings (optional but recommended)
# ----------------------------
target_compile_options(server
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

