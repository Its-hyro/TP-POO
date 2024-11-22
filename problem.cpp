#include "problem.h"
#include <iostream>
#include <stdexcept> 

// Constructeur par défaut
Problem::Problem(IMesh* mesh) : mesh(mesh), num_iterations(1), u_k(mesh), u_kp1(mesh) {
    if (!mesh) { 
        throw std::invalid_argument("Le maillage est nul.");
    }
    std::cout << "Création d’une instance de Problem avec un maillage." << std::endl;
}

// Constructeur avec spécification du nombre d'itérations
Problem::~Problem() {
   // delete mesh;  // Nettoyage du pointeur
}

// Méthode pour résoudre le problème
void Problem::solve() {
    if (!mesh) {
        throw std::runtime_error("Impossible de résoudre le problème : le maillage est nul.");
    }
    // Resolution du probleme 
    std::cout << "--- Solve problem ---" << std::endl; 
    equation.compute_initial_condition(u_k, mesh);
    equation.compute_boundary_condition(u_k, mesh);
    
    for (int iter = 1; iter <= num_iterations; ++iter){
        std::cout << "--- Iterative methode iteration : " << iter << " ---" << std::endl;
        
        // Condition aux bords
        equation.compute_boundary_condition(u_kp1, mesh);
        equation.compute(mesh);

        // Update de u_k
        for (size_t i=0; i < u_k.size(); ++i){
            u_k[i] = u_kp1[i];
        }
    }

}
