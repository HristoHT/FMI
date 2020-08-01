#pragma once
#include "Susi.h"
class Subject;
class StudentSubject;
class Course;
class StudentCourse;
class Student;
class Program;
class Susi;
class Visitor
{
public:	
	virtual void process_Susi(Susi*) = 0;
	virtual void process_Student(Student*) = 0;
	virtual void process_Subject(Subject*) = 0;
	virtual void process_StudentSubject(StudentSubject*) = 0;
	virtual void process_StudentCourse(StudentCourse*) = 0;
	virtual void process_Course(Course*) = 0;
	virtual void process_Program(Program*) = 0;
};

