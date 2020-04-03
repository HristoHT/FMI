#ifndef __DATE_H
#define __DATE_H

class Date
{
private:
    std::string _day, _month, _year, _h, _m, _s;
    time_t now = time(0);
    tm *ltm = localtime(&now);

public:
    Date(std::string year /*= ""*/, std::string month /*= ""*/, std::string day /*= ""*/, std::string h /*= ""*/, std::string m /*= ""*/, std::string s /*= ""*/);
    std::string getDate();
    std::string getTime();
    bool operator < (Date &other)const;
    bool operator > (Date& other)const;
    bool operator == (Date& other)const;
    bool operator != (Date& other)const;
    bool operator <= (Date& other)const;
    bool operator >= (Date& other)const;
};

void setValue(std::string &inClassVar, std::string value, int precision, int defaultValue);
void reverseString(std::string &str);
int toInt(std::string str);
std::string toString(int number);
std::string padStart(std::string member, int count, std::string str);

#endif // __DATE_H
