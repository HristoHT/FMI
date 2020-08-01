#pragma once
#include "Element.h"
class EarthElement :
	public Element
{
public:	
	EarthElement(int quantity = 0, std::string name = "earth");
	bool operator== (const Element& other) const;
};

