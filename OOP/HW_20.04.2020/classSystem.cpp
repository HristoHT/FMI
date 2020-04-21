#ifndef __SYSTEM.CPP
#define __SYSTEM.CPP
System::System()
{
    usersCount = 0;
    challengeCount = 0;
}

char *System::runCommand(Command &command)
{
    if(strcmp(type(command[0]), "string") != 0)
        return "Err: Forbidden Command";

    if(strcmp(command[0], "registration") == 0)
        return createNewUser(command);

    if(strcmp(command[0], "profile_info") == 0)
        return displayUser(command);

    if(strcmp(command[0], "finish") == 0)
        return finishChallenge(command);

    if(strcmp(command[0], "challenge") == 0)
        return validateChallenge(command);

    if(strcmp(command[0], "new_challenge") == 0)
        return addNewChallenge(command);

    if(strcmp(command[0], "load") == 0)
        return bulkLoad(command);

    if(strcmp(command[0], "list_by") == 0)
        return printChallenges(command);

    if(strcmp(command[0], "export") == 0)
    return generateBinFile(command);

    if(strcmp(command[0], "help") == 0)
    {
        showHelp();
        return "";
    }

    return "Invalid command!";
}

void System::showHelp()
{
    std::cout << "system :>";
    for(int i = 0; i < 76; i ++)
        std::cout << "-";
    std::cout << std::endl;
    std::cout << "system :>|"<<std::setw(25)<<"Command|"<< std::setw(50) << "Attributes|" << "\n";
    displayCommand("registration|", "<username> ( <age> or <e-mail> )|");
    displayCommand("profile_info|", "<username>|");
    displayCommand("finish|", "<userId> #<challengeName> <int/double>|");
    displayCommand("challenge|", "<user> #<challengeName> <uername1> ... <uernameN>|");
    displayCommand("new_challenge|", "#<challengeName>|");
    displayCommand("load|", "<filename>.txt or <filename>.bin|");
    displayCommand("list_by|", "<sorttype> (newest, oldest, most_popular)|");
    displayCommand("export|", "<filename>.bin generate bin file ready to be loaded|");
    std::cout << "system :>";
    for(int i = 0; i < 76; i ++)
        std::cout << "-";
    std::cout << std::endl;
}

void System::displayCommand(char* command, char* description)
{
    std::cout  << "system :>|"<< std::setw(25) << command << std::setw(50) << description << "\n";
}

void System::getCommand(Command &command)
{
    std::cout << "system :>" << runCommand(command) << "\n";
}

char *System::finishChallenge(Command &command)
{
    int challengeTagPos = command.getFirst("challenge"),
        userIdPos = command.getFirst("number"),
        doublePos = command.getFirst("double"),
        intPos = command.getFirst("number");

    if(challengeTagPos == -1)
        return "Must contain #<challenge>!";

    if(userIdPos == -1)
        return "Must contain <username>!";

    if(doublePos == -1 && intPos == -1)
        return "Must contain <value>!";

    double val = 0;

    if(doublePos != -1)
        val = toDouble(command[doublePos]);
    else if(intPos != -1)
        val = toInt(command[intPos]);

    if( definitelyLessThan(val, -5., 0.01) || definitelyGreaterThan(val, 10., 0.01))
        return "Rate value must be in [-5.0, 10.0] range!";

    int userId = toInt(command[userIdPos]),
        challengeId = checkChallenge(command[challengeTagPos]);

    if(challengeId == -1)
        return "This challenge doesn't exist!";

    if(users[userId].getChallenge(command[challengeTagPos]) == -1)
        return "The current user has finished or hasn't been challenged for the challenge!";

    users[userId].deleteChallenge(command[challengeTagPos]);
    challenges[challengeId].update(val);

    return "Challenge finished!";
}

char *System::createNewUser(Command &command)
{
    if(command.size() < 2)
        return "Commands must have <username>!";

    if(type(command[1]) != "string")
        return "Second attribute must be string!";

    int emailPos = command.getFirst("mail"),
        agePos = command.getFirst("number");

    if(checkUser(command[1]) != -1)
        return "User already exist!";

    if(agePos != -1 && (toInt(command[agePos]) < 0 || toInt(command[agePos]) > 90))
        return "User's age must be in the range [0, 90]!";

    if(emailPos != -1 && strlen(command[emailPos]) > 100)
        return "User's e-mail must be less than 100!";

    users[usersCount] = User(usersCount, command[1], (emailPos != -1 ? command[emailPos] : ""), (agePos != -1? toInt(command[agePos]): -1));
    usersCount++;

    return "User registered";
}

char *System::displayUser(Command &command)
{
    int usernamePos = command.getFirst("string");

    if(usernamePos == -1)
        return "Include username!";

    int userPos = checkUser(command[usernamePos]);

    if(userPos == -1)
        return "The user doesn't exist!";

    users[userPos].print();

    return "Done!";
}

