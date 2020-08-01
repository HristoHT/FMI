#pragma once
#include "Element.h"

class MetalElement :
	public Element
{
public:
	MetalElement(int quantity = 0, std::string name = "metal");

	bool operator== (const Element& other) const;
};

class GoldElement :
	public Element
{
public:
	GoldElement(int quantity = 0, std::string name = "gold");
	bool operator== (const Element& other) const;
};

class StoneElement :
	public Element
{
public:
	StoneElement(int quantity = 0, std::string name = "stone");
	bool operator== (const Element& other) const;
};

class EnergyElement :
	public Element
{
public:
	EnergyElement(int quantity = 0, std::string name = "energy");
	bool operator== (const Element& other) const;
};

class SpiritElement :
	public Element
{
public:
	SpiritElement(int quantity = 0, std::string name = "spirit");
	bool operator== (const Element& other) const;
};

class PStone :
	public Element
{
public:
	PStone(int quantity = 0, std::string name = "pstone");
	bool operator== (const Element& other) const;
};

