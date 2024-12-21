#include "problem.h"
#include "UniformMesh.h" 
#include <iostream>
#include <spdlog/spdlog.h>
#include "solvers/Jacobi.h"
#include "solvers/GaussSeidel.h"

void setup_logging() {
    // Configuration minimale du logging pour ne pas impacter les performances
    spdlog::set_level(spdlog::level::warn);
}

int main() { 
    try {
        setup_logging();

        // Configuration du problème pour les tests de performance
        Problem::Configuration config;
        config.epsilon = 1e-6;
        config.max_iterations = 100;  // Limité à 100 itérations comme demandé dans le TD5
        config.verbose = false;       // Désactivation des sorties pour les performances
        config.T1 = 30.0;
        config.T2 = 15.0;
        config.iteration_callback = nullptr;  // Désactivation du callback pour les performances

        // Création du maillage avec une discrétisation fine (δx = 10^-6)
        auto mesh = std::make_shared<UniformMesh>(0.0, 1.0, 1e-6);

        // Création du problème
        Problem problem(mesh, config);
        
        std::cout << "\n=== Test de performance avec dx = 1e-6 et 100 itérations ===\n" << std::endl;
        
        // 1. Version séquentielle classique
        std::cout << "1. Version séquentielle :" << std::endl;
        std::cout << "------------------------" << std::endl;
        
        std::cout << "Méthode de Jacobi :" << std::endl;
        problem.solve<Jacobi>();
        
        std::cout << "\nMéthode de Gauss-Seidel :" << std::endl;
        problem.solve<GaussSeidel>();
        
        // 2. Version parallèle avec std::thread
        std::cout << "\n2. Version parallèle (threads) :" << std::endl;
        std::cout << "------------------------------" << std::endl;
        problem.solve_parallel();
        
        // 3. Version parallèle avec std::async
        std::cout << "\n3. Version parallèle (async) :" << std::endl;
        std::cout << "---------------------------" << std::endl;
        problem.solve_parallel_async(std::launch::async);
        
        // 4. Version séquentielle avec std::async deferred
        std::cout << "\n4. Version séquentielle (async deferred) :" << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        problem.solve_parallel_async(std::launch::deferred);
        
        // 5. Version parallèle STL/TBB (Jacobi uniquement)
        std::cout << "\n5. Version parallèle STL/TBB (Jacobi uniquement) :" << std::endl;
        std::cout << "----------------------------------------------" << std::endl;
        problem.solve_parallel_stl();

    } catch (const std::exception& e) { 
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}