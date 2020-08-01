#pragma once
#include "Program.h"
#include "ProxyIterator.h"
#include "BlackMagic.h"
class Student;
class Program;
class Visitor;

class Susi
{
	std::vector<Program*> _programs;
	void _copy(const Susi& other);
public:

	static size_t _fn;
	~Susi();
	Susi(size_t fnStart = 0);
	Susi(const Susi& other);
	Susi& operator=(const Susi& other);

	std::vector<Program*> getPrograms() const;
	std::vector<Student*> getStudents() const;
	size_t getProgramsLen();
	//Range<FilteredIterator<std::vector<Program*>::iterator>>
	std::vector<Program*> getPrograms(std::string name = "");

	std::vector<Student*> getStudents(int fn = -1, std::string name = "", int courseName = -1, int group = -1);

	void addProgram(Program* program);
	void addProgram(std::string name, int groupsCount = 4);
	void addCourseToProgram(std::string programName, int mandatory = 1);
	void addSubjectToCourseOfProgram(std::string programName, int course, std::string subjetname, bool mandotary = 1);
	void addStudentToProgram(std::string programName, std::string name, int group = 1);

	void advanceStudents(int fn = -1, std::string programName = "", int courseName = -1, int group = -1);
	void interuptStudents(int fn = -1, std::string programName = "", int courseName = -1, int group = -1);
	void graduateStudents(int fn = -1, std::string programName = "", int courseName = -1, int group = -1);
	void addGradeToStudents(double grade, std::string subjectname = "", int fn = -1, std::string programName = "", int courseName = -1, int group = -1);

	void transferStudent(int fn, std::string newProgramName, size_t group = 1);

	void print(int fn = -1, std::string programName = "", int courseName = -1, std::ostream& out = std::cout);

	void accept(Visitor* v);

};

