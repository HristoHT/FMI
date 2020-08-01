#pragma once
#include "WaterElement.h"
#include "FireElement.h"
#include "EarthElement.h"
#include "AirElement.h"
#include "RestElements.h"

class Formula
{
	bool _isValid = true;
	void _copy(const Formula& other);

protected:
	std::vector<Element> _result;
	std::vector<Element> _elements;

public:
	Formula(std::vector<Element> elements = {}, std::vector<Element> result = {});
	~Formula();
	Formula(const Formula& other);
	Formula& operator=(const Formula& other);

	virtual bool isValid() const;
	void setIsValid(bool isvalid);

	std::vector<Element> getResult() const;
	std::vector<Element> getElements() const;
	
	bool isBase();
	std::vector<int> countBaseElements();

	void print();
};

