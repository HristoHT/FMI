#pragma once
#include "Element.h"
class WaterElement :
	public Element
{
public:
	WaterElement(int quantity = 0, std::string name = "water");
	bool operator== (const Element& other) const;
};

