#include "Susi.h"

size_t Susi::_fn;

Susi::Susi(size_t fnStart) {
	_fn = fnStart;
}

void Susi::_copy(const Susi& other) {
	if (this != &other) {
		_programs = other.getPrograms();
	}
}

Susi::Susi(const Susi& other) {
	_copy(other);
}

Susi::~Susi() {
	for (Program* x : _programs) {
		delete x;
	}
}

Susi& Susi::operator= (const Susi& other) {
	_copy(other);
	return *this;
}

//Range<FilteredIterator<std::vector<Program*>::iterator>>
std::vector<Program*>
Susi::getPrograms(std::string name) {
	FilterAdaptor<Program*> filterByName{ [&name](Program* prog) -> bool {
		return name == "" || prog->getName() == name;
	} };

	Range<FilteredIterator<std::vector<Program*>::iterator>> r = _programs | filterByName;

	return ~(Range<std::vector<Program*>::iterator>{_programs.begin(), _programs.end()} | filterByName);
}

std::vector<Program*> Susi::getPrograms() const {
	return _programs;
}

void Susi::addProgram(std::string name, int groupCount) {
	/*if (getPrograms(name).empty())*/_programs.push_back(new Program(name, groupCount));
	//else throw std::runtime_error("Program already added.");
}

void Susi::addCourseToProgram(std::string programName, int mandatory) {
	try {
		FilterAdaptor<Program*> filterByName{ [&programName](Program* prog) -> bool {
			return programName == "" || prog->getName() == programName;
		} };

		//Range<FilteredIterator<std::vector<Program*>::iterator>>
		std::vector<Program*>
			programs = ~(_programs | filterByName);


		if (programs.empty()) throw std::runtime_error("Program does not exist.");

		for (Program* prog : programs) {
			prog->createCourse(mandatory);
			//prog->printStudentsWithCoursesInfo();
		}
	}
	catch (const std::runtime_error e) {
		std::cout << e.what() << std::endl;
	}
}

void Susi::addSubjectToCourseOfProgram(std::string programName, int course, std::string subjetname, bool mandotary) {
	MapAdaptor<Program*, std::vector<Course*>> getCourses{
		[&mandotary, &course](Program* progPtr) ->std::vector<Course*> {
			return ~progPtr->getCourses(mandotary, course);
		}
	};

	for (Program* x : getPrograms(programName)) {

		for (Course* y : x->getCourses(mandotary, course)) {
			//std::cout << y->getName() << " ";
			y->addSubject(subjetname, mandotary);
			//y->print();
		}
		//std::cout << " \n";
	}
}

void Susi::addStudentToProgram(std::string programName, std::string name, int group) {
	for (Program* x : getPrograms(programName)) {
		x->signStudent(name, _fn++, group);
		//x->printStudents();
		//if(x->getStudent(2))x->getStudent(1)->printCourses();
	}
}

std::function<bool(Student*)> canContinueToNextCourse = [](Student* x) -> bool {
	return x->getNotpassedSubjects().size() <= 2;
}, canGraduate = [](Student* x) -> bool {
	return x->getNotpassedSubjects().size() == 0 && x->getCourse() >= 4;
}, id = [](Student* x) -> bool {
	return true;
};

void Susi::advanceStudents(int fn, std::string programName, int courseName, int group) {

	for (Program* x : getPrograms(programName)) {
		x->doStudents(&Student::advanceCourse, canContinueToNextCourse, courseName, group, fn);
	}
}

void Susi::interuptStudents(int fn, std::string programName, int courseName, int group) {
	for (Program* x : getPrograms(programName)) {
		x->doStudents(&Student::interuptStudent, id, courseName, group, fn);
	}
}
void Susi::graduateStudents(int fn, std::string programName, int courseName, int group) {
	for (Program* x : getPrograms(programName)) {
		x->doStudents(&Student::graduateStudent, canGraduate, courseName, group, fn);
	}
}

