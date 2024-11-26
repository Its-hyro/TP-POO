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
        config.iteration_callback = iteration_callback;

        // Création du maillage
        auto mesh = std::make_shared<UniformMesh>(0.0, 1.0, 0.01); // 100 points
        spdlog::info("Maillage créé avec {} points", mesh->getNumPoints());

        // Création et résolution du problème
        Problem problem(mesh, config);
        problem.solve<Jacobi>();
        problem.solve<GaussSeidel>();

        // Vérification du résidu
        double final_residual = problem.compute_residual(problem.get_solution());
        spdlog::info("Résidu final: {}", final_residual);

        // Accès à la solution
        [[maybe_unused]] const auto& solution = problem.get_solution();
        spdlog::info("Solution calculée avec succès");

        spdlog::info("Fin du programme principal");
    } catch (const std::exception& e) { 
        spdlog::error("Erreur : {}", e.what());
        return 1;
    }

    return 0;
}