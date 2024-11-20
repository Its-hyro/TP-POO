#include "problem.h"
#include <iostream>

Problem::Problem(IMesh* mesh) : mesh(mesh), num_iterations(1) {
    std::cout << "Création d’une instance de Problem avec un maillage." << std::endl;
}

Problem::~Problem() {
    delete mesh;  // Nettoyage du pointeur
}

void Problem::solve() {
    if (!mesh) {
        throw std::runtime_error("Le maillage est nul. Impossible de résoudre le problème.");
    }

    std::cout << "--- Solve problem ---" << std::endl;
    for (int iter = 1; iter <= num_iterations; ++iter) {
        std::cout << "--- Iterative methode iteration : " << iter << " ---" << std::endl;
        equation.compute(mesh);
    }
}
