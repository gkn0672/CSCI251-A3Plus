#ifndef Point3D_H
#define Point3D_H

#include "Point2D.h"

class Point3D : public Point2D {
    protected:
        int z;
        void setDistFrOrigin();

    public:
        Point3D();
        Point3D(int, int, int);
        int getZ();
        void setZ(int);
        bool operator==(const Point3D &);
};

ostream& operator<<(ostream&, Point3D&);
#endif