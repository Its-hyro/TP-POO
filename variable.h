#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <memory>
#include <iterator>
#include "IMesh.h"

class Variable {
private:
    std::vector<double> values;             
    std::shared_ptr<IMesh> mesh;            // Utilisation de shared_ptr au lieu d'un pointeur brut

public:
    // Constructeurs
    explicit Variable(std::shared_ptr<IMesh> mesh);
    Variable(const Variable& other);         // Constructeur de copie
    Variable& operator=(const Variable& other); // Opérateur d'affectation
    
    // Accès aux éléments
    double& operator[](int i);              
    const double& operator[](int i) const;  

    // Itérateurs
    using iterator = std::vector<double>::iterator;
    using const_iterator = std::vector<double>::const_iterator;
    
    iterator begin() { return values.begin(); }
    iterator end() { return values.end(); }
    const_iterator begin() const { return values.begin(); }
    const_iterator end() const { return values.end(); }

    // Utilitaires
    size_t size() const;
    void reset(double value = 0.0);  // Réinitialise toutes les valeurs
    double max_difference(const Variable& other) const;  // Pour le calcul de convergence
};

#endif // VARIABLE_H