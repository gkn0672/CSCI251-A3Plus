#include "Point2D.h"

void Point2D::setDistFrOrigin() {
    distFrOrigin = sqrt((x * x) + (y * y));
}

int Point2D::getX() {
    return x;
}

int Point2D::getY() {
    return y;
}

double Point2D::getScalarValue() {
    return distFrOrigin;
}

void Point2D::setX(int x) {
    this->x = x;
}

void Point2D::setY(int y) {
    this->y = y;
}

bool Point2D::operator<(Point2D point)
{
	if (x == point.x)
		return y < point.y;
	else
		return x < point.x;
}

bool Point2D::operator>(Point2D point)
{
	if (x == point.x)
		return y > point.y;
	else
		return x > point.x;
}

bool Point2D::operator==(const Point2D& point) {
    if(x == point.x) {
        if(y == point.y) {
            return true;
        }
    }
    return false;
}

ostream& operator<<(ostream& out, Point2D& point)
{
	out << "[" << right << setw(4) << point.getX() << "," << right << setw(5) << point.getY() << "]   " << fixed << setprecision(3) << point.getScalarValue();
	return out;
}