#pragma once
#include<vector>
#include<string>
#include<iostream>
#include "Functions.h"
class Table
{
public:
	Table(std::vector<std::string> columns);
	void push(std::vector<std::string> row);
	class Row {
		std::vector<std::string> _row;
	public:
		Row(std::vector<std::string> row = {});
		void print(std::vector<size_t> len);
	};
	void print();
private:
	Row _columns;
	std::vector<Row> _data;
	std::vector<size_t> _len;
};

