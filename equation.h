#ifndef EQUATION_H
#define EQUATION_H

#include "IMesh.h"
#include "variable.h"

class Equation {
private:
    const double T1 = 30.0;
    const double T2 = 15.0;

public:
    Equation();           
    void compute(IMesh* mesh);  
    void compute_initial_condition(Variable& u, IMesh* mesh);
    void compute_boundary_condition(Variable& u, IMesh* mesh);
};

#endif // EQUATION_H
