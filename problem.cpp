#include "problem.h"
#include <iostream>
#include <stdexcept> 

// Constructeur par défaut
Problem::Problem(IMesh* mesh) : mesh(mesh), num_iterations(1) {
    if (!mesh) {
        throw std::invalid_argument("Le maillage est nul.");
    }
    std::cout << "Création d’une instance de Problem avec un maillage." << std::endl;
}

// Constructeur avec spécification du nombre d'itérations
Problem::~Problem() {
    delete mesh;  // Nettoyage du pointeur
}

// Méthode pour résoudre le problème
void Problem::solve() {
    if (!mesh) {
        throw std::runtime_error("Impossible de résoudre le problème : le maillage est nul.");
    }

    std::cout << "--- Solve problem ---" << std::endl;
    for (int iter = 1; iter <= num_iterations; ++iter) {
        std::cout << "--- Iterative methode iteration : " << iter << " ---" << std::endl;
        equation.compute(mesh);  // Appel de compute() avec le maillage
    }
}
