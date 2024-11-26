#ifndef PROBLEM_H
#define PROBLEM_H

#include <memory>
#include "equation.h"
#include "IMesh.h"
#include "variable.h"

class Problem {
public:
    struct Configuration {
        double epsilon;
        int max_iterations = 1000;
        bool verbose = false;
        std::function<void(int, double)> iteration_callback = nullptr;

        Configuration() : epsilon(1e-5) {}
    };

private:
    Equation equation;
    std::shared_ptr<IMesh> mesh;
    Configuration config;
    Variable u_k;
    Variable u_kp1;

public:
    Problem(std::shared_ptr<IMesh> mesh, Configuration config);
    
    template<typename SolverType>
    void solve() {
        // Initialisation
        equation.compute_initial_condition(u_k, mesh);
        equation.compute_boundary_condition(u_k, *mesh);
        
        int iter = 0;
        double diff;
        
        SolverType solver;  // Créer une instance du solveur
        do {
            equation.compute_for_solver<SolverType>(u_k, u_kp1, mesh);
            diff = u_kp1.max_difference(u_k);
            u_k = u_kp1;
            
            if (config.iteration_callback) {
                config.iteration_callback(iter, diff);
            }
            
            iter++;
        } while (iter < config.max_iterations && diff > config.epsilon);
    }
    
    bool has_converged() const;
    const Variable& get_solution() const { return u_kp1; }
    
    // Accesseurs pour la configuration
    void set_epsilon(double eps) { config.epsilon = eps; }
    void set_max_iterations(int max_iter) { config.max_iterations = max_iter; }
    void set_verbose(bool verbose) { config.verbose = verbose; }
    void set_iteration_callback(std::function<void(int, double)> callback) {
        config.iteration_callback = callback;
    }
    double compute_residual(const Variable& u) const;
};

#endif // PROBLEM_H
