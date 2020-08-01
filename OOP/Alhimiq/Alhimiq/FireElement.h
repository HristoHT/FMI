#pragma once
#include "Element.h"
class FireElement :
	public Element
{
public:
	FireElement(int quantity = 0, std::string name = "fire");
	bool operator==(const Element& other) const;
};

