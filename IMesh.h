#ifndef IMESH_H
#define IMESH_H

#include <cstddef>

class IMesh {
public:
    virtual ~IMesh() = default;
    
    virtual double getXMin() const = 0;
    virtual double getXMax() const = 0;
    virtual int getNumPoints() const = 0;
    virtual double getX(int i) const = 0;
    virtual size_t x_size() const = 0;
};

#endif // IMESH_H
