#ifndef IMESH_H
#define IMESH_H

class IMesh {
public:
    virtual ~IMesh() = default;  // Destructeur virtuel pour garantir la destruction correcte des classes dérivées

    // Méthodes virtuelles pures
    virtual double getXMin() const = 0;
    virtual double getXMax() const = 0;
    virtual int getNumPoints() const = 0;
    virtual double getX(int i) const = 0;
};

#endif // IMESH_H
