#ifndef __USER.CPP
#define __USER.CPP

void User::_deleteChallenges()
{
    for(size_t i = 0; i < _challengeCount ; i++)
        delete[] _challenges[i];

    if(_challenges)
        delete[] _challenges;
    _challengeCount = 0;
}

User::User(const int id = 0, const char *name = "",const char *email = "Unknown",const int age = -1):_age(age), _id(id)
{
    if(strcmp(email, "") == 0)
        setStr("Unknown", _email);
    else
        setStr(email, _email);
    setStr(name, _name);
    _challengeCount = 0;
}

User::~User()
{
    _deleteChallenges();
}

void User::setStr(const char *str, char *toSet)
{
    strcpy(toSet, str);
    toSet[strlen(str)] = '\0';
}

void User::setAge(const int age)
{
    _age = age;
}

char* User::getName()
{
    return _name;
}

char* User::getEmail()
{
    return _email;
}

size_t User::getID()const
{
    return _id;
}

int User::getAge()const
{
    return _age;
}

void User::print()
{
    std::cout  << "system:>"<< "----------------------\n";
    std::cout  << "system:>"<< "Username: " << _name << std::endl;
    std::cout  << "system:>"<< "ID: " << _id << std::endl;
    std::cout  << "system:>"<< "E-mail: " << _email << std::endl;
    if(_age != -1)
        std::cout  << "system:>"<< "Age: " << _age << std::endl;
    else
        std::cout  << "system:>"<< "Age: Unknown\n";
    printChallenges();
    std::cout  << "system:>"<< "----------------------\n";
}

void User::addChallenge(char *challengeName)
{
    size_t newLen = _challengeCount + 1;
    char **newBufer = new char*[newLen];

    //std::cout << "Coping challenges: ";
    for(size_t i = 0; i < _challengeCount; i ++)
    {
        char *challenge = new char[strlen(_challenges[i]) + 1];
        strcpy(challenge, _challenges[i]);
        challenge[strlen(_challenges[i])] = '\0';
        newBufer[i] = challenge;
        //std::cout << '"' << newBufer[i] << '"' << " ";
    }
    //std::cout << std::endl;

    newBufer[_challengeCount] = new char[strlen(challengeName) + 1];
    strcpy(newBufer[_challengeCount], challengeName);
    newBufer[_challengeCount][strlen(challengeName)] = '\0';

    //std::cout << "Adding challenge: " << newBufer[_challengeCount] << std::endl;

    _deleteChallenges();
    _challengeCount = newLen;
    _challenges = newBufer;
}

void User::deleteChallenge(char *challengeName)
{
    size_t newLen = _challengeCount - 1, newBuffPos = 0;
    char **newBufer = new char*[newLen];

    for(size_t i = 0; i < _challengeCount; i ++)
    {
        if(strcmp(challengeName, _challenges[i]) != 0)
        {
            char *challenge = new char[strlen(_challenges[i]) + 1];
            strcpy(challenge, _challenges[i]);
            challenge[strlen(_challenges[i])] = '\0';

            newBufer[newBuffPos] = challenge;
            newBuffPos ++;
        }
    }

    _deleteChallenges();
    _challengeCount = newLen;
    _challenges = newBufer;
}

int User::getChallenge(char* challengeName)
{
    for(size_t i = 0; i < _challengeCount; i++)
    {
        if(strcmp(challengeName, _challenges[i]) == 0)
        {
            return i;
        }
    }

    return -1;
}

void User::printChallenges()
{

    std::cout  << "system:>" << "Challenged to do: ";
    for(size_t i = 0; i < _challengeCount; i++)
    {
        std::cout << _challenges[i];

        if(i+1 != _challengeCount)
            std::cout<<", ";

    }
    std::cout<<std::endl;
}


#endif
