#include "problem.h"
#include "UniformMesh.h" 
#include <iostream>


int main() { 
    try {
        std::cout << "Début du programme principal." << std::endl; // Message de début

        // Création d'un maillage uniforme
        IMesh* mesh = new UniformMesh(0.0, 1.0, 0.2);

        // Création d'une instance de Problem avec le maillage
        Problem problem(mesh); // Utilisation du constructeur de copie
        problem.solve();  // Appel à la méthode solve()

        std::cout << "Fin du programme principal." << std::endl; // Message de fin
    } catch (const std::exception& e) { // Gestion des exceptions
        std::cerr << "Erreur : " << e.what() << std::endl; // Affichage du message d'erreur
    }

    return 0;
}