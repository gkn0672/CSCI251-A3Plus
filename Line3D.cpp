#include "Line3D.h"

Line3D::Line3D(Point3D pt1, Point3D pt2) {
    this->pt1 = pt1;
    this->pt2 = pt2;
    setLength();
}

void Line3D::setLength() {
    int x_diff = pt1.getX() - pt2.getX();
    int y_diff = pt1.getY() - pt2.getY();
    int z_diff = pt1.getZ() - pt2.getZ();
    length = sqrt(pow(x_diff, 2) + pow(y_diff, 2) + pow(z_diff, 2));
}

Point3D Line3D::getPt1() {
    return pt1;
}

Point3D Line3D::getPt2() {
    return pt2;
}

void Line3D::setPt1(Point3D pt1) {
    this->pt1 = pt1;
}

void Line3D::setPt2(Point3D pt2) {
    this->pt2 = pt2;
}

bool Line3D::operator==(const Line3D& line) {
    if(pt1 == line.pt1) {
        if(pt2 == line.pt2) {
            return true;
        }
    }
    return false;
}

ostream& operator <<(ostream& out, Line3D& line) {
	out << "[" << right << setw(4) << line.getPt1().getX() << "," << right << setw(5) << line.getPt1().getY() << "," << right << setw(5) << line.getPt1().getZ() << "]   " << "[" << right << setw(4) << line.getPt2().getX() << "," << right << setw(5) << line.getPt2().getY() << "," << right << setw(5) << line.getPt2().getZ() << "]   " << fixed << setprecision(3) << line.getScalarValue();
	return out;
}