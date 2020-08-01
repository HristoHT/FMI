#include "Subject.h"

Subject::Subject(std::string name, bool mandatory, Course* course) {
	setName(name);
	setCourse(course);
	setMandatory(mandatory);
}

Subject::~Subject() {
}

void Subject::_copy(const Subject& other) {
	if (this != &other) {
		setName(other.getName());
		setCourse(other.getCourse());
		setMandatory(other.getMandatory());
	}
}

Subject::Subject(const Subject& other) {
	_copy(other);
}

Subject& Subject::operator=(const Subject& other) {
	_copy(other);
	return *this;
}

void Subject::setName(std::string name) {
	_name = name;
}

std::string Subject::getName() const {
	return _name;
}

void Subject::setCourse(Course* course) {
	_course = course;
}

Course* Subject::getCourse() const {
	return _course;
}

void Subject::setMandatory(bool mandatory) {
	_mandatory = mandatory;
}

bool Subject::getMandatory() const {
	return _mandatory;
}

void Subject::print(std::ostream& out, size_t offset) {
	printElement(" ", offset, out);
	printElement(getName(), 30, out);
	if (getCourse() != nullptr)
		printElement(getCourse()->getName(), 30, out);
	else
		printElement("", 30, out);
	printElement(getMandatory() ? "Mandatory" : "Not mandatory", 30, out);
	//printElement(this, 9, out);
	//printElement(getCourse(), 9, out);
	out << "\n";
}

void Subject::accept(Visitor* v) {
	v->process_Subject(this);
}