#ifndef Point2D_H
#define Point2D_H
#include <cmath>
#include <iostream>
#include <iomanip>
#include <ostream>
using namespace std;

class Point2D {
    protected:
        int x, y;
        double distFrOrigin;
        virtual void setDistFrOrigin();
    public:
        Point2D(){
            x = 0;
            y = 0;
        }
        Point2D(int x, int y) {
            this->x = x;
            this->y = y;
            setDistFrOrigin();
        }
        int getX();
        int getY();
        double getScalarValue();
        bool operator<(Point2D);
        bool operator>(Point2D);
        bool operator==(const Point2D &);
        void setX(int);
        void setY(int);

};

ostream& operator<<(ostream&, Point2D&);
#endif