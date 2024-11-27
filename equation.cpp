#include "equation.h"
#include <iostream>
#include <spdlog/spdlog.h>  // Pour un meilleur logging

Equation::Equation(Parameters params) : params(params) {
    spdlog::info("Création d'une instance de Equation");
}

void Equation::compute(std::shared_ptr<IMesh> mesh, Variable& u_k, Variable& u_kp1) {
    if (!mesh) {
        throw std::invalid_argument("IMesh invalide");
    }
    
    // Calcul selon la méthode de Jacobi
    for (size_t i = 1; i < static_cast<size_t>(mesh->x_size() - 1); ++i) {
        u_kp1[i] = (u_k[i-1] + u_k[i+1]) / 2.0;
    }
    
    // Application des conditions aux limites
    compute_boundary_condition(u_kp1, *mesh);
}

void Equation::compute_initial_condition(Variable& u, std::shared_ptr<IMesh> mesh) {
    for (size_t i = 0; i < static_cast<size_t>(mesh->x_size()); ++i) {
        double x = mesh->getX(i);
        u[i] = params.initial_condition(x);
    }
}

void Equation::compute_boundary_condition(Variable& u, const IMesh& mesh) {
    u[0] = params.T1;
    u[mesh.x_size() - 1] = params.T2;
}

void Equation::set_temperatures(double T1, double T2) {
    params.T1 = T1;
    params.T2 = T2;
    spdlog::info("Températures mises à jour : T1 = {}, T2 = {}", T1, T2);
}

void Equation::set_initial_condition(std::function<double(double)> func) {
    params.initial_condition = func;
    spdlog::info("Fonction de condition initiale mise à jour");
}


