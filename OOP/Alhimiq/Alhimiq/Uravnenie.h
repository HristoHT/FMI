#pragma once
#include "Formula.h"

class Uravnenie :
	public Formula
{
public:
	Uravnenie(std::vector<Element> elements = {}, std::vector<Element> result = {});
	bool isValid() const;
};

