#include "Functions.h"
const double EPSILON = 0.0001;

bool isAGreaterThanB(double a, double b) {
	return (a - b) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * EPSILON);
}

bool isALessThanB(double a, double b) {
	return (b - a) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * EPSILON);
}

bool isAEqualToB(double a, double b){
	return fabs(a - b) < EPSILON;
}