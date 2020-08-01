#pragma once
#include "Element.h"
class AirElement :
	public Element
{
public:
	AirElement(int quantity = 0, std::string name = "air");
	bool operator==(const Element& other) const;
};

