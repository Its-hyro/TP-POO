#include "problem.h"
#include <spdlog/spdlog.h>
#include <iostream>

Problem::Problem(std::shared_ptr<IMesh> mesh, Configuration config)
    : equation(Equation::Parameters(config.T1, config.T2))
    , mesh(mesh)
    , config(config)
    , u_k(mesh)
    , u_kp1(mesh)
    , u_k_jacobi(mesh, "jacobi_k")
    , u_kp1_jacobi(mesh, "jacobi_kp1")
    , u_k_gauss(mesh, "gauss_k")
    , u_kp1_gauss(mesh, "gauss_kp1")
    , u_ref(mesh, "reference")
    , solution(mesh, "solution")    
{
    if (!mesh) {
        throw std::invalid_argument("Le maillage est nul.");
    }
    
    initializeBoundaryConditions();
    equation.compute_exact_solution(u_ref, mesh);
    
    spdlog::info("Création d'une instance de Problem avec un maillage de {} points", 
                 mesh->getNumPoints());
}

void Problem::initializeBoundaryConditions() {
    auto initVariable = [this](Variable& var) {
        var[0] = config.T1;
        var[mesh->getNumPoints() - 1] = config.T2;
    };
    
    initVariable(u_k);
    initVariable(u_kp1);
    initVariable(u_k_jacobi);
    initVariable(u_kp1_jacobi);
    initVariable(u_k_gauss);
    initVariable(u_kp1_gauss);
    initVariable(solution);
}

bool Problem::has_converged() const {
    double residual = compute_residual(solution);
    
    return residual < config.epsilon;
}

double Problem::compute_residual(const Variable& u) const {
    double max_residual = 0.0;
    
    for (size_t i = 1; i < static_cast<size_t>(mesh->x_size() - 1); ++i) {
        double dx = mesh->getX(1) - mesh->getX(0);
        double residual = std::abs((u[i-1] - 2*u[i] + u[i+1]) / (dx*dx));
        max_residual = std::max(max_residual, residual);
    }
    
    return max_residual;
}