#pragma once
#include "BlackMagic.h"
#include "Functions.h"
#include "Susi.h"
#include "Table.h"
class Line{
	std::string _line;
public:
	Line();

	std::string& string();
	std::string string() const;

	void execute(Susi* susi);
};

std::ostream& operator<<(std::ostream& out, Susi& s);
std::istream& operator>>(std::istream& input, Susi& susi);
std::istream& operator>>(std::istream& input, Line& l);
std::ostream& operator<<(std::ostream& out, const Line& l);