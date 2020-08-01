#include "Formula.h"

Formula::Formula(std::vector<Element> elements, std::vector<Element> result) {
	_result = result;
	_elements = elements;
}

Formula::~Formula() {

}

void Formula::_copy(const Formula& other) {
	if (this != &other) {
		_result = other.getResult();
		_elements = other.getElements();
		setIsValid(other.isValid());
	}
}

Formula::Formula(const Formula& other) {
	_copy(other);
}

Formula& Formula::operator=(const Formula& other) {
	_copy(other);
	return *this;
}

bool Formula::isValid() const {
	return _isValid;
}

void Formula::setIsValid(bool isvalid) {
	_isValid = isvalid;
}

std::vector<Element> Formula::getResult() const {
	return _result;
}

std::vector<Element> Formula::getElements() const {
	return _elements;
}

void Formula::print() {
	for (size_t i = 0; i < _elements.size(); i++) {
		_elements[i].print();
		if (i + 1 != _elements.size())std::cout << "+ ";
	}
	std::cout << "= ";
	for (size_t i = 0; i < _result.size(); i++) {
		_result[i].print();
		if (i + 1 != _result.size())std::cout << "+ ";
	}

	std::cout << std::endl;
}

bool Formula::isBase() {
	for (size_t i = 0; i < _elements.size(); i++) {
		if (_elements[i].getName() != "water" &&
			_elements[i].getName() != "fire" &&
			_elements[i].getName() != "earth" &&
			_elements[i].getName() != "air") return false;
	}

	return true;
}

std::vector<int> Formula::countBaseElements() {
	int water = 0, fire = 0, earth = 0, air = 0;
	for (size_t i = 0; i < _elements.size(); i++) {
		if (_elements[i].getName() == "water") water++;
		else if (_elements[i].getName() == "fire") fire++;
		else if (_elements[i].getName() == "earth") earth++;
		else if (_elements[i].getName() == "air") air++;
	}

	return std::vector<int> {water, fire, earth, air};
}