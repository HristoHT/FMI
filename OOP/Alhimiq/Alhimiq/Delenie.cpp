#include "Delenie.h"

Delenie::Delenie(std::vector<Element> elements, std::vector<Element> result): Formula(elements, result) {}

bool Delenie::isValid() const {
	return true;
}