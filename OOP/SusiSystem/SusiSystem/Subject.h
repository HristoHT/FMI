#pragma once
#include<string>
#include<iostream>
#include"Functions.h"
#include"Course.h"
#include"Visitor.h"
class Course;
class Visitor;
class Subject
{
protected:
	std::string _name;
	Course* _course;
	bool _mandatory;

	virtual void _copy(const Subject& other);
public:
	Subject(std::string name = "Unknown subject", bool mandatory = true, Course* course = nullptr);
	~Subject();
	Subject(const Subject& other);
	Subject& operator=(const Subject& other);

	void setName(std::string name);
	std::string getName() const;

	void setCourse(Course* course);
	Course* getCourse() const;

	void setMandatory(bool mandatory);
	bool getMandatory() const;

	virtual void print(std::ostream& out = std::cout, size_t offset = 0);
	virtual void accept(Visitor*);
};

class StudentSubject :public Subject {
	int _status;
	double _grade;

	virtual void _copy(const Subject& other);
	void _copy(const StudentSubject& other);
public:
	StudentSubject(std::string name = "Unknown subject", bool mandatory = true,
		Course* course = nullptr, int status = 0, double grade = -1);
	StudentSubject(const StudentSubject& other);
	StudentSubject(const Subject& other);
	StudentSubject& operator=(const Subject& other);
	StudentSubject& operator=(const StudentSubject& other);

	void setStatus(int status);
	int getStatus() const;

	void setGrade(double grade);
	double getGrade() const;

	void print(std::ostream& out = std::cout, size_t offset = 0);
	void accept(Visitor*);
};


