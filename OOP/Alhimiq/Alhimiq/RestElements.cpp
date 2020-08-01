#include "RestElements.h"

MetalElement::MetalElement(int quantity, std::string name) : Element(name, quantity) {
	setCompatibility(1, 1, 1, 1);
}

bool MetalElement::operator==(const Element& other) const{
	return other.reactWithEarth() && other.reactWithFire();
}

GoldElement::GoldElement(int quantity, std::string name) : Element(name, quantity) {
	setCompatibility(1, 1, 1, 1);
}

bool GoldElement::operator==(const Element& other) const {
	return other.reactWithEarth() && other.reactWithFire();
}

StoneElement::StoneElement(int quantity, std::string name) : Element(name, quantity) {
	setCompatibility(1, 1, 1, 1);
}

bool StoneElement::operator==(const Element& other) const {
	return other.reactWithWater() && other.reactWithFire();
}

EnergyElement::EnergyElement(int quantity, std::string name) : Element(name, quantity) {
	setCompatibility(1, 1, 1, 1);
}

bool EnergyElement::operator==(const Element& other) const {
	return other.reactWithWater() && other.reactWithAir();
}

SpiritElement::SpiritElement(int quantity, std::string name) : Element(name, quantity) {
	setCompatibility(1, 1, 1, 1);
}

bool SpiritElement::operator==(const Element& other) const {
	return other.reactWithAir();
}

PStone::PStone(int quantity, std::string name) : Element(name, quantity) {
	setCompatibility(1, 1, 1, 1);
}

bool PStone::operator==(const Element& other) const {
	return other.reactWithAir() && other.reactWithFire() && other.reactWithEarth() && other.reactWithWater();
}