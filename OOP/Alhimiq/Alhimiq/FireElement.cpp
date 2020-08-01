#include "FireElement.h"

FireElement::FireElement(int quantity, std::string name) :Element(name, quantity) {
	setCompatibility(1, 1, 0, 1);
}

bool FireElement::operator==(const Element& other) const {
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