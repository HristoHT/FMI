#include "Date.h"
/*Date::Date() {
	_month = (std::to_string)(today->tm_mon + 1);
	_day = (std::to_string)(today->tm_mday);
	_year = (std::to_string)(today->tm_year + 1900);

	_date = today->tm_year + 1900;
	_date *= 100 + today->tm_mon + 1;
	_date *= 100 + today->tm_mday;
}*/

Date::Date(int day, int month, int year) {
	if (year == -1) {
		_year = (std::to_string)(today->tm_year + 1900);
		_date = today->tm_year + 1900;
	}
	else {
		_year = std::to_string(year);
		_date = year / 1000 == 0 ? year + 1000 : year;
	}

	if (month == -1 || (month < 0 || month > 12)) {
		_month = (std::to_string)(today->tm_mon + 1);
		_date = _date * 100 + today->tm_mon + 1;
	}
	else {
		_month = std::to_string(month);
		_date = _date * 100 + month;
	}

	if (day == -1 || (day < 0 || day > 31)) {
		_day = (std::to_string)(today->tm_mday);
		_date = _date * 100 + today->tm_mday;
	}
	else {
		_day = std::to_string(day);
		_date = _date * 100 + day;
	}
}

Date::~Date() {

}

void Date::_copy(const Date& other) {
	if (this != &other) {
		setDay(other.getDay());
		setMonth(other.getMonth());
		setYear(other.getYear());
		setDate(other.getDate());
	}
}

Date::Date(const Date& date) {
	_copy(date);
}

Date& Date::operator=(const Date& other) {
	_copy(other);
	return *this;
}

void Date::setMonth(std::string month) {
	_month = month;
}

void Date::setDay(std::string day) {
	_day = day;
}

void Date::setYear(std::string year) {
	_year = year;
}

void Date::setDate(int date) {
	_date = date;
}

int Date::getDate() const {
	return _date;
}

std::string Date::getDay() const {
	if (_day.size() == 1) return "0" + _day;
	return _day;
}

std::string Date::getMonth() const {
	if (_month.size() == 1) return "0" + _month;
	return _month;
}

std::string Date::getYear() const {
	if (_year.size() == 1) return "200" + _year;
	else if (_year.size() == 2) return "20" + _year;
	else if (_year.size() == 3) return "2" + _year;

	return _year;
}

std::string Date::getISODate() {
	return getYear() + std::string("-") + getMonth() + std::string("-") + getDay();
}

std::string Date::getByElements() {
	return getYear() + std::string("|") + getMonth() + std::string("|") + getDay();
}

bool Date::operator== (const Date& other) {
	return getDate() == other.getDate();
}

bool Date::operator< (const Date& other) {
	return getDate() < other.getDate();
}

bool Date::operator> (const Date& other) {
	return getDate() > other.getDate();
}

bool Date::operator<= (const Date& other) {
	return getDate() <= other.getDate();
}

bool Date::operator>= (const Date& other) {
	return getDate() >= other.getDate();
}