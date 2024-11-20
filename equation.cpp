#include "equation.h"
#include <iostream>

Equation::Equation() {
    std::cout << "Création d’une instance de Equation." << std::endl;
}

void Equation::compute(IMesh* mesh) {
    if (!mesh) {
        throw std::invalid_argument("IMesh invalide : le maillage est nul.");
    }

    for (int i = 0; i < mesh->getNumPoints(); ++i) {
        std::cout << "-- at x_i = " << mesh->getX(i) << std::endl;
    }
}