std::vector<Student*> Susi::getStudents(int fn, std::string name, int courseName, int group) {
	std::vector<Student*> r;

	FilterAdaptor<Program*> filterByName{ [&name](Program* prog) -> bool {
		return name == "" || prog->getName() == name;
	} };

	MapAdaptor<Program*, std::vector<Student*>>
		getStudents{
		[&courseName, &group, &fn](Program* progPtr) ->
		std::vector<Student*> {
			return progPtr->getStudents(courseName, group, fn);
		}
	};

	for (std::vector<Student*> x : _programs | filterByName | getStudents) {
		for (Student* y : x)
			r.push_back(y);
	}

	return r;
}

void Susi::addGradeToStudents(double grade, std::string subjectname, int fn, std::string programName, int courseName, int group) {
	MapAdaptor<Program*, std::vector<Student*>>
		getStudents{ [&courseName, &group, &fn](Program* programPtr) -> std::vector<Student*> {
		return programPtr->getStudents(courseName, group, fn);
	} };

	FilterAdaptor<std::vector<Student*>> clearEmpty{
		[](std::vector<Student*> range) -> bool {
			return !range.empty();
		}
	};

	FilterAdaptor<Subject*> filterSubjects{
		[&subjectname](Subject* subPtr) -> bool {
			return (subjectname == "" || subPtr->getName() == subjectname);// &&
				//static_cast<StudentSubject*>(subPtr)->getStatus() != 1;
		}
	};
	for (std::vector<Student*> studentRange : ~getPrograms(programName) | getStudents | clearEmpty) {
		for (Student* student : studentRange) {
			for (Subject* sub : student->getCurrentCourse() | filterSubjects) {
				static_cast<StudentSubject*>(sub)->setGrade(grade);
			}
		}
	}
}

void Susi::transferStudent(int fn, std::string newProgramName, size_t group) {
	try {
		std::vector<Student*> students = getStudents(fn);

		if (students.empty())
			throw std::runtime_error("This student does not exist!");

		Student* student = students[0];

		if (newProgramName != "") {
			//Range<FilteredIterator<std::vector<Program*>::iterator>>
			std::vector<Program*>
				programs = ~getPrograms(newProgramName);

			if (programs.empty())
				throw std::runtime_error("This new program does not exist!");

			Program* program = programs[programs.size() - 1];

			if (!program->studentCanJoin(student))
				throw std::runtime_error("This student cant't join this program!");

			std::cout << "Student program change from " << student->getProgram()->getName() <<
				" to " << newProgramName << std::endl;

			student->getProgram()->removeStudent(student);
			student->setProgram(program);
			program->addStudent(student);
		}

		if (student->getGroup() != group)
			student->setGroup(group);
	}
	catch (const std::runtime_error e) {
		std::cout << e.what() << std::endl;
	}
}

void Susi::accept(Visitor* v) {
	v->process_Susi(this);
}

void Susi::addProgram(Program* program) {
	_programs.push_back(program);
}

void Susi::print(int fn, std::string programName, int courseName, std::ostream& out) {
	if (fn != -1) {
		std::vector<Student*> students = getStudents(fn);

		if (!students.size())
			throw std::runtime_error("Student with this fn does not exist;");

		Student* student = students[0];
		student->printStudentInfo(out);
		student->printCourses(out);
	}
	else {
		FilterAdaptor<Course*> courseNameFilter{
			[&courseName](Course* coursePtr) -> bool {
				return courseName == -1 || coursePtr->getName() == courseName;
			}
		};


		for (Program* p : getPrograms(programName)) {
			printElement(p->getName(), 30, out);
			out << '\n';
			printElement("", 1, out);
			printElement("Mandatory", 30, out);
			out << '\n';
			for (Course* c : p->getCourses(true, courseName)) {
				c->print(out, 2);
			}
			printElement("", 1, out);
			printElement("Not mandatory", 30, out);
			out << '\n';
			for (Course* c : p->getCourses(false, courseName)) {
				c->print(out, 2);
			}
		}
		out << "\n\n";
		for (Program* p : getPrograms(programName)) {
			printElement(p->getName(), 30, out);
			out << '\n';
			for (Student* s : p->getStudents()) {
				s->printStudentInfo(out, 1);
				s->printCourses(out, 3);
			}
		}
	}
}

size_t Susi::getProgramsLen() {
	return _programs.size();
}
