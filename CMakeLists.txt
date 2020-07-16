cmake_minimum_required(VERSION 3.10)

project(utility-library)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES src/scanner.cpp
            src/delimiters.cpp
            src/string_utility.cpp
            src/menu.cpp)

add_library(utility STATIC ${SOURCES})

set(HEADERS "include/scanner.hpp;"
            "include/string_utility.hpp;"
            "include/timer.hpp"
            "include/menu.hpp;"
            "include/rand.hpp")

set_target_properties(utility PROPERTIES PUBLIC_HEADER "${HEADERS}")

install(TARGETS utility
        LIBRARY DESTINATION /usr/local/lib
        PUBLIC_HEADER DESTINATION /usr/local/include)

