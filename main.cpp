#include "problem.h"
#include "UniformMesh.h" 
#include <iostream>
#include <spdlog/spdlog.h>
#include "solvers/Jacobi.h"
#include "solvers/GaussSeidel.h"

void setup_logging() {
    // Configuration du logging
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] %v");
}

void iteration_callback(int iter, double diff) {
    spdlog::debug("Itération {} : différence = {}", iter, diff);
}

int main() { 
    try {
        setup_logging();
        spdlog::info("Début du programme principal");

        // Configuration du problème
        Problem::Configuration config;
        config.epsilon = 1e-6;
        config.max_iterations = 2000;
        config.verbose = true;
        config.T1 = 30.0;
        config.T2 = 15.0;
        config.iteration_callback = iteration_callback;

        // Création du maillage
        auto mesh = std::make_shared<UniformMesh>(0.0, 1.0, 0.01); // 100 points
        spdlog::info("Maillage créé avec {} points", mesh->getNumPoints());

        // Création et résolution du problème
        Problem problem(mesh, config);
        
        // Résolution avec Jacobi
        problem.solve<Jacobi>();
        spdlog::info("Résidu final Jacobi: {}", 
                     problem.compute_residual(problem.get_jacobi_solution()));
        
        // Résolution avec Gauss-Seidel
        problem.solve<GaussSeidel>();
        spdlog::info("Résidu final Gauss-Seidel: {}", 
                     problem.compute_residual(problem.get_gauss_solution()));
        
        // Export des résultats pour comparaison
        problem.get_jacobi_solution().print("jacobi_solution.dat");
        problem.get_gauss_solution().print("gauss_solution.dat");
        problem.get_exact_solution().print("exact_solution.dat");
        
        // Génération des graphiques avec gnuplot
        spdlog::info("Génération des graphiques...");
        system("chmod +x plot_solutions.gp");  // Rendre le script exécutable
        system("./plot_solutions.gp");
        spdlog::info("Graphiques générés : solutions_comparison.png, jacobi_evolution.png, gauss_evolution.png");
        
        spdlog::info("Fin du programme principal");
    } catch (const std::exception& e) { 
        spdlog::error("Erreur : {}", e.what());
        return 1;
    }

    return 0;
}