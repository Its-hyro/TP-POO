#ifndef JACOBI_H
#define JACOBI_H

#include "../ISolver.h"
#include "../variable.h"

class Jacobi : public ISolver {
public:
    void compute_iteration(Variable& u_k, Variable& u_kp1) override {
        const size_t size = u_k.size();
        for (size_t i = 1; i < size - 1; ++i) {
            u_kp1[i] = (u_k[i-1] + u_k[i+1]) / 2.0;
        }
    }
};

#endif 