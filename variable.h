#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include "IMesh.h"

class Variable {
private:
    std::vector<double> values;             // Stocke les valeurs de u_i
    IMesh* mesh;                            // Pointeur vers le maillage associé

public:
    // Constructeur
    Variable(IMesh* mesh);

    // Accès aux éléments
    double& operator[](int i);              // Lecture/écriture
    const double& operator[](int i) const;  // Lecture seule

    // Retourne la taille du tableau
    size_t size() const;
};

#endif // VARIABLE_H