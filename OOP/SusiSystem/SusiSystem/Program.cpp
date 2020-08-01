#include "Program.h"

Program::Program(std::string name, int groupCount) {
	setName(name);
	setGroupsCount(groupCount);
}

Program::~Program() {
	for (Course* x : _coursesMandatory)
		delete x;

	for (Course* x : _coursesNotMandatory)
		delete x;

	for (Student* x : _students)
		delete x;
}

void Program::_copy(const Program& other) {
	if (this != &other) {
		for (Course* c : other.getMandatoryCourses())
			_coursesMandatory.push_back(new Course(*c));
		for (Course* c : other.getNotMandatoryCourses())
			_coursesNotMandatory.push_back(new Course(*c));
		_students = other.getStudents();
		setName(other.getName());
		setGroupsCount(other.getGroupsCount());
	}
}

void Program::removeStudent(Student* student) {
	std::vector<Student*>::iterator it = std::remove(_students.begin(), _students.end(), student);
	_students.erase(it);
}

Program::Program(const Program& other) {
	_copy(other);
}

Program& Program::operator=(const Program& other) {
	_copy(other);
	return *this;
}

void Program::addCourse(bool mandatory) {
	if (mandatory) {
		_coursesMandatory.push_back(new Course(_coursesMandatory.size()));
	}
	else {
		_coursesNotMandatory.push_back(new Course(_coursesNotMandatory.size()));
	}
}

void Program::addCourseByPointer(Course* course, bool mandatory) {
	if (mandatory) {
		_coursesMandatory.push_back(course);
	}
	else {
		_coursesNotMandatory.push_back(course);
	}
}

void Program::createCourse(bool mandatory) {
	/*std::vector<Course*>
		courses = find_all_if((mandatory ? _coursesMandatory : _coursesNotMandatory), [&name](Course* coursePtr) -> bool {
		return coursePtr->getName() == name;
			});*/

			/*if (!courses.empty())
				throw std::runtime_error("Course with this name already exists!");*/
	if (mandatory) {
		_coursesMandatory.push_back(new Course(_coursesMandatory.size()));
	}
	else {
		_coursesNotMandatory.push_back(new Course(_coursesNotMandatory.size()));
	}
}

std::vector<Student*> Program::getStudents() const {
	return _students;
}

void Program::addSubjectToCourse(std::string name, size_t courseName, bool mandatory) {
	if (mandatory) {
		if (courseName >= _coursesMandatory.size())
			throw std::runtime_error(std::string("Index is too large, for mandotory course!"));

		_coursesMandatory[courseName]->addSubject(name, mandatory);
	}
	else {
		if (courseName >= _coursesNotMandatory.size())
			throw std::runtime_error(std::string("Index is too large, for not mandotory course!"));

		_coursesNotMandatory[courseName]->addSubject(name, mandatory);
	}
}

Student* Program::signStudent(std::string name, size_t fn, int group) {
	Student* newstudent = new Student(name, group, fn, this);
	_students.push_back(newstudent);

	return newstudent;
}

void Program::setName(std::string name) {
	_name = name;
}

std::string Program::getName() const {
	return _name;
}

void Program::setGroupsCount(int groupsCount) {
	_groupsCount = groupsCount;
}

int Program::getGroupsCount() const {
	return _groupsCount;
}

std::vector<Course*> Program::getMandatoryCourses() const {
	return _coursesMandatory;
}

std::vector<Course*> Program::getNotMandatoryCourses() const {
	return _coursesNotMandatory;
}

Student& Program::getStudentByFn(int fn) {
	for (Student* student : _students) {
		if (student->getFn() == fn)
			return *student;
	}

	throw std::runtime_error(std::string("There is no student with this FN."));
}

void Program::loadMandatorySubjectsToStudent(Student* student, int course) {

	if (course < _coursesMandatory.size()) {
		student->addCourse(_coursesMandatory[course]);
	}
	else
		throw std::runtime_error(std::string("There is no course with this index."));
}

void Program::printStudents(std::ostream& out, int offset) {
	for (Student* student : _students) {
		student->printStudentInfo(out);
	}
}

