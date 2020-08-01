#pragma once
#pragma warning(disable : 4996)
#include<string>
#include <ctime>
#include<iostream>

class Date
{
	std::string _month, _day, _year;
	time_t _now = time(0);
	struct tm* today = std::localtime(&_now);
	int _date;

	void _copy(const Date& other);
public:
	//Date();
	Date(int day = -1, int month = -1, int year = -1);
	~Date();
	Date(const Date& other);
	Date& operator= (const Date& other);

	void setYear(std::string year);
	std::string getYear() const;
	
	void setDay(std::string day);
	std::string getDay() const;
	
	void setMonth(std::string month);
	std::string getMonth() const;

	void setDate(int date);
	int getDate() const;
	std::string getISODate();
	std::string getByElements();

	bool operator== (const Date& other);
	bool operator< (const Date& other);
	bool operator<= (const Date& other);
	bool operator> (const Date& other);
	bool operator>= (const Date& other);
};

