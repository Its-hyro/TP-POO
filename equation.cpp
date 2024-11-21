#include "equation.h"
#include <iostream>

// Constructeur par défaut
Equation::Equation() {
    std::cout << "Création d’une instance de Equation." << std::endl; // Affiche un message lors de la création de l'instance
}
// Destructeur
void Equation::compute(IMesh* mesh) { 
    if (!mesh) {
        throw std::invalid_argument("IMesh invalide : le maillage est nul."); // Lance une exception si le maillage est nul 
    }
    // Parcours de tous les points du maillage 
    for (int i = 0; i < mesh->getNumPoints(); ++i) {
        std::cout << "-- at x_i = " << mesh->getX(i) << std::endl; // Affiche la position du point courant
    }
}
