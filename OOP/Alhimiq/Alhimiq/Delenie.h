#pragma once
#include "Formula.h"
class Delenie :
	public Formula
{
public:
	Delenie(std::vector<Element> elements = {}, std::vector<Element> result = {});
	bool isValid() const;
};

