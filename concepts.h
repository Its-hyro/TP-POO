#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include "variable.h"

template<typename T>
concept SolverConcept = requires(T solver, Variable& u_k, Variable& u_kp1) {
    { solver.compute_iteration(u_k, u_kp1) };
};

template<typename F>
concept InitialConditionFunction = requires(F f, double x) {
    { f(x) } -> std::convertible_to<double>;
};

#endif 