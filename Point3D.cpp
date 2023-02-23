#include "Point3D.h"

Point3D::Point3D() : Point2D(0, 0) {
    z = 0;
}

Point3D::Point3D(int x, int y, int z) : Point2D (x, y) {
    this->z = z;
    setDistFrOrigin();
}

void Point3D::setDistFrOrigin() {
    distFrOrigin = sqrt((x * x) + (y * y) + (z * z));
}

int Point3D::getZ() {
    return z;
}

void Point3D::setZ(int z) {
    this->z = z;
}

bool Point3D::operator==(const Point3D& point){
    if(x == point.x && y == point.y && z == point.z) {
        return true;
    }
    else {
        return false;
    }
}

ostream& operator<<(ostream& out, Point3D& point) {
	out << "[" << right << setw(4) << point.getX() << "," << right << setw(5) << point.getY() << "," << right << setw(5) << point.getZ() << "]   " << fixed << setprecision(3) << point.getScalarValue();
	return out;
}