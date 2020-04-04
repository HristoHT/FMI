#ifndef __ADDITIONALFUNCTIONS_CPP
#define __ADDITIONALFUNCTIONS_CPP
#include "used-libs.cpp"
#include "additionalFunctions.h"

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
    if(result == "")
        result = "0";
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
    try
    {
        checkForPrecision(toInt(value), precision);
        inClassVar     = padStart(value, precision, "0");
    }
    catch( const std::invalid_argument& e )
    {
        inClassVar = padStart(toString(defaultValue), precision, "0");
        std::cout << e.what() << "Value (" << value << ") replaced with (" << toString(defaultValue) << ")." << std::endl;
    }

}

void checkForPrecision(int value, int prec)
{
    int i = 0, lowerBound = 0, upperBound = 0;
    while(i < prec)
    {
        upperBound *= 10;
        upperBound += 9;
        i++;
    }

    if(value > upperBound || value < lowerBound)
    {
        throw std::invalid_argument( "Received value outside the range [" + toString(lowerBound) + ", " + toString(upperBound) + "]." );
    }
}


std::string readStringFromConsole(std::string message)//Универсална функция, с която да се въвеждат стрингове
{
    try
    {
        std::string input;

        std::cout << message;
        std::cin.ignore();
        std::getline(std::cin, input);

        std::cout <<"(" << input << ")"<< input.length() << " " << STRING_LOWER_BOUND << std::endl;
        if(input.length() < STRING_LOWER_BOUND || input.length() > STRING_UPPER_BOUND)
            throw std::invalid_argument("Outside the bounds.");

        return input;
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "Input value outside the range.Please try again.";
        return readStringFromConsole(message);
    }
}

double readNumberFromConsole(std::string message)//Уневерсална функция, скоято да се въвежда число
{
    try
    {
        double input;
        std::cout << message;
        std::cin >> input;

        if(double_less(input, NUMBER_LOWER_BOUND) ||  double_less(NUMBER_UPPER_BOUND, input))
            throw std::invalid_argument("Outside the bounds");

        return input;
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "Input value outside the range.Please try again.";
        return readNumberFromConsole(message);
    }
}

bool double_equals(double a, double b)
{
    return std::abs(a - b) < EPSILONE;
}

bool double_less(double a, double b)
{
    return a - b < 0;
}

#endif // __ADDITIONALFUNCTIONS_CPP
