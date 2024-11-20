#include "problem.h"
#include "UniformMesh.h"
#include <iostream>


int main() {
    std::cout << "Début du programme principal." << std::endl;

    // Création d'un maillage uniforme
    IMesh* mesh = new UniformMesh(0.0, 1.0, 0.2);

    // Création d'une instance de Problem avec le maillage
    Problem problem(mesh);
    problem.solve();  // Appel à la méthode solve()

    std::cout << "Fin du programme principal." << std::endl;

    return 0;
}
