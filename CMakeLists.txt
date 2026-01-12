cmake_minimum_required(VERSION 3.13)
project(NETSIM)


set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Zapobiega instalowaniu gtest razem z Twoim projektem
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include_directories(include)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        )

add_executable(main_app main.cpp ${LIB_SOURCES})
add_executable(unit_tests tests/tests.cpp ${LIB_SOURCES})