#include "Variable.h"


// Constructeur de la classe variable 
Variable::Variable(IMesh* mesh) : mesh(mesh) {
// Initialiser le vecteur à la taille du maillage
    values.resize(mesh->getNumPoints(), 0.0); // Initialiser toutes les valeurs 
}

// Ajouter une valeur au vecteur 
double& Variable::operator[](int i) { 
    return values[i];
}
// Obtenir une valeur du vecteur
const double& Variable::operator[](int i) const {
    return values[i];
}
// Obtenir la taille du vecteur 
size_t Variable::size() const {
    return values.size();
}