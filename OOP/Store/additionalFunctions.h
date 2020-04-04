#ifndef __ADDITIONALFUNCTIONS_H
#define __ADDITIONALFUNCTIONS_H

int toInt(std::string str);

double readNumberFromConsole(std::string message);

void setValue(std::string &inClassVar, std::string value, int precision, int defaultValue);
void reverseString(std::string &str);
void checkForPrecision(int value, int prec);

std::string toString(int number);
std::string padStart(std::string member, int count, std::string str);
std::string readStringFromConsole(std::string message);

bool double_equals(double a, double b);
bool double_less(double a, double b);

#endif // __ADDITIONALFUNCTIONS_H
