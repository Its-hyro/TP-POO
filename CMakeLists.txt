cmake_minimum_required(VERSION 3.10)
project(SimulatorProject)

# Utiliser le standard C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Fichiers sources de l'exécutable principal
add_executable(Simulator main.cpp problem.cpp equation.cpp UniformMesh.cpp)

# Includer GTest
find_package(GTest REQUIRED)
include(GoogleTest)

# Définir l'exécutable de test avant de spécifier les bibliothèques
add_executable(UnitTests test_unit.cpp problem.cpp equation.cpp UniformMesh.cpp)

# Lier les bibliothèques GTest et GTest::Main
target_link_libraries(UnitTests GTest::GTest GTest::Main)

# Découverte des tests pour CTest
gtest_discover_tests(UnitTests)
