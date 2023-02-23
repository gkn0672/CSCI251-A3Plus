#include "Line2D.h"
Line2D::Line2D(Point2D pt1, Point2D pt2) {
    this->pt1 = pt1;
    this->pt2 = pt2;
    setLength();
}

void Line2D::setLength() {
    int x_diff = pt1.getX() - pt2.getX();
    int y_diff = pt1.getY() - pt2.getY();
    length = sqrt(pow(x_diff, 2) + pow(y_diff, 2));
}

Point2D Line2D::getPt1() {
    return pt1;
}

Point2D Line2D::getPt2() {
    return pt2;
}

double Line2D::getScalarValue() {
    return length;
}

void Line2D::setPt1(Point2D pt1) {
    this->pt1 = pt1;
}

void Line2D::setPt2(Point2D pt2) {
    this->pt2 = pt2;
}

bool Line2D::operator==(const Line2D& line) {
    if(pt1 == line.pt1) {
        if(pt2 == line.pt2) {
            return true;
        }
    }
    return false;
}

ostream& operator <<(ostream& out, Line2D& line) {
	out << "[" << right << setw(4) << line.getPt1().getX() << "," << right << setw(5) << line.getPt1().getY() << "]   " << "[" << right << setw(4) << line.getPt2().getX() << "," << right << setw(5) << line.getPt2().getY() << "]   " << fixed << setprecision(3) << line.getScalarValue();
	return out;
}