#pragma once
#include "Visitor.h"
#include "BlackMagic.h"
class Serialize :
	public Visitor
{
	std::ostream&_out;
public:
	Serialize(std::ostream& out);

	void process_Susi(Susi*);
	void process_Student(Student*);
	void process_Subject(Subject*);
	void process_StudentSubject(StudentSubject*);
	void process_StudentCourse(StudentCourse*);
	void process_Course(Course*);
	void process_Program(Program*);

};