char *System::validateChallenge(Command &command)
{
    int challengeNamePos = command.getFirst("challenge");

    if(challengeNamePos == -1)
        return "Challenge name must be with format: #<name>!";

    if(challengeNamePos != 2)
        return "Challenge name must be right after the <username>!";

    if(strlen(command[challengeNamePos]) > 31)
        return "Challenge name must be with max length 31!";

    int challengerPos = command.getFirst("string");

    if(challengerPos == -1)
        return "Missing challenger!";

    if(checkUser(command[challengerPos]) == -1)
        return "The challenger is not registered!";

    int firstChallengedPos = command.getFirst("string");

    if(firstChallengedPos == -1)
        return "There must be at least one challenged!";

    if(checkUser(command[firstChallengedPos]) == -1)
        return "Not all users exist!";

    int lastChallengedPos = firstChallengedPos, currentPos = command.getFirst("string");

    while(currentPos != -1)//Тука ако има нещо различно от стринг ще стане грозно, трябва да имплементирам вектор, но има изискване в условието
    {
        if(checkUser(command[currentPos]) == -1)
            return "Not all users exist!";
        lastChallengedPos = currentPos;
        currentPos = command.getFirst("string");
    }

    int challengePos = checkChallenge(command[challengeNamePos]);

    if(challengePos == -1)
    {
        challenges[challengeCount] = Challange(command[challengeNamePos], challengeCount);
        challengePos = challengeCount;
        challengeCount++;
    }

    for(size_t i = firstChallengedPos; i <= lastChallengedPos; i++)
    {
        size_t userPos = checkUser(command[i]);
        if(users[userPos].getChallenge(command[challengeNamePos]) == -1)
        {
            challenges[challengePos].challange();
            users[userPos].addChallenge(command[challengeNamePos]);
        }
    }

    //challenges[challengePos].challangeInfo();
    return "Challenge send!";
}

char *System::bulkLoadUsers(const char *filename)
{
    char buffer[1024];
    Command newCommand;

    std::ifstream myfile(filename);

    if (!myfile)
        return "Unable to open your file!";


    while (myfile.getline(buffer, sizeof(buffer)))
    {
        std::cout <<"file   :>"<< buffer << "\n";
        newCommand = buffer;
        getCommand(newCommand);
    }
    myfile.close();
    return "Txt file processed!";
}

char *System::bulkLoad(Command &command)
{
    int txt = command.getFirst("txt"),
        bin = command.getFirst("bin");

    if(txt != -1)
        return bulkLoadUsers(command[txt]);

    if(bin != -1)
        return bulkLoadChallenges(command[bin]);

    return "Something got wrong!";
}

int System::checkUser(const char *username)
{
    for(size_t i = 0; i < usersCount; i++)
    {
        if(strcmp(users[i].getName(), username) == 0)
        {
            return i;
        }
    }
    return -1;
}

int System::checkChallenge(const char *name)
{
    for(size_t i = 0; i < challengeCount; i++)
    {
        if(strcmp(challenges[i].getName(), name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void System::printUsers()
{
    std::cout << usersCount << std::endl;
    for(int i = 0; i < usersCount; i++)
        users[i].print();
}

char *System::printChallenges(Command &command)
{
    int sortTypePos = command.getFirst("string");

    if(strcmp(command[sortTypePos], "newest") != 0 && strcmp(command[sortTypePos], "oldest") != 0 && strcmp(command[sortTypePos], "most_popular") != 0)
        return "Unknown sort!";

    bool (*howToSort)(Challange&, Challange&);

    if(strcmp(command[sortTypePos], "newest") == 0)
        howToSort = newestSort;
    else if(strcmp(command[sortTypePos], "oldest") == 0)
        howToSort = oldestSort;
    else
        howToSort = popularSort;

    sort(challenges, challenges + challengeCount, howToSort);

    std::cout << "system :>";
    for(int i = 0; i < 101; i++)
        std::cout << "-";
    std::cout << "\n";
    std::cout  << "system :>"
               << std::setw(32) << "Name|"
               << std::setw(16) << "Challenged|"
               << std::setw(21) << "Status|"
               << std::setw(16) << "Rating|"
               << std::setw(16) << "ID|" << std::endl;

    for(int i = 0; i < challengeCount; i++)
        challenges[i].challangeInfo();

    std::cout  << "system :>";
    for(int i = 0; i < 101; i++)
        std::cout << "-";
    std::cout << std::endl;

    return "Challenges displayed!";
}

char* System::generateBinFile(Command &command)
{
    int bin = command.getFirst("bin");

    if(bin == -1)
        return "Missing <filename>.bin!";

    std::ofstream BinOut(command[bin], std::ios::out | std::ios::binary);

    for(size_t i = 0; i < challengeCount; i ++)
    {
        size_t nameLen = strlen(challenges[i].getName());
        BinOut.write((char*) &nameLen, sizeof(nameLen));
        BinOut.write(challenges[i].getName(), nameLen);
    }

    BinOut.close();
    return "File saved!";
}

char *System::addNewChallenge(Command &command)
{
    int challengeNamePos = command.getFirst("challenge");

    if(challengeNamePos == -1)
        return "Challenge name must be with format: #<name>!";

    if(strlen(command[challengeNamePos]) > 31)
        return "Challenge name must be with max length 31!";

    if(checkChallenge(command[challengeNamePos]) != -1)
        return "Challenge already exist!";

    challenges[challengeCount] = Challange(command[challengeNamePos], challengeCount);
    challengeCount++;

    return "Challenge added!";

}

char *System::bulkLoadChallenges(const char *filename)
{
    std::ifstream binFile(filename, std::ios::in | std::ios::binary);

    if(!binFile)
        return "Cannot open the bin file!\n";

    Command a;

    while(binFile)
    {
        size_t len = 0;
        binFile.read((char*)&len, sizeof(len));
        char *newChallengeName = new char[len + 14];
        strcpy(newChallengeName, "new_challenge ");
        binFile.read(newChallengeName + 14, len);
        newChallengeName[len + 14] = '\0';
        a = newChallengeName;

        if(len != 0)
        {
            getCommand(a);
            std::cout << "file   :>" << newChallengeName << "\n";
        }
    }

    return "Bin file processed!";
}
#endif // __SYSTEM
