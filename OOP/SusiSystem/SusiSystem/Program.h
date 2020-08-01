#pragma once
#include "Student.h"
#include "Course.h"
#include "BlackMagic.h"
#include "ProxyIterator.h"
#include "Table.h"
class Student;
class Visitor;
class Course;
class Program
{
	std::vector<Course*> _coursesMandatory, _coursesNotMandatory;
	std::vector<Student*> _students;
	std::string _name;
	int _groupsCount;

	void _copy(const Program& other);

	Student& getStudentByFn(int fn);

public:
	Program(std::string name = "Unknown program", int groupsCount = 4);
	~Program();
	Program(const Program& other);
	Program& operator=(const Program& other);

	void addCourseByPointer(Course* coourse, bool mandatory = true);
	void addCourse(bool mandatory = true);
	void createCourse(bool mandatory = true);
	void removeStudent(Student* s);
	void addSubjectToCourse(std::string name = "Unknown subject", size_t courseName = 0, bool mandatory = true);

	void addStudent(Student* student);
	Student* signStudent(std::string name, size_t fn, int group = 1);
	Student* getStudent(int fn);

	void setName(std::string name);
	std::string getName() const;

	void setGroupsCount(int groupsCount);
	int getGroupsCount() const;

	std::vector<Course*> getMandatoryCourses() const;
	std::vector<Course*> getNotMandatoryCourses() const;

	std::vector<Student*>
		getStudents(int courseName = -1, int group = -1, int fn = -1);

	std::vector<Student*> getStudents() const;

	void doStudents(void(Student::* action)(), std::function<bool(Student*)> additionalFilter, int courseName = -1, int group = -1, int fn = -1);

	void loadMandatorySubjectsToStudent(Student* student, int course);

	void printStudent(int fn, int course = -1, std::ostream& out = std::cout, int offset = 0);
	void printStudents(std::ostream& out = std::cout, int offset = 0);
	void printStudentsWithCoursesInfo(std::ostream& out = std::cout, int offset = 0);
	void printProgramStudents(std::ostream& out = std::cout, int offset = 0);
	void printCourses(std::ostream& out = std::cout, int offset = 0);

	//Range<FilteredIterator<std::vector<Course*>::iterator>>
	std::vector<Course*>
		getCourses(bool mandatory = 1, int courseName = -1);

	bool studentCanJoin(Student* student);

	void accept(Visitor*);
};

