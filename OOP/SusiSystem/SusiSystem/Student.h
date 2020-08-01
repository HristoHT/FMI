#pragma once
#include "Program.h"
#include "BlackMagic.h"
class Course;
class Program;
class Subject;
class Visitor;
class Student
{
	std::vector<Course*> _courses;
	Program* _program;
	std::string _name;
	int _status, _group, _fn;
	double _averageGrade;

	void _copy(const Student& other);
	void setCourse(int course);
public:
	int _course;
	Student(std::string name = "Unknown student", int group = 1, int fn = 0, Program* program = nullptr);
	~Student();
	Student(const Student& other);
	Student& operator=(const Student& other);

	Course& operator[] (size_t i);
	Course operator[] (size_t i) const;
	Course& getCurrentCourse();

	void setCourses(std::vector<Course*> courses);
	std::vector<Course*> getCourses() const;
	std::vector<Subject*> getNotpassedSubjects();

	void addCourse(Course* newcourse);
	void addCourse2(Course* newcourse);

	void setProgram(Program* program);
	Program* getProgram() const;

	void setStatus(int status);
	int getStatus() const;

	void setGroup(int status);
	int getGroup() const;

	void setFn(int status);
	int getFn() const;
	
	void advanceCourse();
	int getCourse() const;

	void setName(std::string name);
	std::string getName() const;

	void interuptStudent();
	void graduateStudent();
	void resumeStudent();

	void calculateAverageGrade();
	double getAverageGrade()const;

	void printStudentInfo(std::ostream& out = std::cout, size_t offset = 0);
	void printCourses(std::ostream& out = std::cout, size_t offset = 0);


	std::vector<Course*>::iterator begin();
	std::vector<Course*>::iterator end();

	void accept(Visitor*);
};

