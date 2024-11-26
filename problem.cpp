#include "problem.h"
#include <spdlog/spdlog.h>
#include <iostream>

Problem::Problem(std::shared_ptr<IMesh> mesh, Configuration config)
    : mesh(mesh)
    , config(config)
    , u_k(mesh)
    , u_kp1(mesh) 
{
    if (!mesh) {
        throw std::invalid_argument("Le maillage est nul.");
    }
    spdlog::info("Création d'une instance de Problem avec un maillage de {} points", 
                 mesh->getNumPoints());
}

bool Problem::has_converged() const {
    double diff = u_kp1.max_difference(u_k);
    double residual = compute_residual(u_kp1);
    
    return diff < config.epsilon && residual < config.epsilon;
}

double Problem::compute_residual(const Variable& u) const {
    double max_residual = 0.0;
    
    for (int i = 1; i < mesh->x_size() - 1; ++i) {
        double dx = mesh->getX(1) - mesh->getX(0);
        double residual = (u[i-1] - 2*u[i] + u[i+1]) / (dx*dx);
        max_residual = std::max(max_residual, std::abs(residual));
    }
    
    return max_residual;
}
