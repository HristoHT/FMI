#pragma once
#include "Subject.h"
#include <vector>
#include <exception>
#include <stdexcept>
class Subject;
class Student;
class Visitor;
class Course {
protected:
	std::vector<Subject*> _subjects;
	size_t _name;
	
	virtual void _copy(const Course& other);
public:
	using value_type = Subject*;

	Course(size_t name = 1);
	~Course();
	Course(const Course& other);
	Course& operator=(const Course& other);

	Subject& operator[](size_t i);
	Subject operator[](size_t i) const;

	void setName(size_t name);
	size_t getName() const;

	void addSubject(Subject* newsubjet);
	void setSubjects(std::vector<Subject*> subjects);
	std::vector<Subject*> getSubjects() const;
	
	void removeSubject(Subject* removesubject);
	virtual void addSubject(std::string name = "Unknown subject", bool mandatory = true);

	Subject* findSubjectByName(std::string subjectname);

	virtual void print(std::ostream& out = std::cout, size_t offset = 0);
	virtual void accept(Visitor*);
	class iterator {
	public:
		iterator(size_t startPos, std::vector<Subject*>& v);
		bool operator != (const iterator& other);
		bool operator == (const iterator& other);
		iterator& operator ++();
		Subject* operator*();

		using value_type = Subject*;
	private:
		size_t index;
		std::vector<Subject*>& vector;
	};

	iterator begin();
	iterator end();
};

class StudentCourse : public Course {
	Student* _student;
	int _status;

	void _copy(const StudentCourse& other);
	void _copy(const Course& other);
public:
	StudentCourse(size_t name = 1, Student* student = nullptr);
	~StudentCourse();
	StudentCourse(const Course& other);
	StudentCourse(const StudentCourse& other);
	StudentCourse& operator=(const StudentCourse& other);
	StudentCourse& operator=(const Course& other);

	void setStudent(Student* student);
	Student* getStudent() const;

	double averageGrade();

	void setStatus(int status);
	int getStatus() const;

	void print(std::ostream& out = std::cout, size_t offset = 0);

	void accept(Visitor*);
};
