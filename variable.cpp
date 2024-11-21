#include "variable.h"


// Constructeur de la classe variable 
Variable::Variable(IMesh* mesh) : mesh(mesh) {

    if (!mesh){
        throw std :: invalid_argument("le maillage est nul ");
    }
    values.resize(mesh->x_size(), 0.0); 
}

// Ajouter une valeur au vecteur 
double& Variable::operator[](int i) { 
    if (i < 0 || i >= static_cast<int>(values.size())){
        throw std :: out_of_range ("index hors limites");
    }
    return values[i];
}
// Obtenir une valeur du vecteur
const double& Variable::operator[](int i) const {
    if (i < 0 || i >= static_cast<int>(values.size())) {
        throw std::out_of_range("index hors limites");
    }
    return values[i];
}
// Obtenir la taille du vecteur 
size_t Variable::size() const {
    return values.size();
}