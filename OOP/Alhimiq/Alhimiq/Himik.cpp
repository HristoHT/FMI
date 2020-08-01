#include "Himik.h"

Himik::Himik(int water, int fire, int eart, int air) {
	_canOptainPStone = false;
	_water = water;
	_fire = fire;
	_earth = eart;
	_air = air;
}

Himik::~Himik() {

}

void Himik::_copy(const Himik& other) {
	if (this != &other) {
		_canOptainPStone = other.canOptainPStone();
		foundbook = other.getFoundBook();
		_water = other.getWater();
		_fire = other.getFire();
		_earth = other.getEarth();
		_air = other.getAir();
	}
}

Himik::Himik(const Himik& other) {
	_copy(other);
}

Himik& Himik::operator=(const Himik& other) {
	_copy(other);
	return *this;
}

bool Himik::canOptainPStone() const {
	return _canOptainPStone;
}

Book Himik::getFoundBook() const {
	return foundbook;
}

int Himik::getWater() const {
	return _water;
}
int Himik::getEarth() const {
	return _earth;
}
int Himik::getAir() const {
	return _air;
}
int Himik::getFire() const {
	return _fire;
}

void Himik::addFoundFormula(std::string formula) {
	try {
		std::vector<std::string> isDelenie = split(formula, "/"),
			isUravnenie = split(formula, "=");

		std::vector<Element> result, elements;
		if (isDelenie.size() > 1) {
			result = getElementsOfDelenie(isDelenie[1]);
			elements.push_back(getElementByName(isDelenie[1]));

			foundbook.addDelenie(elements, result);
		}
		else if (isUravnenie.size() > 1) {
			std::vector<std::string> otherElements = split(isUravnenie[0], "+");
			result.push_back(getElementByName(isUravnenie[1]));

			for (size_t i = 0; i < otherElements.size(); i++) {
				elements.push_back(getElementByName(otherElements[i]));
			}

			foundbook.addUravnenie(elements, result);
		}

		//foundbook.print();
	}
	catch (const std::string e) {
		std::cout << e << "\n";
	}
}

void Himik::isItPossibleToOptainPS() {
	std::vector<Formula> waysToGenerateElement = foundbook.howToGenerateElement(PStone().getName());
	std::vector<std::pair<Formula, size_t>> qu;
	size_t lvl = 0;
	for (size_t i = 0; i < waysToGenerateElement.size(); i++) {
		qu.push_back(std::make_pair(waysToGenerateElement[i], -1));
	}
	size_t tracker = 0;
	while (!_canOptainPStone && lvl < qu.size() && tracker < 30) {
		std::pair<Formula, size_t> currentElement = qu[lvl];
		Formula formulaToWorkWith = currentElement.first;
		std::vector<Element> elements = formulaToWorkWith.getElements(),
			newElements;

		if (!formulaToWorkWith.isBase()) {
			bool flag = false;
			size_t i = 0;

			while (i < elements.size() && !flag) {
				if (!elements[i].isBase()) {
					flag = true;
					waysToGenerateElement = foundbook.howToGenerateElement(elements[i].getName());
				}
				i++;
			}

			elements.erase(elements.begin() + (i - 1));

			for (size_t i = 0; i < waysToGenerateElement.size(); i++) {
				if (!waysToGenerateElement[i].isValid()) continue;
				newElements = waysToGenerateElement[i].getElements();
				newElements.insert(newElements.end(), elements.begin(), elements.end());
				qu.push_back(std::make_pair(Uravnenie(newElements, formulaToWorkWith.getResult()), lvl));
				//Uravnenie(newElements, formulaToWorkWith.getResult()).print();
			}
		}
		else {
			std::vector<int> elementsNeeded = formulaToWorkWith.countBaseElements();
			if (_water >= elementsNeeded[0] && _fire >= elementsNeeded[1] &&
				_earth >= elementsNeeded[2] && _air >= elementsNeeded[3]) {
				std::stack<Formula> history;
				_canOptainPStone = true;
				while (currentElement.second != -1) {
					history.push(currentElement.first);
					currentElement = qu[currentElement.second];
				}
				history.push(currentElement.first);

				while (!history.empty()) {
					Formula firstElement = history.top();
					firstElement.print();
					history.pop();
				}
			}
		}
		tracker++;
		lvl++;
	}

	if (!_canOptainPStone)
		std::cout << "Himika ne uspq da nameri nachin da poluchi filosofskiq kamak :(\n";
}

std::string& ltrim(std::string& str, const std::string& chars)
{
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

std::string& rtrim(std::string& str, const std::string& chars)
{
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

std::string& trim(std::string& str, const std::string& chars)
{
	return ltrim(rtrim(str, chars), chars);
}

std::vector<std::string> split(std::string str, std::string splitter) {
	std::string attr;
	std::vector<std::string> r;
	size_t pos = 0;

	while ((pos = str.find(splitter)) != std::string::npos)
	{
		attr = str.substr(0, pos);
		str.erase(0, pos + splitter.length());
		r.push_back(trim(attr));
	}
	r.push_back(trim(str));
	return r;
}

Element getElementByName(std::string name) {
	if (name == "Water") {
		return WaterElement();
	}
	else if (name == "Fire") {
		return FireElement();
	}
	else if (name == "Earth") {
		return EarthElement();
	}
	else if (name == "Air") {
		return AirElement();
	}
	else if (name == "Metal") {
		return MetalElement();
	}
	else if (name == "Gold") {
		return GoldElement();
	}
	else if (name == "Stone") {
		return StoneElement();
	}
	else if (name == "Energy") {
		return EnergyElement();
	}
	else if (name == "Spirit") {
		return SpiritElement();
	}
	else if (name == "Philosopher's Stone") {
		return PStone();
	}

	throw std::string("->No such element '") + name + std::string("'");
}

std::vector<Element> getElementsOfDelenie(std::string name) {
	if (name == "Water") {
		return std::vector<Element>{ WaterElement(), WaterElement() };
	}
	else if (name == "Fire") {
		return std::vector<Element>{ FireElement(), FireElement() };
	}
	else if (name == "Earth") {
		return std::vector<Element>{ EarthElement(), EarthElement() };
	}
	else if (name == "Air") {
		return std::vector<Element>{ AirElement(), AirElement() };
	}
	else if (name == "Metal") {
		return std::vector<Element>{ EarthElement(), FireElement() };
	}
	else if (name == "Gold") {
		return std::vector<Element>{ MetalElement(), MetalElement() };
	}
	else if (name == "Stone") {
		return std::vector<Element>{ FireElement(), WaterElement() };
	}
	else if (name == "Energy") {
		return std::vector<Element>{ EnergyElement(), WaterElement() };
	}
	else if (name == "Spirit") {
		return std::vector<Element>{ AirElement(), AirElement() };
	}
	else if (name == "Philosopher's Stone") {
		return std::vector<Element>{ PStone(), PStone() };
	}

	throw std::string("No such element '") + name + std::string("'");
}