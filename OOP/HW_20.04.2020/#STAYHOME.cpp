#include<iostream>
#include<cstring>

class User
{
    char _name[100];
    char _email[100];
    int _age;
    size_t _id;

public:
    User(const int id = 0, const char *name = "",const char *email = "",const int age = -1):_age(age), _id(id)
    {
        setStr(name, _name);
        setStr(email, _email);
    }

    void setStr(const char *str, char *toSet)
    {
        strcpy(toSet, str);
        toSet[strlen(str)] = '\0';
    }

    void setAge(const int age)
    {
        _age = age;
    }

    char* getName()
    {
        return _name;
    }

    char* getEmail()
    {
        return _email;
    }

    size_t getID()const
    {
        return _id;
    }

    int getAge()const
    {
        return _age;
    }
};

char* type(char *str)
{
    size_t len = strlen(str);
    bool isNumber = true, isContainDot = false, isContainClomba = false;

    if(str[0] == '#')
        return "challenge";

    for(size_t i = 0; i < len; i ++)
    {
        if(str[i] < '0' || str[i] > '9')
            isNumber = false;

        if(str[i] == '.')
            isContainDot = true;

        if(str[i] == '@')
            isContainClomba = true;
    }

    if(isNumber)
        return "number";
    else if(isContainClomba && isContainDot)
        return "mail";
    else
        return "string";
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

class Challange
{
    char *_name, *_status;
    double _evaluation = 0.;
    int _challangedCount = 0;
public:
    Challange(){}

    Challange(const char *name)
    {
        setName(name);
        checkStatus();
    }

    ~Challange()
    {
        delete[] _status;
        delete[] _name;
    }

    void setName(const char *name)
    {
        delete[] _name;
        _name = new char[strlen(name) + 1];
        strcpy(_name, name);
        _name[strlen(name)] = '\0';
    }

    void setStatus(const char *status)
    {
        delete[] _status;
        _status = new char[strlen(status) + 1];
        strcpy(_status, status);
        _status[strlen(status)] = '\0';
    }

    void checkStatus()
    {
        if(_challangedCount < 2)
            setStatus("new");
        else if(_challangedCount >= 2 && _challangedCount <= 10)
            setStatus("quite recently");
        else
            setStatus("old");
    }

    void challange()
    {
        _challangedCount ++;
        checkStatus();
    }

    void challangeInfo()
    {
        std::cout << "Name: " << _name << std::endl;
        std::cout << "Challenged: " << _challangedCount << std::endl;
        std::cout << "Status: " << _status << std::endl;
        std::cout << "Evaluation: " << _evaluation << std::endl;
        std::cout << "--------------------"<<std::endl;
    }

    char* getName()
    {
        return _name;
    }
};


class Command
{
    char *_str;
    char *attr[100];
    bool _used[100];
    size_t wordsCount = 0;

    void _clearCommand()
    {
        delete[] _str;
        for(int i = 0; i < wordsCount; i ++)
            delete[] attr[i];
    }

public:
    Command(char *str = "")
    {
        setStr(str);
    }

    ~Command()
    {
        _clearCommand();
    }

    Command(Command &other)
    {
        setStr(other.getStr());
    }

    Command &operator= (char *str)
    {
        std::cout << "new command\n";
        setStr(str);
        std::cout << "new command set\n";
        return *this;
    }

    Command &operator= (Command &other)
    {
        setStr(other.getStr());
        return *this;
    }

    void setStr(char *str)
    {
        _clearCommand();
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
        _str[strlen(str)] = '\0';
        splitCommand();
    }

    void splitCommand()
    {
        wordsCount = 0;
        size_t wordLen = 0, cursorPosition = 0;
        char singleWord[100];
        print();
        for(cursorPosition; cursorPosition <= strlen(_str); cursorPosition++)
        {
            if(wordsCount > 0 && strlen(attr[wordsCount - 1]) == 0)
                wordsCount--;

            if(cursorPosition == strlen(_str))
            {
                singleWord[wordLen] = '\0';
                delete[] attr[wordsCount];
                attr[wordsCount] = new char[wordLen];
                strcpy(attr[wordsCount], singleWord);
                attr[wordsCount][wordLen] = '\0';
                wordsCount++;
                wordLen = 0;
            }

            if(cursorPosition < strlen(_str))
            {
                if(_str[cursorPosition] != ' ')
                {
                    singleWord[wordLen] = _str[cursorPosition];
                    //attr[wordsCount][wordLen] = _str[cursorPosition];
                    wordLen++;
                }
                else
                {
                    //attr[wordsCount][wordLen] = '\0';
                    singleWord[wordLen] = '\0';
                    attr[wordsCount] = new char[wordLen];
                    strcpy(attr[wordsCount], singleWord);
                    attr[wordsCount][wordLen] = '\0';
                    wordsCount++;
                    wordLen = 0;
                }
            }
        }
        std::cout << "splitCommand::2\n";

        for(int i = 0; i < wordsCount; i++)
        {
            _used[i] = 0;
        }
        _used[0] = 1;
    }

    char* operator[](size_t i)
    {
        return attr[i];
    }

    int getFirst(const char *str)
    {
        for(int i = 0; i < wordsCount; i++)
        {
            if(!_used[i] && strcmp(str, type(attr[i])) == 0)
            {
                _used[i] = 1;
                return i;
            }
        }

        return (-1);
    }

    void print()
    {
        for(size_t i = 0; i < wordsCount; i ++)
        {
            std::cout << attr[i] << " -> " << type(attr[i]) << std::endl;
        }
    }

    size_t size()
    {
        return wordsCount + 1;
    }

    char* getStr()
    {
        return _str;
    }

};



std::ostream& operator << (std::ostream& stream, User &v)
{
    stream << "Username: " << v.getName() << std::endl;
    stream << "ID: " << v.getID() << std::endl;
    if(v.getEmail() != "")
        stream << "E-mail: " << v.getEmail() << std::endl;
    if(v.getAge() != -1)
        stream << "Age: " << v.getAge() << std::endl;

    return stream;
}

class System
{
    User users[100];
    Challange challenges[100];
    size_t usersCount = 0, challengeCount = 0;

public:
    System()
    {
        std::cout <<"In";
    }

    char *getCommand(Command &command)
    {
        std::cout << "getting command\n";
        if(strcmp(type(command[0]), "string") != 0)
            return "Err: Forbidden Command";

        if(strcmp(command[0], "registration") == 0)
            return createNewUser(command);

        if(strcmp(command[0], "profile_info") == 0)
            return displayUser(command);

        if(strcmp(command[0], "challenge") == 0)
            return validateChallenge(command);

        return "Invalid command!";
    }

    char *createNewUser(Command &command)
    {
        if(command.size() < 2)
            return "Commands must have username!";

        if(type(command[1]) != "string")
            return "Second attribute must be string!";

        int emailPos = command.getFirst("mail"),
            agePos = command.getFirst("number");

        users[usersCount] = User(usersCount, command[1], (emailPos != -1 ? command[emailPos] : ""), (agePos != -1? toInt(command[agePos]): -1));
        usersCount++;

        return "User registered";
    }

    char *displayUser(Command &command)
    {
        int usernamePos = command.getFirst("string");

        if(usernamePos == -1)
            return "Include username!\n";

        int userPos = checkUser(command[usernamePos]);

        if(userPos == -1)
            return "The user doesn't exist!\n";

        std::cout << users[userPos];;
        return "Done!\n";
    }

    char *validateChallenge(Command &command)
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
        std::cout << "currentPos = " << currentPos << std::endl;
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
            challenges[challengeCount] = Challange(command[challengeNamePos]);
            challengePos = challengeCount;
            challengeCount++;
        }

        for(size_t i = firstChallengedPos; i <= lastChallengedPos; i++)
        {
            challenges[challengePos].challange();
        }

        challenges[challengePos].challangeInfo();

        return "Challenge send!";
    }

    int checkUser(const char *username)
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

    int checkChallenge(const char *name)
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

    char* listUsers()
    {
        std::cout << "Tuka trqbva da se izvedat userite: " << std::endl;
        for(int i = 0; i < usersCount; i++)
        {
            std::cout << users[i] << std::endl;
        }

        return "Users listed";
    }
};

int main()
{
    std::cout << 0 << std::endl;
    System db;
    std::cout << 1 << std::endl;
    Command a("registration username ico@gmail.com 20");
    std::cout<<db.getCommand(a)<<std::endl;
    std::cout << 2 << std::endl;
    a = "registration username2 ico@g2mail.com 23";
    std::cout<<db.getCommand(a)<<std::endl;
    std::cout << 3 << std::endl;
    a = "registration username3 ico@g2mail.com 23";
    std::cout<<db.getCommand(a)<<std::endl;
    std::cout << 4 << std::endl;

    a = "challenge username #test username2 username3";
    std::cout<<db.getCommand(a)<<std::endl;
    std::cout << 5 << std::endl;

}
