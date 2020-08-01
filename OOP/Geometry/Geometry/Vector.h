#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
class Vector
{
	double _x, _y, _len;
public:
	Vector();
	Vector(double x, double y);
	Vector rotate(double deg);

	void setXY(double x, double y);
	double getX();
	double getY();
	double len();

};

double operator*(Vector a, Vector b);
Vector operator+(Vector a, Vector b);
std::ostream& operator<<(std::ostream& out, Vector a);