void Program::printStudentsWithCoursesInfo(std::ostream& out, int offset) {
	for (Student* student : _students) {
		student->printStudentInfo(out, 0);
		student->printCourses(out, 1);
		out << "\n";
	}
}

void Program::printStudent(int fn, int course, std::ostream& out, int offset) {
	Student student = getStudentByFn(fn);

	student.printStudentInfo(out, offset);
	if (course == -1)
		student.printCourses(out, offset + 2);
	else
		student[course - 1].print(out);
}

Student* Program::getStudent(int fn) {
	Student* found = find_if(_students, (std::function<bool(Student*)>)[&fn](Student* x) -> bool {
		return x->getFn() == fn;
		});

	return found;
}

std::vector<Student*>
Program::getStudents(int courseName, int group, int fn) {
	FilterAdaptor<Student*>filter{ [&courseName, &group, &fn](Student* student) -> bool {
		return (courseName == -1 || (*student).getCourse() == courseName) &&
			(group == -1 || (*student).getGroup() == group) &&
			(fn == -1 || (*student).getFn() == fn);
	} };

	return ~(_students | filter);
}

void Program::doStudents(void(Student::* action)(), std::function<bool(Student*)> additionalFilter, int courseName, int group, int fn) {
	try {
		FilterAdaptor<Student*> fullFillAdditionalFilter{ additionalFilter };
		std::vector<std::string> studentStatuses2 = { "Studing", "Interrupt", "Graduated" };

		std::cout << "Operation info for program :" << getName() << '\n';
		Table newTable({ "Faculty N.", "Name", "Status", "Course" });


		for (Student* student : getStudents(courseName, group, fn)) {
			try {
				((*student).*action)();
				newTable.push({
					std::to_string(student->getFn()),
					student->getName(),
					studentStatuses2[student->getStatus()],
					std::to_string(student->getCourse()) });
			}
			catch (const std::runtime_error e) {
				//std::cout << e.what() << "\n";
			}
		}
		newTable.print();
	}
	catch (const std::runtime_error e) {
		std::cout << e.what() << "\n";
	}
}


void Program::printProgramStudents(std::ostream& out, int offset) {
	printElement("", offset, out);
	printElement("Student name", 30, out);
	printElement("FN", 10, out);
	printElement("Course", 3, out);
	out << "\n";
	for (Student* student : _students) {
		printElement("", offset, out);
		printElement(student->getName(), 30, out);
		printElement(student->getFn(), 10, out);
		printElement(student->getCourse(), 3, out);
		out << "\n";
	}
}


//Range<FilteredIterator<std::vector<Course*>::iterator>>
std::vector<Course*>
Program::getCourses(bool mandatory, int courseName) {
	FilterAdaptor<Course*> filterByName{ [&courseName](Course* coursePtr) -> bool {
		return courseName == -1 || coursePtr->getName() == courseName;
	} };

	return (mandatory ? ~(_coursesMandatory | filterByName) : ~(_coursesNotMandatory | filterByName));
}

bool Program::studentCanJoin(Student* student) {
	size_t studentCourse = student->getCourse();

	FilterAdaptor<Course*> filterCourses{
		[&studentCourse](Course* ptr) -> bool {
			return ptr->getName() < studentCourse;
}
	};

	std::vector<std::string> subjectsWhichMustHavePassed;
	size_t count = 0;

	if (studentCourse > 0) {
		for (Course* coursesToCheck : _coursesMandatory | filterCourses) {
			for (Subject* subject : *coursesToCheck) {
				subjectsWhichMustHavePassed.push_back(subject->getName());
			}
		}

		for (Course* studentCourses : *student) {
			for (std::string subName : subjectsWhichMustHavePassed) {
				bool flag = false;
				for (Subject* studentSubject : *studentCourses) {
					if (subName == studentSubject->getName())
						flag = true;
				}
				if (!flag) return false;
			}
		}
	}

	return true;
}

void Program::addStudent(Student* student) {
	_students.push_back(student);
}

void Program::accept(Visitor* v) {
	v->process_Program(this);
}

void Program::printCourses(std::ostream& out, int offset) {
	printElement("", offset, out);
	printElement(getName(), 30, out);
	out << '\n';
	for (Course* c : _coursesMandatory) {
		c->print(out, offset + 1);
	}
}

