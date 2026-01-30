cmake_minimum_required(VERSION 3.13)
project(NETSIM)

# Ustawienie standardu C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Sekcja 1: Pobieranie GoogleTest (GTest) ---
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# Wymuszenie użycia dynamicznego CRT (ważne dla Windows/MinGW)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(${googletest_SOURCE_DIR}/googletest/include)
# --- Sekcja 2: Konfiguracja ścieżek i plików ---
include_directories(include)

# Lista plików źródłowych logiki (bez main.cpp i bez testów)
set(LIB_SOURCES
    src/package.cpp
    src/storage_types.cpp
    src/storage_types.cpp
    src/nodes.cpp      
    src/helpers.cpp
    src/factory.cpp
)

# --- Sekcja 3: Główna aplikacja (main_app) ---
# Tworzy plik main_app.exe
add_executable(main_app main.cpp ${LIB_SOURCES})

# --- Sekcja 4: Testy jednostkowe (unit_tests) ---
# Tworzy plik unit_tests.exe
add_executable(unit_tests test/tests.cpp ${LIB_SOURCES})

# Kluczowe: Podlinkowanie bibliotek GTest do pliku testowego
# GTest::gtest_main automatycznie dodaje funkcję main() dla testów, 
# więc nie musisz jej pisać w test/tests.cpp
target_link_libraries(unit_tests 
    GTest::gtest 
    GTest::gtest_main
)

# Opcjonalnie: ułatwia uruchamianie testów komendą "ctest"
enable_testing()
add_test(NAME MyProjectTests COMMAND unit_tests)