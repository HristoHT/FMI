#include "StoreOperation.h"

StoreOperation::StoreOperation(std::string type, std::string content) {
	_type = type;
	_date = Date();
	_content = content;
}

StoreOperation::StoreOperation() {
	_type = "Unknown";
	_date = Date();
	_content = "No content";
}

void StoreOperation::_copy(const StoreOperation& other) {
	if (this != &other) {
		_type = other._type;
		_date = other._date;
		_content = other._content;
	}
}

StoreOperation::StoreOperation(const StoreOperation& other) {
	_copy(other);
}

StoreOperation& StoreOperation::operator=(const StoreOperation& other) {
	_copy(other);
	return *this;
}

bool StoreOperation::operator<=(const StoreOperation& other) {
	return _date <= other._date;
}

bool StoreOperation::operator>=(const StoreOperation& other) {
	return _date >= other._date;
}

StoreOperation::~StoreOperation() {

}

void StoreOperation::print(std::ostream& out) {
	out << _type << "|" << _date.getByElements() << "|" << _content << "\n";
}