#ifndef Line3D_H
#define Line3D_H

#include "Point3D.h"
#include "Line2D.h"

class Line3D : public Line2D
{
    Point3D pt1;
    Point3D pt2;

    protected:
        void setLength();

    public:
        Line3D(){};
        Line3D(Point3D, Point3D);
        
        Point3D getPt1();
        Point3D getPt2();

        void setPt1(Point3D);
        void setPt2(Point3D);

        bool operator==(const Line3D &);
};
ostream& operator <<(ostream&, Line3D&);
#endif