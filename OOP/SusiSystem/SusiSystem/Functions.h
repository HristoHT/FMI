#pragma once
#include<iostream>
#include<iomanip>
#include<ostream>
#include<math.h>
#include<vector>
#include<string>
#include "BlackMagic.h"
#include "Program.h"
#include "Course.h"
#include "Student.h"

class Student;
class StudentCourse;
class StudentSubject;
class Subject;
class Course;
class Program;

template<typename T>
void printElement(T t, int width, std::ostream& out = std::cout, bool left = true) {
	out << (left ? std::left : std::right) << std::setw(width) << std::setfill(' ') << t;
}

bool isAGreaterThanB(double a, double b);

bool isALessThanB(double a, double b);

bool isAEqualToB(double a, double b);

std::vector<std::string> split(std::string str, std::string splitter);

bool isInt(const std::string& number);

int toInt(const std::string& number);

double toDouble(const std::string& number);

Program* getProgramInput(std::istream& input);

Course* getCourseInput(std::istream& input);

Student* getStudentInput(std::istream& input, Program* prog);

Subject* getSubjectInput(std::istream& input, Course* course);

StudentCourse* getStudentCourseInput(std::istream& input, Student* student);

StudentSubject* getStudentSubjectInput(std::istream& input, Course* course);

std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ");
