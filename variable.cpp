#include "variable.h"
#include <algorithm>
#include <stdexcept>

Variable::Variable(std::shared_ptr<IMesh> mesh) : mesh(mesh) {
    if (!mesh) {
        throw std::invalid_argument("Le maillage est nul");
    }
    values.resize(mesh->x_size(), 0.0);
}

Variable::Variable(const Variable& other) 
    : values(other.values), mesh(other.mesh) {}

Variable& Variable::operator=(const Variable& other) {
    if (this != &other) {
        values = other.values;
        mesh = other.mesh;
    }
    return *this;
}

double& Variable::operator[](size_t i) {
    if (i >= values.size()) {
        throw std::out_of_range("Index hors limites");
    }
    return values[i];
}

const double& Variable::operator[](size_t i) const {
    if (i >= values.size()) {
        throw std::out_of_range("Index hors limites");
    }
    return values[i];
}

size_t Variable::size() const {
    return values.size();
}

void Variable::reset(double value) {
    std::fill(values.begin(), values.end(), value);
}

double Variable::max_difference(const Variable& other) const {
    if (size() != other.size()) {
        throw std::invalid_argument("Les variables n'ont pas la même taille");
    }
    
    double max_diff = 0.0;
    for (size_t i = 0; i < size(); ++i) {
        max_diff = std::max(max_diff, std::abs(values[i] - other.values[i]));
    }
    return max_diff;
}