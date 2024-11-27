#include <gtest/gtest.h>
#include <memory>
#include "UniformMesh.h"
#include "problem.h"
#include "equation.h"
#include <spdlog/spdlog.h>
#include "solvers/Jacobi.h"
#include "solvers/GaussSeidel.h"

class TestEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        spdlog::set_level(spdlog::level::debug);
    }
};

class ProblemTest : public ::testing::Test {
protected:
    void SetUp() override {
        mesh = std::make_shared<UniformMesh>(0, 1, 0.1);
        config.epsilon = 1e-6;
        config.max_iterations = 1000;
    }

    std::shared_ptr<UniformMesh> mesh;
    Problem::Configuration config;
};

// Test de UniformMesh
TEST_F(ProblemTest, MeshTest) {
    EXPECT_EQ(mesh->getXMin(), 0);
    EXPECT_EQ(mesh->getXMax(), 1);
    EXPECT_EQ(mesh->getNumPoints(), 11);

    EXPECT_THROW(UniformMesh(10, 0, 1), std::invalid_argument);
    EXPECT_THROW(UniformMesh(0, 10, -1), std::invalid_argument);
}

// Test de Equation avec différentes conditions initiales
TEST_F(ProblemTest, EquationTest) {
    Equation::Parameters params;
    params.T1 = 30.0;
    params.T2 = 15.0;
    
    // Test avec condition initiale par défaut
    Equation eq(params);
    Variable u_k(mesh);
    Variable u_kp1(mesh);
    
    EXPECT_NO_THROW(eq.compute(mesh, u_k, u_kp1));
    
    // Test avec condition initiale personnalisée
    params.initial_condition = [](double x) { return x * x; };
    Equation eq2(params);
    EXPECT_NO_THROW(eq2.compute_initial_condition(u_k, mesh));
}

// Test de convergence avec monitoring
TEST_F(ProblemTest, ConvergenceTest) {
    std::vector<double> convergence_history;
    config.iteration_callback = [&convergence_history](int, double diff) {
        convergence_history.push_back(diff);
    };

    Problem problem(mesh, config);
    problem.solve<Jacobi>();

    // Vérifie que la convergence est monotone
    for (size_t i = 1; i < convergence_history.size(); ++i) {
        EXPECT_LE(convergence_history[i], convergence_history[i-1]);
    }
}

// Test des conditions aux limites
TEST_F(ProblemTest, BoundaryConditionsTest) {
    Problem problem(mesh, config);
    problem.solve<GaussSeidel>();
    
    const Variable& solution = problem.get_solution();
    EXPECT_NEAR(solution[0], 30.0, 1e-10);
    EXPECT_NEAR(solution[mesh->getNumPoints()-1], 15.0, 1e-10);
}

// Test de performance
TEST_F(ProblemTest, PerformanceTest) {
    auto fine_mesh = std::make_shared<UniformMesh>(0, 1, 0.01); // 100 points
    Problem problem(fine_mesh, config);
    
    auto start = std::chrono::high_resolution_clock::now();
    problem.solve<Jacobi>();
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    spdlog::info("Temps de résolution : {} ms", duration.count());
    
    EXPECT_LT(duration.count(), 1000); // Test doit finir en moins d'une seconde
}

TEST_F(ProblemTest, ExactSolutionTest) {
    // Configuration
    Problem::Configuration config;
    config.epsilon = 1e-6;
    
    // Création du problème
    Problem problem(mesh, config);
    
    // Résolution
    problem.solve<Jacobi>();
    
    // Récupération des solutions
    const Variable& numerical = problem.get_solution();
    const Variable& exact = problem.get_exact_solution();
    
    // Vérification de la convergence vers la solution exacte
    for(size_t i = 0; i < mesh->x_size(); ++i) {
        double x = mesh->getX(i);
        double expected = (15.0 - 30.0) * x + 30.0;  // T2 = 15, T1 = 30
        EXPECT_NEAR(numerical[i], expected, 1.5e-5);
        EXPECT_NEAR(exact[i], expected, 1e-10);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    return RUN_ALL_TESTS();
}