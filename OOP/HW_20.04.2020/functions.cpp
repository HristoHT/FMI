#ifndef __FUNCTIONS.CPP
#define __FUNCTIONS.CPP

char* type(char *str)
{
    size_t len = strlen(str);
    bool isNumber = true, isContainDot = false, isContainClomba = false, isContainOneDot = false;

    for(size_t i = 0; i < len; i ++)
    {
        if(str[i] == '.' && i + 3 < len && str[i+1] == 't' && str[i+2] == 'x' && str[i+3] == 't')
            return "txt";

        if(str[i] == '.' && i + 3 < len && str[i+1] == 'b' && str[i+2] == 'i' && str[i+3] == 'n')
            return "bin";
    }

    if(str[0] == '#')
        return "challenge";

    for(size_t i = 0; i < len; i ++)
    {
        if(str[i] < '0' || str[i] > '9')
            isNumber = false;

        if(str[i] == '.' && isContainDot)
            isContainDot = false;

        if(str[i] == '.')
        {
            isContainDot = true;
            isContainOneDot = true;
        }

        if(str[i] == '@')
            isContainClomba = true;
    }

    if(isNumber)
        return "number";
    else if(isContainClomba && isContainDot)
        return "mail";
    else if (!isContainClomba && isContainOneDot)
        return "double";
    else
        return "string";
}

double toDouble(const char *str)
{
    double number = 0, negative = 1, decimalPlace = 1;
    size_t len = strlen(str), i = 0;
    bool isDot = false;

    if(str[0] == '-')
    {
        negative = -1;
        i = 1;
    }

    for(i; i < len; i++)
    {
        if(isDot)
            decimalPlace *= 10;

        if(str[i] != '.')
        {
            number *= 10;
            number += (int)(str[i] - '0');
        }
        else
        {
            isDot =  true;
        }

    }

    return (number * negative) / decimalPlace;
}

int toInt(char *str)
{
    int number = 0, negative = 1, i = 0;
    size_t len = strlen(str);

    if(str[0] == '-')
    {
        negative = -1;
        i = 1;
    }

    for(i; i < len; i++)
    {
        number *= 10;
        number += (int)(str[i] - '0');
    }

    return number * negative;
}

bool approximatelyEqual(float a, float b, float epsilon)
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

bool definitelyGreaterThan(float a, float b, float epsilon)
{
    return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

bool definitelyLessThan(float a, float b, float epsilon)
{
    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

bool newestSort(Challange &a, Challange &b)
{
    return a.getId() > b.getId();
}

bool oldestSort(Challange &a, Challange &b)
{
    return a.getId() < b.getId();
}

bool popularSort(Challange &a, Challange &b)
{
    return a.getChallengedCount() < b.getChallengedCount();
}

void sort(Challange *begin, Challange *end, bool (*compare)(Challange&, Challange&))
{
    Challange *i = begin;

    while(i != end)
    {
        Challange *j = i + 1;
        while(j != end)
        {
            if(compare(*i, *j))
            {
                Challange c = *i;
                *i = *j;
                *j = c;
            }
            j += 1;
        }
        i += 1;
    }
}

#endif // __FUNCTIONS
