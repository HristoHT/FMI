#ifndef __DATE_CPP
#define __DATE_CPP

#include "used-libs.cpp"
#include "additionalFunctions.cpp"

#include "Date.h"

std::string Date::getDate()
{
    return _year + "-" + _month + "-" + _day;
}

std::string Date::getTime()
{
    return _h + ":" + _m + ":" + _s;
}

Date Date::operator = (const Date &other)
{

    Date newDate(other._year, other._month, other._day, other._h,  other._m, other._s);
    return newDate;
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
    setValue(_day, day, 2, ltm->tm_mday + 1);

    setValue(_h, h, 2, ltm->tm_hour + 1);
    setValue(_m, m, 2, ltm->tm_min + 1);
    setValue(_s, s, 2, ltm->tm_sec + 1);
}

/*Date readDateFromConsole(std::string message)
{
    Date input;

    std::cout << message;
    std::cin >> input;

    return input;
}

/*std::istream operator >> (const Date &date)
{
    date.setValue(date._s, readStringFromConsole("Year:"), 4, date.ltm->tm_year + 1);
    date.setValue(date._month, readStringFromConsole("Month:"), 2, date.ltm->tm_mon + 1);
    date.setValue(date._day, readStringFromConsole("Day:"), 2, date.ltm->tm_mday + 1);
}

/*int main()
{
    Date a, b("1", "2", "-3", "", "", "");
    std::cout << a.getDate() << " " << a.getTime() << std::endl;
    std::cout << b.getDate() << " " << b.getTime() << std::endl;
    std::cout << (a < b) << std::endl;
    std::cout << (a > b) << std::endl;
    std::cout << (a == b) << std::endl;
    std::cout << (a != b) << std::endl;
    std::cout << (a >= b) << std::endl;
    std::cout << (a <= b) << std::endl;
}*/



#endif
