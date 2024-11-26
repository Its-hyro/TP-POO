#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include "../ISolver.h"
#include "../variable.h"

class GaussSeidel : public ISolver {
public:
    void compute_iteration(Variable& u_k, Variable& u_kp1) override {
        // Copie initiale
        u_kp1 = u_k;
        
        const size_t size = u_k.size();
        // Mise à jour immédiate (utilise les valeurs déjà calculées)
        for (size_t i = 1; i < size - 1; ++i) {
            u_kp1[i] = (u_kp1[i-1] + u_k[i+1]) / 2.0;
        }
    }
};

#endif 