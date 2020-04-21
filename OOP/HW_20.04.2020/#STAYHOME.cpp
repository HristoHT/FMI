#include<algorithm>
#include<iostream>
#include<cstring>
#include <iomanip>
#include <fstream>

const int MAX_USERS = 1000;
const int MAX_CHALLENGES = 1000;
const int MAX_COMMAND_LENGTH = 1000;
const int MAX_COMMAND_WORD_LENGTH = 100;
const int MAX_USER_NAME_LENGTH = 100;
const int MAX_USER_MAIL_LENGTH = 100;

#include "headers.h"
#include "classUser.cpp"
#include "classChallenge.cpp"
#include "classCommand.cpp"
#include "classSystem.cpp"
#include "functions.cpp"


int main()
{
    System db;
    Command a;
    char *str = new char[MAX_COMMAND_LENGTH];

    std::cout << "system :>Type help for list with all commands;\n";

    while(!std::cin.eof())
    {
        std::cout << "command:>";
        std::cin.getline(str, MAX_COMMAND_LENGTH);
        a = str;
        db.getCommand(a);
    }

    return 0;
}
