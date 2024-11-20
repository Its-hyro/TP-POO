#ifndef EQUATION_H
#define EQUATION_H

#include "IMesh.h"

class Equation {
public:
    Equation();           // Constructeur
    void compute(IMesh* mesh);  // Méthode pour résoudre l'équation
};

#endif // EQUATION_H
