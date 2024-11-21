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

void Equation::compute_initial_condition(Variable& u, IMesh* mesh){
    if (!mesh){
        throw std::invalid_argument("Maillage invalide");
    }
    for (int i = 0; i < mesh->x_size(); ++i){
        if (mesh->getX(i) <= 0.5){
            u[i] = T1;
        } else {
            u[i] = T2;
        }
    }
}

void Equation::compute_boundary_condition(Variable& u, IMesh* mesh){
    if (!mesh){
        throw std::invalid_argument("Maillage invalide ");

    }
    u[0] = T1;  
    u[mesh->x_size() - 1] = T2;
}
