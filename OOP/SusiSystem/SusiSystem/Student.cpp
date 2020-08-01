#include "Student.h"

std::vector<std::string> studentStatuses = { "Studing", "Interrupt", "Graduated" };

Student::Student(std::string name, int group, int fn, Program* program) {
	setName(name);
	setGroup(group);
	setFn(fn);
	setProgram(program);
	setCourse(0);
}

Student::~Student() {
	for (Course* x : _courses)
		delete static_cast<StudentCourse*>(x);
}

void Student::_copy(const Student& other) {
	if (this != &other) {
		setName(other.getName());
		setGroup(other.getGroup());
		setFn(other.getFn());
		setProgram(other.getProgram());
		setCourse(other.getCourse());
		setCourses(other.getCourses());
	}
}

Student::Student(const Student& other) {
	_copy(other);
}

Student& Student::operator=(const Student& other) {
	_copy(other);
	return *this;
}

Course& Student::operator[](size_t i) {
	if (i < _courses.size()) {
		return *_courses[i];
	}

	throw std::runtime_error(std::string("Index is too large!"));
}

Course Student::operator[](size_t i) const {
	if (i < _courses.size()) {
		return *_courses[i];
	}

	throw std::runtime_error(std::string("Index is too large!"));
}

Course& Student::getCurrentCourse() {
	if (getCourse() < _courses.size()) {
		return *_courses[getCourse()];
	}

	throw std::runtime_error(std::string("Something wrong int getCurrentCourse!"));
}

void Student::setCourses(std::vector<Course*> courses) {
	_courses.clear();

	for (Course* course : courses) {
		StudentCourse* newcourse = new StudentCourse(*course);
		newcourse->setStudent(this);
		_courses.push_back(newcourse);
	}
}

void Student::interuptStudent() {
	if (getStatus() == 1)throw std::runtime_error(std::string("Student with faculty number ") + std::to_string(getFn()) + std::string(" had been interupted."));
	else if(getStatus() == 2)throw std::runtime_error(std::string("Student with faculty number ") + std::to_string(getFn()) + std::string(" had been graduated."));
	
	setStatus(1);
}

void Student::graduateStudent() {
	if (getStatus() == 1)throw std::runtime_error(std::string("Student with faculty number ") + std::to_string(getFn()) + std::string(" had been interupted."));
	else if(getStatus() == 2)throw std::runtime_error(std::string("Student with faculty number ") + std::to_string(getFn()) + std::string(" had been graduated."));
	
	setStatus(2);
}

void Student::resumeStudent() {
	if (getStatus() == 0)throw std::runtime_error(std::string("Student with faculty number ") + std::to_string(getFn()) + std::string(" is studing."));
	else if(getStatus() == 2)throw std::runtime_error(std::string("Student with faculty number ") + std::to_string(getFn()) + std::string(" had been graduated."));
	
	setStatus(0);
}

std::vector<Course*> Student::getCourses() const {
	return _courses;
}

void Student::addCourse(Course* newcourse) {
	StudentCourse* newstudentcourse = new StudentCourse(*newcourse);
	newstudentcourse->setStudent(this);
	_courses.push_back(newstudentcourse);
}

void Student::setProgram(Program* program) {
	_program = program;
}

Program* Student::getProgram() const {
	return _program;
}

void Student::setStatus(int status) {
	_status = status;
}

void Student::setGroup(int group) {
	_group = group;
}

void Student::setFn(int fn) {
	_fn = fn;
}

int Student::getStatus() const {
	return _status;
}

int Student::getGroup() const {
	return _group;
}

int Student::getCourse() const {
	return _course;
}

int Student::getFn() const {
	return _fn;
}

void Student::setCourse(int course) {
	_course = course;
	if (_program != nullptr)
		_program->loadMandatorySubjectsToStudent(this, course);
}

void Student::advanceCourse() {
	setCourse(getCourse() + 1);
}

void Student::setName(std::string name) {
	_name = name;
}

std::string Student::getName() const {
	return _name;
}
void Student::calculateAverageGrade() {
	_averageGrade = 6.66;
}

double Student::getAverageGrade() const {
	return _averageGrade;
}

std::vector<Subject*> Student::getNotpassedSubjects() {
	std::vector<Subject*>
		notpassed;

	FilterAdaptor<Course*>
		ifNotPassed{
			[](Course* currentcourse) -> bool {
				return !(static_cast<StudentCourse*>(currentcourse)->getStatus());
			}
	};

	MapAdaptor<Course*, std::vector<Subject*>>
		getSubjects{
			[](Course* course) -> std::vector<Subject*> {

				std::function<bool(Subject*)> ifNotPassed = [](Subject* currentSubject) -> bool {
					return (static_cast<StudentSubject*>(currentSubject)->getStatus() != 1);
				};

				std::vector<Subject*>
					subjects = find_all_if(*course, ifNotPassed);

				return subjects;
			}
	};

	// Вектор от клас Course -> филтриран вектор от клас Course -> Вектор от вектори клас Subject
	for (std::vector<Subject*> subjects : _courses | ifNotPassed | getSubjects ) {
		for (Subject* x : subjects) {
			notpassed.push_back(x);
		}
	}

	return notpassed;
}

void Student::printStudentInfo(std::ostream& out, size_t offset) {
	printElement("", offset, out);
	printElement(getFn(), 5, out);
	printElement(getName(), 10, out);
	printElement(getCourse(), 2, out);
	printElement(getGroup(), 2, out);
	printElement(studentStatuses[getStatus()], 11, out);
	//printElement(this, 10, out);
	out << "\n";
}

void Student::printCourses(std::ostream& out, size_t offset) {
	for (Course* course : _courses) {
		course->print();
	}
}
	
std::vector<Course*>::iterator Student::begin() {
	return _courses.begin();
}

std::vector<Course*>::iterator Student::end() {
	return _courses.end();
}

void Student::accept(Visitor* v) {
	v->process_Student(this);
}

void Student::addCourse2(Course* c) {
	_courses.push_back(c);
}
