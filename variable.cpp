#include "variable.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <spdlog/spdlog.h>
#include <numeric>

Variable::Variable(std::shared_ptr<IMesh> mesh, const std::string& name)
    : mesh(mesh), name(name) {
    if (!mesh) throw std::invalid_argument("Le maillage est nul");
    values.resize(mesh->getNumPoints(), 0.0);
}

Variable::Variable(std::shared_ptr<IMesh> mesh)
    : Variable(mesh, "unnamed") {
}

Variable::Variable(const Variable& other)
    : values(other.values), mesh(other.mesh), name(other.name) {
}

Variable& Variable::operator=(const Variable& other) {
    if (this != &other) {
        values = other.values;
        mesh = other.mesh;
        name = other.name;
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
    
    std::vector<double> differences(size());
    std::transform(values.begin(), values.end(),
                  other.values.begin(),
                  differences.begin(),
                  [](double a, double b) { return std::abs(a - b); });
    
    return *std::max_element(differences.begin(), differences.end());
}

void Variable::print() const {
    spdlog::info("Variable: {}", name);
    
    // Export vers un fichier de données
    std::string filename = name + ".dat";
    std::ofstream file(filename);
    
    if (!file) {
        spdlog::error("Impossible d'ouvrir le fichier {}", filename);
        return;
    }
    
    // Écriture des données (x, valeur)
    std::vector<size_t> indices(size());
    std::iota(indices.begin(), indices.end(), 0);
    
    for(size_t i : indices) {
        file << mesh->getX(i) << " " << values[i] << "\n";
    }
    
    file.close();
    spdlog::info("Données exportées dans {}", filename);
    
    // Export au format VTK
    std::string vtk_filename = name + ".vtk";
    std::ofstream vtk_file(vtk_filename);
    
    if (!vtk_file) {
        spdlog::error("Impossible d'ouvrir le fichier {}", vtk_filename);
        return;
    }
    
    // En-tête VTK
    vtk_file << "# vtk DataFile Version 3.0\n";
    vtk_file << "Variable " << name << "\n";
    vtk_file << "ASCII\n";
    vtk_file << "DATASET STRUCTURED_GRID\n";
    vtk_file << "DIMENSIONS " << size() << " 1 1\n";
    vtk_file << "POINTS " << size() << " float\n";
    
    // Points du maillage
    for(size_t i : indices) {
        vtk_file << mesh->getX(i) << " 0.0 0.0\n";
    }
    
    // Données
    vtk_file << "\nPOINT_DATA " << size() << "\n";
    vtk_file << "SCALARS " << name << " float 1\n";
    vtk_file << "LOOKUP_TABLE default\n";
    
    for(double val : values) {
        vtk_file << val << "\n";
    }
    
    vtk_file.close();
    spdlog::info("Données exportées au format VTK dans {}", vtk_filename);
}