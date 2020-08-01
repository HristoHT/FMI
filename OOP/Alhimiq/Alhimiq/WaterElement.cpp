#include "WaterElement.h"

WaterElement::WaterElement(int quantity, std::string name):Element(name, quantity) {
	setCompatibility(0, 0, 1, 1);
}

bool WaterElement::operator==(const Element& other) const {
	if (other.getName() == "water") {
		return reactWithWater();
	}
	else if (other.getName() == "air") {
		return reactWithAir();
	}
	else if (other.getName() == "fire") {
		return reactWithFire();
	}
	else if (other.getName() == "earth") {
		return reactWithEarth();
	}
}