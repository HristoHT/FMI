#ifndef __DATE_CPP
#define __DATE_CPP
#include<ctime>
#include<iostream>
#include<string>
#include "Date.h"
#include<stack>


std::string Date::getDate()
{
    return _year + "-" + _month + "-" + _day;
}

std::string Date::getTime()
{
    return _h + ":" + _m + ":" + _s;
}

bool Date::operator < (Date &other)const
{
    if(_year > other._year)
        return false;
    else if (_month > other._month)
        return false;
    else if (_day > other._day)
        return false;
    else if (_h > other._h)
        return false;
    else if (_m > other._m)
        return false;
    else if (_s > other._s)
        return false;
    else
        return true;
}

bool Date::operator > (Date& other)const
{
    return !(operator < (other));
}

bool Date::operator == (Date& other)const
{
    if(_year != other._year)
        return false;
    else if (_month != other._month)
        return false;
    else if (_day != other._day)
        return false;
    else if (_h != other._h)
        return false;
    else if (_m != other._m)
        return false;
    else if (_s != other._s)
        return false;
    else
        return true;
}

bool Date::operator != (Date& other)const
{
    return !(operator == (other));
}

bool Date::operator <= (Date& other)const
{
    return (operator == (other) || operator < (other));
}

bool Date::operator >= (Date& other)const
{
    return (operator == (other) || operator > (other));
}

Date::Date(std::string year = "", std::string month = "", std::string day = "",
           std::string h  = "", std::string m = "", std::string s = "")
{
    setValue(_year, year, 4, ltm->tm_year + 1900);
    setValue(_month, month, 2, ltm->tm_mon + 1);
    setValue(_day, day, 2, ltm->tm_yday + 1);

    setValue(_h, h, 2, ltm->tm_hour + 1);
    setValue(_m, m, 2, ltm->tm_min + 1);
    setValue(_s, s, 2, ltm->tm_sec + 1);
}

int main()
{
    Date a, b("1", "2", "3", "", "-2", "");
    std::cout << a.getDate() << " " << a.getTime() << std::endl;
    std::cout << b.getDate() << " " << b.getTime() << std::endl;
    std::cout << (a < b) << std::endl;
    std::cout << (a > b) << std::endl;
    std::cout << (a == b) << std::endl;
    std::cout << (a != b) << std::endl;
    std::cout << (a >= b) << std::endl;
    std::cout << (a <= b) << std::endl;
}


std::string toString(int number)
{
    std::string result;

    if(number < 0)
    {
        result += "-";
        number *= -1;
    }

    int currentDigit;
    while(number != 0)
    {
        currentDigit = number%10;
        number = number/10;
        result += (currentDigit + '0');
    }
    reverseString(result);
    return result;
}

std::string padStart(std::string member, int counter, std::string str)
{
    std::string newString = "";
    size_t i = member.length();

    while( i < counter)
    {
        newString += "0";
        i++;
    }
    newString += member;

    return newString;
}

void reverseString(std::string &str)
{
    for(size_t i = 0; i < str.length() / 2; i++)
    {
        std::swap(str[i], str[str.length() - i - 1]);
    }
}

int toInt(std::string str)
{
    int number = 0, negative = 1, i = 0;

    if(str[0] == '-')
    {
        negative = -1;
        i = 1;
    }

    for(i; i < str.length(); i++)
    {
        number *= 10;
        number += (int)(str[i] - '0');
    }

    return number * negative;
}


void setValue(std::string &inClassVar, std::string value, int precision, int defaultValue)
{
    if(value == "")
        inClassVar = padStart(toString(defaultValue), precision, "0");
    else
        inClassVar = padStart(value, precision, "0");
}

#endif
