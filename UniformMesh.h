#ifndef UNIFORMMESH_H
#define UNIFORMMESH_H

#include "IMesh.h"

// Classe représentant un maillage uniforme
class UniformMesh : public IMesh {
private:
    double x_min, x_max, dx;  // Bornes du maillage et pas entre les points
    int num_points;          // Nombre de points dans le maillage

public:
    // Constructeur
    // x_min : borne inférieure
    // x_max : borne supérieure
    // dx : pas entre les points
    UniformMesh(double x_min, double x_max, double dx);

    // Retourne la borne inférieure du maillage
    double getXMin() const override;

    // Retourne la borne supérieure du maillage
    double getXMax() const override;

    // Retourne le nombre de points du maillage
    int getNumPoints() const override;

    // Retourne la position du point d'indice i
    double getX(int i) const override {return x_min + i * dx;}

    // Retourne la taille du maillage   
    size_t x_size() const override;
};


#endif // UNIFORMMESH_H