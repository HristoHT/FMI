#pragma once
#include<iomanip>
#include<ostream>
#include<math.h>

template<typename T>
void printElement(T t, int width, std::ostream& out, bool left = true) {
	out << (left ? std::left : std::right) << std::setw(width) << std::setfill(' ') << t;
}

bool isAGreaterThanB(double a, double b);

bool isALessThanB(double a, double b);

bool isAEqualToB(double a, double b);