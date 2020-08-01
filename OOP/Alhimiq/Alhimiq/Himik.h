#pragma once
#include "Book.h"
#include <stack>
#include <queue>
class Himik
{
	Book foundbook;
	bool _canOptainPStone = false;
	int _water, _fire, _earth, _air;

	void _copy(const Himik& other);
public:
	Himik(int water = 0, int fire = 0, int eart = 0, int air = 0);
	~Himik();
	Himik(const Himik& other);
	Himik& operator= (const Himik& other);

	void addFoundFormula(std::string formula);
	void isItPossibleToOptainPS();
	bool canOptainPStone() const;
	Book getFoundBook() const;

	int getWater() const;
	int getEarth() const;
	int getAir() const;
	int getFire() const;
};

Element getElementByName(std::string name);
std::vector<Element> getElementsOfDelenie(std::string name);

std::vector<std::string> split(std::string str, std::string splitter);
std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");