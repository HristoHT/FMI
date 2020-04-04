#ifndef __GOOD_H
#define __GOOD_H

class Good
{
private:
    std::string _name, _producedBy, _measure, _storeLocation, _comment;
    Date _expirationDate, _entryDate;
    double _quantity;

public:
    void inputInfo();

};

#endif // __DATE_H

