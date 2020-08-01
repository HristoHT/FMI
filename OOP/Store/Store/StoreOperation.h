#pragma once
#include<string>
#include "Date.h"
#include<iostream>

struct StoreOperation
{
	std::string _type, _content;
	Date _date;

	void _copy(const StoreOperation& other);
	StoreOperation();
	StoreOperation(std::string type, std::string content);
	~StoreOperation();
	StoreOperation(const StoreOperation& other);
	StoreOperation& operator= (const StoreOperation& other);
	bool operator <= (const StoreOperation& other);
	bool operator >= (const StoreOperation& other);
	void print(std::ostream& out = std::cout);
};

