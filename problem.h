#ifndef PROBLEM_H
#define PROBLEM_H

#include <memory>
#include <thread>
#include <atomic>
#include <execution>
#include <algorithm>
#include <numeric>  // Pour std::iota
#include <future>  // Pour std::async
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "equation.h"
#include "IMesh.h"
#include "variable.h"
#include "solvers/Jacobi.h"
#include "solvers/GaussSeidel.h"
#include "Timer.hpp"

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
        Timer total_timer;
        Timer solver_timer;
        
        total_timer.start();
        
        // Sélection des variables selon le solveur
        Variable& u_k = std::is_same_v<SolverType, Jacobi> ? u_k_jacobi : u_k_gauss;
        Variable& u_kp1 = std::is_same_v<SolverType, Jacobi> ? u_kp1_jacobi : u_kp1_gauss;
        
        // Initialisation des conditions initiales
        equation.compute_initial_condition(u_k, mesh);
        
        // Export de la condition initiale
        u_k.print("initial_condition.dat");
        
        int iter = 0;
        double diff;
        double residual;
        
        // Démarrage du timer pour la méthode itérative
        solver_timer.start();
        
        do {
            equation.compute_for_solver<SolverType>(u_k, u_kp1, mesh);
            diff = u_kp1.max_difference(u_k);
            residual = compute_residual(u_kp1);
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
        } while (iter < config.max_iterations && (diff > config.epsilon || residual > config.epsilon));

        // Mise à jour de la solution finale
        solution = u_kp1;

        // Arrêt du timer pour la méthode itérative
        solver_timer.stop();
        
        // Export des solutions finales
        if(std::is_same_v<SolverType, Jacobi>) {
            u_kp1.print("jacobi_final.dat");
            std::cout << "Temps d'exécution de la méthode de Jacobi : ";
        } else {
            u_kp1.print("gauss_final.dat");
            std::cout << "Temps d'exécution de la méthode de Gauss-Seidel : ";
        }
        solver_timer.print();
        
        u_ref.print("exact_solution.dat");
        
        total_timer.stop();
        std::cout << "Temps total d'exécution : ";
        total_timer.print();
    }
    
    /**
     * @brief Version originale avec std::thread
     */
    void solve_parallel() {
        Timer total_timer;
        Timer jacobi_timer;
        Timer gauss_timer;
        
        total_timer.start();
        
        // Calcul de la solution exacte (thread principal uniquement)
        equation.compute_exact_solution(u_ref, mesh);
        
        // Initialisation des conditions initiales (thread principal uniquement)
        equation.compute_initial_condition(u_k_jacobi, mesh);
        equation.compute_initial_condition(u_k_gauss, mesh);
        
        // Variables thread-safe pour stocker les temps d'exécution
        std::atomic<double> jacobi_time{0.0};
        std::atomic<double> gauss_time{0.0};
        
        // Thread pour la méthode de Jacobi
        std::thread jacobi_thread([this, &jacobi_time]() {
            Timer local_timer;
            local_timer.start();
            
            int iter = 0;
            double diff;
            do {
                equation.compute_for_solver<Jacobi>(u_k_jacobi, u_kp1_jacobi, mesh);
                diff = u_kp1_jacobi.max_difference(u_k_jacobi);
                u_k_jacobi = u_kp1_jacobi;
                iter++;
            } while (iter < config.max_iterations && diff > config.epsilon);
            
            local_timer.stop();
            jacobi_time = local_timer.elapsed_time();
        });
        
        // Thread pour la méthode de Gauss-Seidel
        std::thread gauss_thread([this, &gauss_time]() {
            Timer local_timer;
            local_timer.start();
            
            int iter = 0;
            double diff;
            do {
                equation.compute_for_solver<GaussSeidel>(u_k_gauss, u_kp1_gauss, mesh);
                diff = u_kp1_gauss.max_difference(u_k_gauss);
                u_k_gauss = u_kp1_gauss;
                iter++;
            } while (iter < config.max_iterations && diff > config.epsilon);
            
            local_timer.stop();
            gauss_time = local_timer.elapsed_time();
        });
        
        // Synchronisation : attente de la fin des deux threads
        jacobi_thread.join();
        gauss_thread.join();
        
        // Affichage des résultats
        std::cout << "Temps d'exécution de Jacobi avec thread : " << jacobi_time << " ms" << std::endl;
        std::cout << "Temps d'exécution de Gauss-Seidel avec thread : " << gauss_time << " ms" << std::endl;
        
        total_timer.stop();
        std::cout << "Temps total d'exécution avec thread : ";
        total_timer.print();
    }

    /**
     * @brief Version avec std::async pour comparaison
     * Cette version permet de choisir entre exécution séquentielle (deferred) 
     * ou parallèle (async) via le paramètre launch_policy
     */
    void solve_parallel_async(std::launch launch_policy = std::launch::async) {
        Timer total_timer;
        total_timer.start();
        
        // Calcul de la solution exacte (thread principal uniquement)
        equation.compute_exact_solution(u_ref, mesh);
        
        // Initialisation des conditions initiales (thread principal uniquement)
        equation.compute_initial_condition(u_k_jacobi, mesh);
        equation.compute_initial_condition(u_k_gauss, mesh);
        
        // Lancement des calculs avec la politique spécifiée
        auto jacobi_future = std::async(launch_policy, [this]() {
            Timer local_timer;
            local_timer.start();
            
            int iter = 0;
            double diff;
            do {
                equation.compute_for_solver<Jacobi>(u_k_jacobi, u_kp1_jacobi, mesh);
                diff = u_kp1_jacobi.max_difference(u_k_jacobi);
                u_k_jacobi = u_kp1_jacobi;
                iter++;
            } while (iter < config.max_iterations && diff > config.epsilon);
            
            local_timer.stop();
            return local_timer.elapsed_time();
        });
        
        auto gauss_future = std::async(launch_policy, [this]() {
            Timer local_timer;
            local_timer.start();
            
            int iter = 0;
            double diff;
            do {
                equation.compute_for_solver<GaussSeidel>(u_k_gauss, u_kp1_gauss, mesh);
                diff = u_kp1_gauss.max_difference(u_k_gauss);
                u_k_gauss = u_kp1_gauss;
                iter++;
            } while (iter < config.max_iterations && diff > config.epsilon);
            
            local_timer.stop();
            return local_timer.elapsed_time();
        });
        
        // Récupération des résultats
        double jacobi_time = jacobi_future.get();
        double gauss_time = gauss_future.get();
        
        // Affichage des résultats
        std::string mode = (launch_policy == std::launch::async) ? "async" : "deferred";
        std::cout << "Temps d'exécution de Jacobi avec " << mode << " : " << jacobi_time << " ms" << std::endl;
        std::cout << "Temps d'exécution de Gauss-Seidel avec " << mode << " : " << gauss_time << " ms" << std::endl;
        
        total_timer.stop();
        std::cout << "Temps total d'exécution avec " << mode << " : ";
        total_timer.print();
    }
    
    /**
     * @brief Résout le système avec la méthode de Jacobi en utilisant la parallélisation TBB
     * 
     * Cette méthode utilise Intel TBB pour paralléliser la boucle de calcul de la méthode
     * de Jacobi uniquement, car Gauss-Seidel n'est pas parallélisable simplement
     * (dépendance sur i-1).
     */
    void solve_parallel_stl() {
        Timer total_timer;
        Timer solver_timer;
        
        total_timer.start();
        
        // Calcul de la solution exacte
        equation.compute_exact_solution(u_ref, mesh);
        
        // Initialisation des conditions initiales
        equation.compute_initial_condition(u_k_jacobi, mesh);
        
        int iter = 0;
        double diff;
        
        // Démarrage du timer pour la méthode itérative
        solver_timer.start();
        
        do {
            // Parallélisation avec TBB
            tbb::parallel_for(tbb::blocked_range<size_t>(1, mesh->x_size() - 1),
                [this](const tbb::blocked_range<size_t>& range) {
                    for(size_t i = range.begin(); i != range.end(); ++i) {
                        u_kp1_jacobi[i] = (u_k_jacobi[i-1] + u_k_jacobi[i+1]) / 2.0;
                    }
                });
            
            // Mise à jour des conditions aux limites
            equation.compute_boundary_condition(u_kp1_jacobi, *mesh);
            
            // Calcul de la différence et mise à jour
            diff = u_kp1_jacobi.max_difference(u_k_jacobi);
            u_k_jacobi = u_kp1_jacobi;
            
            iter++;
        } while (iter < config.max_iterations && diff > config.epsilon);
        
        solver_timer.stop();
        
        std::cout << "Temps d'exécution de Jacobi avec parallélisation TBB : ";
        solver_timer.print();
        
        total_timer.stop();
        std::cout << "Temps total d'exécution avec parallélisation TBB : ";
        total_timer.print();
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
