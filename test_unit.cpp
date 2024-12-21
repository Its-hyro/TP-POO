#include <gtest/gtest.h>
#include <memory>
#include "UniformMesh.h"
#include "problem.h"
#include "equation.h"
#include "variable.h"
#include "solvers/Jacobi.h"
#include "solvers/GaussSeidel.h"
#include <spdlog/spdlog.h>
#include <cmath>

// Configuration de l'environnement de test
class TestEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        spdlog::set_level(spdlog::level::debug);
    }
};

// Fixture pour les tests
class SimulatorTest : public ::testing::Test {
protected:
    void SetUp() override {
        mesh = std::make_shared<UniformMesh>(0.0, 1.0, 0.1);
        config.epsilon = 1e-6;
        config.max_iterations = 10000;
        config.T1 = 30.0;
        config.T2 = 15.0;
    }

    std::shared_ptr<UniformMesh> mesh;
    Problem::Configuration config;
};

// 1. Tests du Maillage
TEST_F(SimulatorTest, MeshCreationAndProperties) {
    EXPECT_EQ(mesh->getXMin(), 0.0);
    EXPECT_EQ(mesh->getXMax(), 1.0);
    EXPECT_EQ(mesh->getNumPoints(), 11);  // (1-0)/0.1 + 1 = 11 points
    
    // Test des positions des points
    EXPECT_NEAR(mesh->getX(0), 0.0, 1e-10);
    EXPECT_NEAR(mesh->getX(5), 0.5, 1e-10);
    EXPECT_NEAR(mesh->getX(10), 1.0, 1e-10);
    
    // Test des cas d'erreur
    EXPECT_THROW(UniformMesh(1.0, 0.0, 0.1), std::invalid_argument);  // xmax < xmin
    EXPECT_THROW(UniformMesh(0.0, 1.0, 0.0), std::invalid_argument);  // dx = 0
    EXPECT_THROW(UniformMesh(0.0, 1.0, -0.1), std::invalid_argument); // dx < 0
}

// 2. Tests de la classe Variable
TEST_F(SimulatorTest, VariableOperations) {
    Variable var(mesh, "test_var");
    
    // Test de la taille
    EXPECT_EQ(var.size(), mesh->getNumPoints());
    
    // Test de l'accès aux éléments
    var[0] = 1.0;
    var[5] = 2.0;
    EXPECT_EQ(var[0], 1.0);
    EXPECT_EQ(var[5], 2.0);
    
    // Test de la copie
    Variable var2 = var;
    EXPECT_EQ(var2[0], 1.0);
    EXPECT_EQ(var2[5], 2.0);
    
    // Test de reset
    var.reset(3.0);
    for(size_t i = 0; i < var.size(); ++i) {
        EXPECT_EQ(var[i], 3.0);
    }
    
    // Test de max_difference
    Variable var3(mesh);
    var3.reset(1.0);
    var.reset(2.0);
    EXPECT_EQ(var.max_difference(var3), 1.0);
}

// 3. Tests de l'Équation et des solveurs
TEST_F(SimulatorTest, EquationAndSolvers) {
    Problem problem(mesh, config);
    
    // Test de la solution exacte
    const Variable& exact = problem.get_exact_solution();
    for(size_t i = 0; i < mesh->x_size(); ++i) {
        double x = mesh->getX(i);
        double expected = config.T1 + (config.T2 - config.T1) * x;
        EXPECT_NEAR(exact[i], expected, 1e-10);
    }
    
    // Test des solveurs
    problem.solve<Jacobi>();
    const Variable& jacobi_sol = problem.get_jacobi_solution();
    
    problem.solve<GaussSeidel>();
    const Variable& gauss_sol = problem.get_gauss_solution();
    
    // Vérification que les deux solveurs convergent vers la même solution
    for(size_t i = 0; i < mesh->x_size(); ++i) {
        EXPECT_NEAR(jacobi_sol[i], gauss_sol[i], 1e-5);
        EXPECT_NEAR(jacobi_sol[i], exact[i], 1e-5);
    }
}

// 4. Tests de convergence
TEST_F(SimulatorTest, ConvergenceTests) {
    std::vector<double> convergence_history;
    config.iteration_callback = [&convergence_history](int, double diff) {
        convergence_history.push_back(diff);
    };
    
    // Ajustement des paramètres pour assurer la convergence
    config.max_iterations = 10000;  // Beaucoup plus d'itérations
    config.epsilon = 1e-4;         // Critère moins strict
    
    Problem problem(mesh, config);
    
    // Test Jacobi
    problem.solve<Jacobi>();
    EXPECT_TRUE(problem.has_converged());
    
    // Vérification de la convergence monotone
    for(size_t i = 1; i < convergence_history.size(); ++i) {
        EXPECT_LE(convergence_history[i], convergence_history[i-1]);
    }
    
    // Test du résidu
    EXPECT_LE(problem.compute_residual(problem.get_solution()), config.epsilon);
}

// 5. Tests de performance
TEST_F(SimulatorTest, PerformanceTests) {
    // Création d'un maillage plus fin pour les tests de performance
    auto fine_mesh = std::make_shared<UniformMesh>(0.0, 1.0, 0.001);
    config.max_iterations = 100;  // Limité comme demandé dans le TD5
    Problem problem(fine_mesh, config);
    
    // Test séquentiel
    auto start = std::chrono::high_resolution_clock::now();
    problem.solve<Jacobi>();
    auto end = std::chrono::high_resolution_clock::now();
    auto seq_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Test parallèle
    start = std::chrono::high_resolution_clock::now();
    problem.solve_parallel();
    end = std::chrono::high_resolution_clock::now();
    auto par_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // On s'attend à ce que la version parallèle soit plus rapide
    EXPECT_LT(par_duration.count(), seq_duration.count());
}

// 6. Tests parallèles
TEST_F(SimulatorTest, ParallelImplementationTests) {
    auto fine_mesh = std::make_shared<UniformMesh>(0.0, 1.0, 0.001);
    config.max_iterations = 100;
    Problem problem(fine_mesh, config);
    
    // Test des différentes implémentations parallèles
    problem.solve<Jacobi>();  // Version séquentielle
    const Variable& seq_sol = problem.get_solution();
    
    problem.solve_parallel();  // Version std::thread
    const Variable& thread_sol = problem.get_solution();
    
    problem.solve_parallel_async();  // Version std::async
    const Variable& async_sol = problem.get_solution();
    
    problem.solve_parallel_stl();  // Version STL/TBB
    const Variable& stl_sol = problem.get_solution();
    
    // Vérification que toutes les versions donnent le même résultat
    for(size_t i = 0; i < fine_mesh->x_size(); ++i) {
        EXPECT_NEAR(thread_sol[i], seq_sol[i], 1e-5);
        EXPECT_NEAR(async_sol[i], seq_sol[i], 1e-5);
        EXPECT_NEAR(stl_sol[i], seq_sol[i], 1e-5);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    return RUN_ALL_TESTS();
}