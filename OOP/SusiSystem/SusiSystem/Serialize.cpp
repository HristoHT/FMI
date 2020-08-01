#include "Serialize.h"

Serialize::Serialize(std::ostream& out) : _out(out) {}

void Serialize::process_Subject(Subject* subject) {
	printElement("", 4, _out);
	_out << subject->getName() << "|" << subject->getMandatory() << "\n";
}

void Serialize::process_StudentSubject(StudentSubject* subject) {
	printElement("", 4, _out);
	_out << subject->getName() << "|" << subject->getMandatory() << "|" <<
		subject->getGrade() << "|" << subject->getStatus() << '\n';
}

void Serialize::process_Susi(Susi* susi) {
	_out << susi->getProgramsLen() << "|" << susi->getStudents().size() << "|" << susi->_fn<< "\n";

	for (Program* p : susi->getPrograms()) {
		process_Program(p);
	}

	/*for (Student* s : susi->getStudents()) {
		process_Student(s);
	}*/
}
void Serialize::process_Student(Student* student) {
	printElement("", 2, _out);
	_out << student->getName() << "|" << student->getStatus() << "|"
		<< student->getFn() << "|" << student->getGroup() << "|"
		<< student->getCourse() << "|" << student->getCourses().size() << '\n';

	for (Course* c : *student) {
		process_StudentCourse(static_cast<StudentCourse*>(c));
	}
}
void Serialize::process_StudentCourse(StudentCourse* course) {
	printElement("", 3, _out);
	_out << course->getName() << "|" << course->getSubjects().size() /*<< "|"
		<< course->getStatus()*/ << "\n";
	for (Subject* s : *course) {
		process_StudentSubject(static_cast<StudentSubject*>(s));
	}
}
void Serialize::process_Course(Course* course) {
	printElement("", 3, _out);
	_out << course->getName() << "|" << course->getSubjects().size() << "\n";
	for (Subject* s : *course) {
		process_Subject(s);
	}
}
void Serialize::process_Program(Program* program) {
	printElement("", 1, _out);
	_out << program->getName() << "|" <<
		program->getMandatoryCourses().size() << "|" <<
		program->getNotMandatoryCourses().size() << "|" <<
		program->getStudents().size() << '\n';

	for (Course* c : program->getMandatoryCourses()) {
		process_Course(c);
	}

	for (Course* c : program->getNotMandatoryCourses()) {
		process_Course(c);
	}

	for (Student* s : program->getStudents()) {
		process_Student(s);
	}
}