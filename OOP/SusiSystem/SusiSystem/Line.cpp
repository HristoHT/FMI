#include "Line.h"
#include <stdlib.h>

Line::Line() : _line("") {}
std::string workFile = "";
std::ifstream in;
std::ofstream out;
std::string& Line::string() {
	return _line;
}

std::string Line::string() const {
	return _line;
}

std::istream& operator>>(std::istream& input, Line& l) {
	std::getline(input, l.string());
	return input;
}

std::ostream& operator<<(std::ostream& out, const Line& l) {
	out << l.string();
	return out;
}

void checkPositive(int x) {
	if (x < 0)
		throw std::runtime_error("The number should be grater than 0!");
}

void Line::execute(Susi* susi) {
	std::vector<std::string> attributes = split(trim(_line), " ");
	if (attributes.size() > 0) {
		std::string command = attributes[0];
		std::remove(attributes.begin(), attributes.end(), command);

		int groupsCount = 4,
			fn = -1,
			group = -1,
			courseName = -1,
			mandatory = 1;

		std::string programName = "",
			subjectName = "",
			studentName = "",
			file = "";

		double grade = -1;

		for (std::string attr : attributes) {
			std::vector<std::string> attrSplited = split(attr, ":");

			if (attrSplited.size() > 1 && attrSplited[0] != "") {
				if (attrSplited[0] == "groupsCount")
					groupsCount = toInt(attrSplited[1]);
				else if (attrSplited[0] == "fn")
					fn = toInt(attrSplited[1]);
				else if (attrSplited[0] == "group")
					group = toInt(attrSplited[1]);
				else if (attrSplited[0] == "courseName")
					courseName = toInt(attrSplited[1]);
				else if (attrSplited[0] == "mandatory")
					mandatory = toInt(attrSplited[1]);
				else if (attrSplited[0] == "programName")
					programName = attrSplited[1];
				else if (attrSplited[0] == "subjectName")
					subjectName = attrSplited[1];
				else if (attrSplited[0] == "studentName")
					studentName = attrSplited[1];
				else if (attrSplited[0] == "grade")
					grade = toDouble(attrSplited[1]);
				else if (attrSplited[0] == "file")
					file = attrSplited[1];
			}
		}
		if(courseName != -1)courseName--;

		if (grade != -1 && (grade < 2.00 || grade > 6.00)) {
			throw std::runtime_error("Grade should be between 2.00 and 6.00");
		}

		if (command == "addProgram") {
			if (programName == "")
				throw std::runtime_error("For this command programName is mandatory field!");
			checkPositive(groupsCount);
			susi->addProgram(programName, groupsCount);
		}
		else if (command == "addCourse") {
			if (programName == "")
				throw std::runtime_error("For this command programName is mandatory field!");
			checkPositive(mandatory);

			susi->addCourseToProgram(programName, mandatory);
		}
		else if (command == "addSubject") {
			if (programName == "")
				throw std::runtime_error("For this command programName is mandatory field!");
			if (courseName == -1)
				throw std::runtime_error("For this command courseName is mandatory field!");
			if (subjectName == "")
				throw std::runtime_error("For this command subjectName is mandatory field!");
			checkPositive(courseName);
			checkPositive(mandatory);

			susi->addSubjectToCourseOfProgram(programName, courseName, subjectName, mandatory);
		}
		else if (command == "addStudent") {
			if (programName == "")
				throw std::runtime_error("For this command programName is mandatory field!");
			if (studentName == "")
				throw std::runtime_error("For this command studentName is mandatory field!");
			if (group == -1)group = 1;
			checkPositive(group);

			susi->addStudentToProgram(programName, studentName, group);
		}
		else if (command == "advanceStudents") {
			susi->advanceStudents(fn, programName, courseName, group);
		}
		else if (command == "interuptStudents") {
			susi->interuptStudents(fn, programName, courseName, group);
		}
		else if (command == "graduateStudents") {
			susi->graduateStudents(fn, programName, courseName, group);
		}
		else if (command == "addGrade") {
			if (grade == -1)
				throw std::runtime_error("For this command grade is mandatory field!");

			checkPositive(grade + 1);

			susi->addGradeToStudents(grade, subjectName, fn, programName, courseName, group);
		}
		else if (command == "transferStudent") {
			if (fn == -1)
				throw std::runtime_error("For this command fn is mandatory field!");
			if (programName == "")
				throw std::runtime_error("For this command programName is mandatory field!");

			if (group == -1)group = 1;
			checkPositive(group + 1);

			susi->transferStudent(fn, programName, group);
		}
		else if (command == "open") {
			if (file == "")
				throw std::runtime_error("For this file fn is mandatory field!");
			workFile = file;
		}
		else if (command == "load") {
			if (workFile == "")
				throw std::runtime_error("Plase open a file!");

			if (in) {
				in.close();
			}
			in.open(workFile, std::ios::in);

			if (in.eof())
				throw std::runtime_error("Could not load the file!");

			Susi newSusi;
			/*for (Susi s : in | *susi) {
				*susi = s;
				std::cout << "file loaded\n";
				//for (Program* p : s.getPrograms()) {
					//susi->addProgram(new Program(*p));
				//}
			}*/

			in >> *susi;
		}
		else if (command == "save") {
			if (workFile == "")
				throw std::runtime_error("Plase open a file!");

			if (out)
				out.close();

			out.open(workFile, std::ios::out);

			if (out.eof())
				throw std::runtime_error("Could not load the file!");

			out << (*susi);
		}
		else if (command == "saveAs") {
			if (file == "")
				throw std::runtime_error("For this file file is mandatory field!");

			if (out) {
				out.close();
			}
			out.open(file, std::ios::out);
			if (out.eof())
				throw std::runtime_error("Could not load the file!");

			out << (*susi);
		}
		else if (command == "close") {
			if (in)in.close();
			if (out)out.close();
			workFile = "";
		}
		else if (command == "exit") {
			exit(3);
		}
		else if (command == "print") {
			susi->print(fn, programName, courseName);
		}
		else if (command == "help") {
			Table helpTable({ "Command", "Mandatory params", "Not mandatory params" });
			helpTable.push({ "addProgram", "programName", "groupsCount(4)" });
			helpTable.push({ "addCourse", "programName", "mandatory(true)" });
			helpTable.push({ "addSubject", "programName, courseName, subjectName", "mandatory(true)" });
			helpTable.push({ "addStudent", "programName, studentName", "group(1)" });
			helpTable.push({ "advanceStudents", "", "fn, programName, courseName, group" });
			helpTable.push({ "interuptStudents", "", "fn, programName, courseName, group" });
			helpTable.push({ "graduateStudents", "", "fn, programName, courseName, group" });
			helpTable.push({ "addGrade", "grade", "subjectName, fn, programName, courseName, group" });
			helpTable.push({ "transferStudent", "programName, fn", "group(1)" });
			helpTable.push({ "open", "file" });
			helpTable.push({ "load" });
			helpTable.push({ "save" });
			helpTable.push({ "saveAs", "file" });
			helpTable.push({ "close" });
			helpTable.push({ "exit" });
			helpTable.push({ "print", "", "fn, programName, courseName" });

			helpTable.print();
		}
		else std::cout << "Unknown command!" << "\n";
	}

}

