#include "Element.h"

Element::Element(std::string name, int quantity) {
	setName(name);
	setQuantity(quantity);
	setCompatibility(0, 0, 0, 0);
	setCompound(false);
}

Element::~Element() {

}

void Element::_copy(const Element& other) {
	if (this != &other) {
		setQuantity(other.getQuantity());
		setName(other.getName());
		setCompatibility(other.reactWithWater(),
			other.reactWithEarth(), other.reactWithAir(), other.reactWithFire());
		setCompound(other.getCompaund());
	}
}

Element::Element(const Element& other) {
	_copy(other);
}

Element& Element::operator=(const Element& other) {
	_copy(other);
	return *this;
}

bool Element::operator==(const Element& other) const {
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
	else if (other.getName() == "metal") {
		return reactWithFire() && reactWithEarth();
	}
	else if (other.getName() == "stone") {
		return reactWithFire() && reactWithWater();
	}
	else if (other.getName() == "energy") {
		return reactWithAir() && reactWithWater();
	}
	else if (other.getName() == "spirit") {
		return reactWithAir();
	}
	else if (other.getName() == "gold") {
		return reactWithEarth() && reactWithFire();
	}
	else if (other.getName() == "pstone") {
		return reactWithEarth() && reactWithFire() && reactWithWater() && reactWithAir();
	}
}

void Element::setName(const std::string name) {
	_name = name;
}

std::string Element::getName() const {
	return _name;
}

void Element::setQuantity(int quantity) {
	_quantity = quantity;
}

int Element::getQuantity() const {
	return _quantity;
}

void Element::setCompatibility(bool water, bool earth, bool air, bool fire) {
	_water = water;
	_earth = earth;
	_air = air;
	_fire = fire;
}

bool Element::reactWithWater() const {
	return _water;
}

bool Element::reactWithEarth() const {
	return _earth;
}

bool Element::reactWithAir() const {
	return _air;
}

bool Element::reactWithFire() const {
	return _fire;
}

bool Element::getCompaund() const {
	return _compound;
}

void Element::setCompound(bool compound) {
	_compound = compound;
}

void Element::print() {
	std::cout << getName() << " ";
}

bool Element::isBase() {
	return (_name == "water") || (_name == "fire") || (_name == "earth") || (_name == "air");
}