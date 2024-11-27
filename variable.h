#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <memory>
#include <iterator>
#include <string>
#include "IMesh.h"

class Variable {
private:
    std::vector<double> values;             
    std::shared_ptr<IMesh> mesh;            
    std::string name;  // Nouveau champ pour le nom

public:
    // Nouveau constructeur avec nom
    Variable(std::shared_ptr<IMesh> mesh, const std::string& name)
        : mesh(mesh), name(name) {
        if (!mesh) throw std::invalid_argument("Le maillage est nul");
        values.resize(mesh->getNumPoints(), 0.0);
    }
    
    // Constructeur existant qui délègue au nouveau
    explicit Variable(std::shared_ptr<IMesh> mesh);
        
    // Les autres constructeurs et méthodes restent inchangés
    Variable(const Variable& other);         
    Variable& operator=(const Variable& other);
    
    double& operator[](size_t i);              
    const double& operator[](size_t i) const;  

    using iterator = std::vector<double>::iterator;
    using const_iterator = std::vector<double>::const_iterator;
    
    iterator begin() { return values.begin(); }
    iterator end() { return values.end(); }
    const_iterator begin() const { return values.begin(); }
    const_iterator end() const { return values.end(); }

    size_t size() const;
    void reset(double value = 0.0);
    double max_difference(const Variable& other) const;
    
    // Nouvelle méthode pour accéder au nom
    const std::string& getName() const { return name; }
};

#endif // VARIABLE_H