#pragma once
#include <string>
#include <vector>
#include <iostream>
class Element
{
	bool _water = false,
		_earth = false,
		_air = false,
		_fire = false,
		_compound = false;
	std::string _name;
	int _quantity;

	void _copy(const Element& other);
public:
	Element(std::string name = "", int quantity = 0);
	~Element();
	Element(const Element& other);
	Element& operator=(const Element& other);

	virtual bool operator==(const Element& other) const;

	void setName(const std::string name);
	std::string getName()const;

	void setQuantity(int quantity);
	int getQuantity()const;

	bool getCompaund() const;
	void setCompound(bool compound);

	void setCompatibility(bool water = false, bool earth = false,
		bool air = false, bool fire = false);
	bool reactWithWater() const;
	bool reactWithEarth() const;
	bool reactWithAir() const;
	bool reactWithFire() const;
	bool isBase();

	void print();
};

