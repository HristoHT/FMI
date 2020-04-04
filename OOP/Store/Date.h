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
    Date operator = (const Date &other);
    bool operator < (Date &other)const;
    bool operator > (Date& other)const;
    bool operator == (Date& other)const;
    bool operator != (Date& other)const;
    bool operator <= (Date& other)const;
    bool operator >= (Date& other)const;
};

#endif // __DATE_H
