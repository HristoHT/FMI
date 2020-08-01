#include "Subject.h"

std::vector<std::string> statuses = { "Not graded", "Graded", "Failed" };

StudentSubject::StudentSubject(std::string name, bool mandatory, Course* course,
	int status, double grade) {
	setName(name);
	setCourse(course);
	setMandatory(mandatory);
	setStatus(status);
	setGrade(grade);
}

void StudentSubject::_copy(const Subject& other) {
	if (this != &other) {
		setName(other.getName());
		setCourse(other.getCourse());
		setMandatory(other.getMandatory());
		setStatus(0);
		setGrade(-1);
	}
}

void StudentSubject::_copy(const StudentSubject& other) {
	if (this != &other) {
		setName(other.getName());
		setCourse(other.getCourse());
		setMandatory(other.getMandatory());
		setStatus(other.getStatus());
		setGrade(other.getGrade());
	}
}

StudentSubject::StudentSubject(const Subject& other) {
	_copy(other);
}

StudentSubject& StudentSubject::operator=(const Subject& other) {
	_copy(other);
	return *this;
}

StudentSubject::StudentSubject(const StudentSubject& other) {
	_copy(other);
}

StudentSubject& StudentSubject::operator=(const StudentSubject& other) {
	_copy(other);
	return *this;
}

void StudentSubject::setStatus(int status) {
	_status = status;
}

int StudentSubject::getStatus() const {
	return _status;
}

void StudentSubject::setGrade(double grade) {
	if (isAGreaterThanB(grade, 3))setStatus(1);
	else setStatus(2);
	_grade = grade;
}

double StudentSubject::getGrade() const {
	return _grade;
}

void StudentSubject::print(std::ostream& out, size_t offset) {
	printElement(" ", offset, out);
	printElement(getName(), 30, out);
	if (getCourse() != nullptr)
		printElement(getCourse()->getName(), 30, out);
	else
		printElement("", 30, out);
	printElement(getMandatory() ? "Mandatory" : "Not mandatory", 15, out);
	printElement(statuses[getStatus()], 12, out);
	if (getGrade() == -1) {
		printElement("", 5, out);
	}
	else printElement(getGrade(), 5, out);
	//printElement(this, 9, out);
	//printElement(getCourse(), 9, out);
	out << "\n";
}

void StudentSubject::accept(Visitor* v) {
	v->process_StudentSubject(this);
}