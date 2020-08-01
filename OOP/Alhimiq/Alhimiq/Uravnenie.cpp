#include "Uravnenie.h"

Uravnenie::Uravnenie(std::vector<Element> elements, std::vector<Element> result) : Formula(elements, result) {

}

bool Uravnenie::isValid() const {
	bool react = true;
	for (size_t i = 1; i < _elements.size(); i++) {
		//for (size_t j = i + 1; j < _elements.size(); j++) {
		react = react && (_elements[i - 1] == _elements[i]);
		//}
	}

	return react;
}