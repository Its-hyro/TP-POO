cmake_minimum_required(VERSION 3.14)
project(SimulatorProject VERSION 1.0)

# Options de compilation
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options de build
option(BUILD_TESTING "Build the testing tree." ON)
option(ENABLE_WARNINGS "Enable warnings" ON)

# Compiler flags
if(ENABLE_WARNINGS)
    if(MSVC)
        add_compile_options(/W4)
    else()
        add_compile_options(-Wall -Wextra -Wpedantic)
    endif()
endif()

# Trouver les dépendances
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)

# Définir les sources communes (sans main.cpp)
set(COMMON_SOURCES
    problem.cpp
    equation.cpp
    UniformMesh.cpp
    variable.cpp
)

# Exécutable principal
add_executable(Simulator main.cpp ${COMMON_SOURCES})
target_link_libraries(Simulator PRIVATE spdlog::spdlog)

# Tests
if(BUILD_TESTING)
    enable_testing()
    add_executable(UnitTests test_unit.cpp ${COMMON_SOURCES})
    target_link_libraries(UnitTests PRIVATE 
        GTest::GTest 
        GTest::Main
        spdlog::spdlog
    )
    gtest_discover_tests(UnitTests)
endif()

# Installation
install(TARGETS Simulator
    RUNTIME DESTINATION bin
)
