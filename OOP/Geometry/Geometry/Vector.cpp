#include "Vector.h"

Vector::Vector() {
	setXY(0, 0);
}

Vector::Vector(double x, double y) {
	setXY(x, y);
}

double Vector::getX() {
	return _x;
}

double Vector::getY() {
	return _y;
}

double Vector::len() {
	return sqrt(*this * *this);
}

void Vector::setXY(double x, double y) {
	_x = x;
	_y = y;
}

Vector Vector::rotate(double deg) {
	double rad = deg * M_PI / deg,
		Sin = sin(rad), Cos = cos(rad),
		newX = getX() * Cos - getY() * Sin,
		newY = getX() * Sin + getY() * Cos;
	
	return Vector(newX, newY);
}


double operator*(Vector a, Vector b) {
	return a.getX() * b.getX() + a.getY() * b.getY();
}

Vector operator+(Vector a, Vector b) {
	return Vector(a.getX() + b.getX(), a.getY() + b.getY());
}

std::ostream& operator<<(std::ostream& out, Vector a) {
	out << "(" << a.getX() << ", " << a.getY() << ")";

	return out;
}