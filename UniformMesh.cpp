#include "UniformMesh.h"
#include <stdexcept>

// Définition du constructeur de la classe UniformMesh
UniformMesh::UniformMesh(double x_min, double x_max, double dx)
    : x_min(x_min), x_max(x_max), dx(dx) {
    if (x_max <= x_min || dx <= 0) {
        throw std::invalid_argument("Maillage invalide : x_max doit être supérieur à x_min, et dx doit être positif.");
    }
    num_points = static_cast<int>((x_max - x_min) / dx) + 1;
}

// Redéfinition de la méthode getXMin()
double UniformMesh::getXMin() const {
    return x_min;
}

// Redéfinition de la méthode getXMax()
double UniformMesh::getXMax() const {
    return x_max;
}

// Redéfinition de la méthode getNumPoints()
int UniformMesh::getNumPoints() const {
    return num_points;
}

