#ifndef Line2D_H
#define Line2D_H
#include "Point2D.h"

class Line2D {
    protected:
        double length;
        virtual void setLength();
    
    public:
        Point2D pt1, pt2;
        Line2D(){};
        Line2D(Point2D, Point2D);
        Point2D getPt1();
        Point2D getPt2();
        double getScalarValue();
        void setPt1(Point2D);
        void setPt2(Point2D);
        bool operator==(const Line2D &);
};
ostream& operator <<(ostream&, Line2D&);
#endif
