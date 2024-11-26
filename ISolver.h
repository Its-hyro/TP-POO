#ifndef ISOLVER_H
#define ISOLVER_H
#include "variable.h"   


class ISolver {
public:
    virtual ~ISolver() = default;
    virtual void compute_iteration(Variable& u_k, Variable& u_kp1) = 0;
};

#endif // ISOLVER_H 