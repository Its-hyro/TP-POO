#include "problem.h"
#include "UniformMesh.h" 
#include <iostream>


int main() { 
    try {
        std::cout << "Début du programme principal." << std::endl; 

        // Création d'un maillage uniforme avec un pointeur unique 
        std::unique_ptr <IMesh> mesh (new UniformMesh(0.0, 1.0, 0.2));

        // Création d'une instance de Problem avec le maillage
        Problem problem(mesh.get()); 
        problem.solve();  

        std::cout << "Fin du programme principal." << std::endl; 
    } catch (const std::exception& e) { 
        std::cerr << "Erreur : " << e.what() << std::endl; 
        return 1;
    }

    return 0;
}