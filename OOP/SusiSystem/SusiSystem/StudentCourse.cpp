#include "Course.h"

StudentCourse::StudentCourse(size_t name, Student* student) {
	setName(name);
	setStudent(student);
}

StudentCourse::~StudentCourse() {
	for (Subject* x : _subjects)
		delete static_cast<StudentSubject*>(x);
}

void StudentCourse::_copy(const Course& other) {
	if (this != &other) {
		setName(other.getName());
		setStudent(nullptr);
		setStatus(0);
		for (Subject* oldsubject : other.getSubjects()) {
			StudentSubject* newsubject = new StudentSubject(*oldsubject);
			newsubject->setCourse(this);
			_subjects.push_back(newsubject);
		}
	}
}

void StudentCourse::_copy(const StudentCourse& other) {
	if (this != &other) {
		setStudent(nullptr);
		setStatus(other.getStatus());
		setName(other.getName());
		for (Subject* oldsubject : other.getSubjects()) {
			StudentSubject* newsubject = new StudentSubject(*oldsubject);
			newsubject->setCourse(this);
			_subjects.push_back(newsubject);
		}
	}
}

StudentCourse::StudentCourse(const Course& other) {
	_copy(other);
}

StudentCourse& StudentCourse::operator=(const Course& other) {
	_copy(other);
	return *this;
}

StudentCourse::StudentCourse(const StudentCourse& other) {
	_copy(other);
}

StudentCourse& StudentCourse::operator=(const StudentCourse& other) {
	_copy(other);
	return *this;
}

void StudentCourse::setStudent(Student* student) {
	_student = student;
}

Student* StudentCourse::getStudent() const {
	return _student;
}

void StudentCourse::setStatus(int status) {
	_status = status;
}

int StudentCourse::getStatus() const {
	return _status;
}

void StudentCourse::print(std::ostream& out, size_t offset) {
	printElement("", offset + 1, out);
	printElement(std::string("Info for course ") + std::to_string(getName() + 1), 30, out);
	out << "\n";

	printElement("", offset + 2, out);
	printElement("Name", 30, out);
	printElement("Course", 30, out);
	printElement("Status", 13, out);
	printElement(std::string("Average grade:") + std::to_string(averageGrade()), 10, out);
	//printElement(getStudent(), 10, out);
	out << "\n";

	for (Subject* subject : _subjects) {
		subject->print(out, offset + 2);
	}
}

void StudentCourse::accept(Visitor* v) {
	v->process_Course(this);
}

double StudentCourse::averageGrade() {
	double grade = 0., subjects = 0., avGrade;

	for (Subject* s : *this) {
		double sG = static_cast<StudentSubject*>(s)->getGrade();
		if (sG == -1) grade += 2.;
		else grade += sG;
		subjects += 1;
	}

	avGrade = grade / subjects;

	return isALessThanB(avGrade, 2.) ? 2.00 : avGrade;
}