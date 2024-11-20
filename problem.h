#ifndef PROBLEM_H
#define PROBLEM_H

#include "equation.h"
#include "IMesh.h"

class Problem {
private:
    Equation equation;
    IMesh* mesh;           // Pointeur vers l'interface IMesh
    int num_iterations;    // Nombre d'itérations

public:
    Problem(IMesh* mesh);
    ~Problem();

    void solve();          // Méthode pour résoudre le problème
};

#endif // PROBLEM_H
