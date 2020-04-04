#include "used-libs.cpp"
#include "additionalFunctions.cpp"

#include "Date.cpp"
#include "Good.h"

void Good::inputInfo()
{
    std::cout << "All string must be with length in the range of [" << STRING_LOWER_BOUND << ", " << STRING_UPPER_BOUND << "]!\n";
    std::cout << "All numbers must be in the range of [" << NUMBER_LOWER_BOUND << ", " << NUMBER_UPPER_BOUND << "]!\n";
    _name = readStringFromConsole("Input name:");
    //_expirationDate = readDateFromConsole("Input expiration date:");
    _quantity = readNumberFromConsole("Input quantity:");
    _producedBy = readStringFromConsole("Input the producer:");
    _measure = readStringFromConsole("Input the measure:");
    _comment = readStringFromConsole("Input the comment:");
    _entryDate = Date();
}




int main()
{
    Good a;
    a.inputInfo();
}


