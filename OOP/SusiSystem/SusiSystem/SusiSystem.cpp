#include <iostream>
#include "Functions.h"
#include "Course.h"
#include "Student.h"
#include "Line.h"
#include "Susi.h"
#include "Visitor.h"	
#include "Serialize.h"

std::ostream& operator<<(std::ostream& out, Susi& s) {
	Serialize serializer(out);
	s.accept(&serializer);
	return out;
}

std::istream& operator>>(std::istream& input, Susi& susi) {
	std::string line;
	std::getline(input, line);
	trim(line);
	std::vector<std::string> attr = split(line, "|");

	if (attr.size() < 3 && attr.size() != 1)
		throw std::runtime_error("The file is corrupted!-");

	if (attr.size() != 1) {
		size_t programs = toInt(attr[0]), students = toInt(attr[1]);
		int fn = toInt(attr[2]);

		susi._fn = fn;

		for (size_t i = 0; i < programs; i++) {
			susi.addProgram(getProgramInput(input));
			//break;
		}
	}
	return input;
}

int main()
{
	//std::ifstream fileIn("output.txt", std::ios::in);

	{
		Susi mySusi(1000);

		//fileIn >> mySusi;


		mySusi.addProgram("KN", 5);
		mySusi.addProgram("SI", 4);
		mySusi.addProgram("TU", 4);

		for (Program* x : mySusi.getPrograms()) {
			std::cout << x->getName() << '\n';

			mySusi.addCourseToProgram("");
			mySusi.addSubjectToCourseOfProgram("", 0, "Matematika");
			mySusi.addSubjectToCourseOfProgram("KN", 0, "Matematika2");
			mySusi.addCourseToProgram("SI");
			mySusi.addCourseToProgram("");
			mySusi.addSubjectToCourseOfProgram("", 1, "Matematika2");
			mySusi.addCourseToProgram("", 0);
			mySusi.addSubjectToCourseOfProgram("", 0, "Izbiraem1", 0);
			mySusi.addSubjectToCourseOfProgram("", 0, "Izbiraem2", 0);
			mySusi.addStudentToProgram("KN", "Hristo", 2);
			mySusi.addStudentToProgram("KN", "Ivan", 2);
			mySusi.addStudentToProgram("SI", "Georgi", 1);
			mySusi.addStudentToProgram("KN", "Dimitar", 2);
			mySusi.addStudentToProgram("TU", "Petar", 2);
			mySusi.addStudentToProgram("SI", "Angel", 3);
			mySusi.transferStudent(1000, "SI", 3);
			mySusi.transferStudent(1001, "TU", 1);
			mySusi.transferStudent(1005, "TU", 1);
			mySusi.addGradeToStudents(4.5, "Matematika");
			mySusi.addGradeToStudents(6, "Matematika2", 1003);
			mySusi.addGradeToStudents(7, "Izbiraem1", 1003);
			//mySusi.print(-1, "KN");


			//std::cout << mySusi;

			//mySusi.print(1000);
			//mySusi.print(-1, "KN");
			//mySusi.print(-1, "", 1);

			for (Line newCommand : std::cin | Line()) {
				try {
					newCommand.execute(&mySusi);
				}
				catch (const std::runtime_error& error) {
					std::cout << error.what() << "\n";
				}
			}

			//std::ofstream out("test_output.txt", std::ios::out);
			//out << mySusi;

		}

	}
