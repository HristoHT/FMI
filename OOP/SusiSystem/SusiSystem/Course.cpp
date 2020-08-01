#include "Course.h"

Course::Course(size_t name) {
	setName(name);
}

Course::~Course() {
	for (Subject* x : _subjects)
			delete x;
}

void Course::_copy(const Course& other) {
	if (this != &other) {
		setName(other.getName());
		for (Subject* oldsubject : other.getSubjects()) {
			Subject* newsubject = new Subject(*oldsubject);
			newsubject->setCourse(this);
			_subjects.push_back(newsubject);
		}
	}
}

Course::Course(const Course& other) {
	_copy(other);
}

Course& Course::operator=(const Course& other) {
	_copy(other);
	return *this;
}

void Course::setName(size_t name) {
	_name = name;
}

size_t Course::getName() const {
	return _name;
}

void Course::setSubjects(std::vector<Subject*> subjects) {
	_subjects = subjects;
}

std::vector<Subject*> Course::getSubjects() const {
	return _subjects;
}

void Course::addSubject(Subject* newsubject) {
	_subjects.push_back(newsubject);
}

void Course::addSubject(std::string name, bool mandatory) {
	Subject* existingSubject = findSubjectByName(name);

	if (existingSubject == nullptr) {
		Subject* newsubject = new Subject(name, mandatory, this);
		addSubject(newsubject);
	}
	else {
		existingSubject->print();
		throw std::runtime_error(std::string("Subject ") + name + std::string(" has been added already!"));
	}
}

void Course::removeSubject(Subject* removesubject) {
	std::remove(_subjects.begin(), _subjects.end(), removesubject);
}

Subject* Course::findSubjectByName(std::string subjectname) {
	for (Subject* subject : _subjects) {
		if (subject->getName() == subjectname)
			return subject;
	}

	return nullptr;
}

Subject& Course::operator[](size_t i) {
	if (i < _subjects.size()) {
		return *_subjects[i];
	}
	throw std::runtime_error(std::string("Index ") + std::to_string(i) + std::string(" is too large!"));
}

Subject Course::operator[](size_t i) const {
	if (i < _subjects.size()) {
		return *_subjects[i];
	}
	throw std::runtime_error(std::string("Index ") + std::to_string(i) + std::string(" is too large!"));
}

void Course::print(std::ostream& out, size_t offset) {
	printElement("", offset, out);
	printElement(std::string("Info for course ") + std::to_string(getName() + 1), 40, out);
	out << "\n";

	printElement("", offset + 1, out);
	printElement("Name", 30, out);
	printElement("Course", 30, out);
	printElement("Status", 30, out);
	out << "\n";

	for (Subject* subject : _subjects) {
		subject->print(out, offset + 1);
	}
}


Course::iterator Course::begin()
{
	return Course::iterator(0, _subjects);
}

Course::iterator Course::end()
{
	return Course::iterator(_subjects.size(), _subjects);
}

Course::iterator::iterator(size_t startPos, std::vector<Subject*>& v) :index(startPos), vector(v) {}

bool Course::iterator::operator==(const Course::iterator& other) {
	return index == other.index;
}

bool Course::iterator::operator!=(const Course::iterator& other) {
	return index != other.index;
}

Course::iterator& Course::iterator::operator++() {
	index++;
	return *this;
}

Subject* Course::iterator::operator*() {
	if (index >= vector.size())
	{
		throw std::out_of_range("Reading past end of vector.");
	}
	return vector[index];
}

void Course::accept(Visitor* v) {
	v->process_Course(this);
}