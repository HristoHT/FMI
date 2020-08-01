
#include "Functions.h"
const double EPSILON = 0.0001;

bool isAGreaterThanB(double a, double b) {
	return (a - b) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * EPSILON);
}

bool isALessThanB(double a, double b) {
	return (b - a) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * EPSILON);
}

bool isAEqualToB(double a, double b) {
	return fabs(a - b) < EPSILON;
}

std::string& ltrim(std::string& str, const std::string& chars)
{
	str.erase(0, str.find_first_not_of(chars));
	return str;
}

std::string& rtrim(std::string& str, const std::string& chars)
{
	str.erase(str.find_last_not_of(chars) + 1);
	return str;
}

std::string& trim(std::string& str, const std::string& chars)
{
	return ltrim(rtrim(str, chars), chars);
}

std::vector<std::string> split(std::string str, std::string splitter) {
	std::string attr;
	std::vector<std::string> r;
	size_t pos = 0;

	while ((pos = str.find(splitter)) != std::string::npos)
	{
		attr = str.substr(0, pos);
		str.erase(0, pos + splitter.length());
		r.push_back(attr);
	}
	r.push_back(str);

	return r;
}

bool isInt(const std::string& number)
{
	return !number.empty() && !find_if(number, [](unsigned char c) -> bool { return !std::isdigit(c); });
}

int toInt(const std::string& number) {
	if (isInt(number)) {
		return std::stoi(number);
	}

	throw std::runtime_error("Incorect input!Try again!!! !!! !");
}

double toDouble(const std::string& number) {
	return std::stod(number);
}

Program* getProgramInput(std::istream& input) {
	std::string line;
	std::getline(input, line);
	trim(line);
	std::vector<std::string> attr = split(line, "|");

	if (attr.size() < 4)
		throw std::runtime_error("The file is corrupted!!!!!!");

	std::string name = attr[0];
	int mandatoryCourses = toInt(attr[1]),
		notMandatoryCourses = toInt(attr[2]),
		students = toInt(attr[3]);

	Program* program = new Program(name);

	for (int i = 0; i < mandatoryCourses; i++) {
		program->addCourseByPointer(getCourseInput(input), true);
	}

	for (int i = 0; i < notMandatoryCourses; i++) {
		program->addCourseByPointer(getCourseInput(input), false);
	}

	for (int i = 0; i < students; i++) {
		program->addStudent(getStudentInput(input, program));
	}

	return program;
}

Course* getCourseInput(std::istream& input) {
	std::string line;
	std::getline(input, line);
	trim(line);
	std::vector<std::string> attr = split(line, "|");

	if (attr.size() < 2)
		throw std::runtime_error("The file is corrupted!!!!!");

	int subjects = toInt(attr[1]), name = toInt(attr[0]);

	Course* course = new Course(name);

	for (int i = 0; i < subjects; i++) {
		course->addSubject(getSubjectInput(input, course));
	}

	return course;
}

Student* getStudentInput(std::istream& input, Program* prog) {
	std::string line;
	std::getline(input, line);
	trim(line);
	std::vector<std::string> attr = split(line, "|");

	if (attr.size() < 6)
		throw std::runtime_error("The file is corrupted!!!!");

	std::string name = attr[0];
	int status = toInt(attr[1]),
		fn = toInt(attr[2]),
		group = toInt(attr[3]),
		course = toInt(attr[4]),
		courses = toInt(attr[5]);

	Student* student = new Student(name, group, fn, prog);
	student->setStatus(status);
	student->_course = course;
	for (int i = 0; i < courses; i++) {
		student->addCourse2(getStudentCourseInput(input, student));
	}

	return student;
}

Subject* getSubjectInput(std::istream& input, Course* course) {
	std::string line;
	std::getline(input, line);
	trim(line);
	std::vector<std::string> attr = split(line, "|");

	if (attr.size() < 2)
		throw std::runtime_error("The file is corrupted!!!");

	std::string name = attr[0];
	int mandatory = toInt(attr[1]);

	Subject* subject = new Subject(name, mandatory, course);

	return subject;
}

StudentCourse* getStudentCourseInput(std::istream& input, Student* student) {
	std::string line;
	std::getline(input, line);
	trim(line);
	std::vector<std::string> attr = split(line, "|");

	if (attr.size() < 2)
		throw std::runtime_error("The file is corrupted!!");

	int subjects = toInt(attr[1]), name = toInt(attr[0])/*, status = toInt(attr[2])*/;

	StudentCourse* course = new StudentCourse(name, student);
	//course->setStatus(status);

	for (int i = 0; i < subjects; i++) {
		course->addSubject(getStudentSubjectInput(input, course));
	}

	return course;
}

StudentSubject* getStudentSubjectInput(std::istream& input, Course* course) {
	std::string line;
	std::getline(input, line);
	trim(line);
	std::vector<std::string> attr = split(line, "|");
	if (attr.size() < 4)
		throw std::runtime_error("The file is corrupted!");

	std::string name = attr[0];
	int mandatory = toInt(attr[1]),
		status = toInt(attr[3]);
	double grade = toDouble(attr[2]);

	StudentSubject* subject = new StudentSubject(name, mandatory, course, status, grade);

	return subject;
}