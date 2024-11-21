#include <gtest/gtest.h>
#include "UniformMesh.h"
#include "problem.h"
#include "equation.h"

// Test de UniformMesh
TEST(UnitaryTest, MeshTest) {
    // Cas normal
    UniformMesh mesh(0, 10, 1);
    EXPECT_EQ(mesh.getXMin(), 0);
    EXPECT_EQ(mesh.getXMax(), 10);
    EXPECT_EQ(mesh.getNumPoints(), 11);

    // Cas limite
    EXPECT_THROW(UniformMesh(10, 0, 1), std::invalid_argument);
    EXPECT_THROW(UniformMesh(0, 10, -1), std::invalid_argument);
}

// Test de Equation
TEST(UnitaryTest, EquationTest) {
    Equation eq;

    // Cas normal
    UniformMesh mesh(0, 10, 1);
    EXPECT_NO_THROW(eq.compute(&mesh));
    
    // Cas limite
    EXPECT_THROW(eq.compute(nullptr), std::invalid_argument);
}

// Test de Problem
TEST(UnitaryTest, ProblemTest) {
    // Cas normal : avec un maillage valide
    UniformMesh* valid_mesh = new UniformMesh(0, 10, 1);
    Problem problem(valid_mesh);
    EXPECT_NO_THROW(problem.solve());

    // Cas limite : avec un maillage nul
    IMesh* null_mesh = nullptr;
    EXPECT_THROW({
        Problem invalid_problem(null_mesh);
    }, std::invalid_argument); // Vérifie que std::invalid_argument est levé
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}