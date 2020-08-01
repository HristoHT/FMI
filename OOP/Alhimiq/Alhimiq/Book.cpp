#include "Book.h"

Book::Book() {

}

Book::~Book() {
	//for (size_t i = 0; i < formuli.size(); i++)
			//if (formuli[i])delete formuli[i];
}

void Book::_copy(const Book& other) {
	if (this != &other) {
		formuli = other.getFormuli();
	}
}

Book::Book(const Book& other) {
	_copy(other);
}

Book& Book::operator= (const Book& other) {
	_copy(other);
	return *this;
}

void Book::addUravnenie(std::vector<Element> elements, std::vector<Element> result) {
	formuli.push_back(Uravnenie(elements, result));
}

void Book::addDelenie(std::vector<Element> elements, std::vector<Element> result) {
	formuli.push_back(Delenie(elements, result));
}

std::vector<Formula> Book::getFormuli() const {
	return formuli;
}

std::vector<Formula> Book::howToGenerateElement(std::string name) {
	std::vector<Formula> result;

	for (size_t i = 0; i < formuli.size(); i++) {
		bool flag = false;
		std::vector<Element> results = formuli[i].getResult();
		for (size_t j = 0; j < results.size(); j++) {
			if (name == results[j].getName())
				flag = true;
		}
		if (flag)
			result.push_back(formuli[i]);
	}

	return result;
}

void Book::print() {
	for (size_t i = 0; i < formuli.size(); i++) {
		std::cout << (formuli[i].isValid() ? "TRUE  " : "FALSE ");
		formuli[i].print();
	}
}