#ifndef EQUATION_H
#define EQUATION_H

#include <memory>
#include <functional>
#include "IMesh.h"
#include "variable.h"
#include "ISolver.h"
#include "concepts.h"

class Equation {
public:
    struct Parameters {
        double T1;
        double T2;
        std::function<double(double)> initial_condition;
        
        Parameters() : T1(30.0), T2(15.0) {
            initial_condition = [this](double x) {
                return x <= 0.5 ? T1 : T2;
            };
        }
    };

private:
    Parameters params;
    
public:
    explicit Equation(Parameters params = Parameters{});
    
    // Méthodes de calcul principales
    void compute(std::shared_ptr<IMesh> mesh, Variable& u_k, Variable& u_kp1);
    
    // Template pour différents solveurs
    template<SolverConcept Solver>
    void compute_for_solver(Variable& u_k, Variable& u_kp1, std::shared_ptr<IMesh> mesh) {
        Solver solver;
        solver.compute_iteration(u_k, u_kp1);
        compute_boundary_condition(u_kp1, *mesh);
    }
    
    // Conditions
    void compute_initial_condition(Variable& u, std::shared_ptr<IMesh> mesh);
    void compute_boundary_condition(Variable& u_kp1, const IMesh& mesh);
    
    // Setters pour les paramètres
    void set_temperatures(double T1, double T2);
    void set_initial_condition(std::function<double(double)> func);

    void compute_exact_solution(Variable& u_ref, std::shared_ptr<IMesh> mesh) {
        if (!mesh) {
            throw std::invalid_argument("Maillage invalide");
        }
        for (size_t i = 0; i < mesh->x_size(); ++i) {
            double x = mesh->getX(i);
            u_ref[i] = (params.T2 - params.T1) * x + params.T1;
        }
    }
};

#endif // EQUATION_H
