#include "Variable.h"

Variable::Variable(IMesh* mesh) : mesh(mesh) {
    // Initialiser le vecteur à la taille du maillage
    values.resize(mesh->getNumPoints(), 0.0);
}

double& Variable::operator[](int i) {
    return values[i];
}

const double& Variable::operator[](int i) const {
    return values[i];
}

size_t Variable::size() const {
    return values.size();
}