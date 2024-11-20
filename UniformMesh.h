#ifndef UNIFORMMESH_H
#define UNIFORMMESH_H

#include "IMesh.h"

// Définition de la classe UniformMesh qui hérite de IMesh
class UniformMesh : public IMesh {
private:
    double x_min, x_max, dx;
    int num_points;

public:
    // Constructeur de la classe UniformMesh
    UniformMesh(double x_min, double x_max, double dx);

    // Méthodes qui redéfinissent celles de la classe IMesh
    double getXMin() const override;
    double getXMax() const override;
    int getNumPoints() const override;
    double getX(int i) const override;
};

#endif // UNIFORMMESH_H
