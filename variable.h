#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <memory>
#include <iterator>
#include <string>
#include "IMesh.h"
#include <fstream>
#include <spdlog/spdlog.h>

class Variable {
private:
    std::vector<double> values;             
    std::shared_ptr<IMesh> mesh;            
    std::string name;  // Nouveau champ pour le nom

public:
    // Déclaration uniquement des constructeurs
    Variable(std::shared_ptr<IMesh> mesh, const std::string& name);
    explicit Variable(std::shared_ptr<IMesh> mesh);
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

    void print(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("Impossible d'ouvrir le fichier " + filename);
        }
        
        // Ajout d'un en-tête pour gnuplot
        file << "# x\t" << name << "\n";
        
        // Export des données au format x y
        for (size_t i = 0; i < values.size(); ++i) {
            file << mesh->getX(i) << "\t" << values[i] << "\n";
        }
        
        spdlog::info("Données exportées dans {}", filename);
    }

    void print() const;
};

#endif // VARIABLE_H