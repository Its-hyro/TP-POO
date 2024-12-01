#ifndef PROBLEM_H
#define PROBLEM_H

#include <memory>
#include "equation.h"
#include "IMesh.h"
#include "variable.h"
#include "solvers/Jacobi.h"
#include "solvers/GaussSeidel.h"

class Problem {
public:
    struct Configuration {
        double epsilon;
        int max_iterations;
        bool verbose;
        std::function<void(int, double)> iteration_callback;
        
        // Ajout des conditions aux limites
        double T1;  // Température à gauche (x = 0)
        double T2;  // Température à droite (x = 1)
        
        Configuration() 
            : epsilon(1e-6)
            , max_iterations(1000)
            , verbose(false)
            , T1(30.0)  // Valeur par défaut
            , T2(15.0)  // Valeur par défaut
        {}
    };

private:
    Equation equation;
    std::shared_ptr<IMesh> mesh;
    Configuration config;
    Variable u_k;
    Variable u_kp1;
    Variable u_k_jacobi;
    Variable u_kp1_jacobi;
    Variable u_k_gauss;
    Variable u_kp1_gauss;
    Variable u_ref;
    Variable solution;

    void initializeBoundaryConditions();

public:
    Problem(std::shared_ptr<IMesh> mesh, Configuration config = Configuration{});
    
    template<typename SolverType>
    void solve() {
        // Calcul de la solution exacte
        equation.compute_exact_solution(u_ref, mesh);
        
        // Sélection des variables selon le solveur
        Variable& u_k = std::is_same_v<SolverType, Jacobi> ? u_k_jacobi : u_k_gauss;
        Variable& u_kp1 = std::is_same_v<SolverType, Jacobi> ? u_kp1_jacobi : u_kp1_gauss;
        
        // Initialisation des conditions initiales
        equation.compute_initial_condition(u_k, mesh);
        
        // Export de la condition initiale
        u_k.print("initial_condition.dat");
        
        int iter = 0;
        double diff;
        
        do {
            equation.compute_for_solver<SolverType>(u_k, u_kp1, mesh);
            diff = u_kp1.max_difference(u_k);
            u_k = u_kp1;
            
            // Export intermédiaire optionnel (tous les N itérations)
            if(config.verbose && iter % 100 == 0) {
                std::string filename = std::is_same_v<SolverType, Jacobi> ? 
                    "jacobi_iter_" : "gauss_iter_";
                u_kp1.print(filename + std::to_string(iter) + ".dat");
            }
            
            if (config.iteration_callback) {
                config.iteration_callback(iter, diff);
            }
            
            iter++;
        } while (iter < config.max_iterations && diff > config.epsilon);

        // Export des solutions finales
        if(std::is_same_v<SolverType, Jacobi>) {
            u_kp1.print("jacobi_final.dat");
        } else {
            u_kp1.print("gauss_final.dat");
        }
        u_ref.print("exact_solution.dat");

        // Mise à jour de la solution finale
        solution = u_kp1;
    }
    
    bool has_converged() const;
    const Variable& get_jacobi_solution() const { return u_kp1_jacobi; }
    const Variable& get_gauss_solution() const { return u_kp1_gauss; }
    const Variable& get_exact_solution() const { return u_ref; }
    const Variable& get_solution() const { return solution; }
    
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
