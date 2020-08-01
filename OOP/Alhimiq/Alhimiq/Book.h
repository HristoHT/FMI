#pragma once
#include "Formula.h"
#include "Uravnenie.h"
#include "Delenie.h"

class Book
{
	std::vector<Formula> formuli;

	void _copy(const Book& other);
public:
	Book();
	~Book();
	Book(const Book& other);
	Book& operator=(const Book& other);

	void addUravnenie(std::vector<Element> elements, std::vector<Element> result);
	void addDelenie(std::vector<Element> elements, std::vector<Element> result);
	std::vector<Formula> howToGenerateElement(std::string element);
	std::vector<Formula> getFormuli() const;

	void print();
};

