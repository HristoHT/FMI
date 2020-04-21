#ifndef __COMMAND.CPP
#define __COMMAND.CPP

void Command::_clearCommand()
{
    for(int i = 0; i < wordsCount; i ++)
        delete[] attr[i];

    if(_str != nullptr)
    {
        delete[] _str;
    }
}

Command::Command(char *str = "")
{
    wordsCount = 0;
    setStr(str);
}

Command::~Command()
{
    _clearCommand();
    wordsCount = 0;
}

Command::Command(Command &other)
{
    setStr(other.getStr());
}

Command &Command::operator= (char *str)
{
    setStr(str);
    return *this;
}

Command &Command::operator= (Command &other)
{
    setStr(other.getStr());
    return *this;
}

void Command::setStr(char *str)
{
    _clearCommand();
    _str = new char[strlen(str) + 1];
    strcpy(_str, str);
    _str[strlen(str)] = '\0';
    splitCommand();
}

void Command::splitCommand()
{
    wordsCount = 0;
    size_t wordLen = 0, cursorPosition = 0;
    char singleWord[MAX_COMMAND_WORD_LENGTH];
    //std::cout << "---><<>><<><>><<";
    for(cursorPosition; cursorPosition <= strlen(_str); cursorPosition++)
    {
        //std::cout << cursorPosition << std::endl;
        if(wordsCount > 0 && strlen(attr[wordsCount - 1]) == 0)
            wordsCount--;

        if(cursorPosition == strlen(_str))
        {
            //std::cout << "-1" << std::endl;
            singleWord[wordLen] = '\0';
            //std::cout << "-2" << std::endl;
            //delete[] attr[wordsCount];
            //std::cout << "-3" << std::endl;
            attr[wordsCount] = new char[wordLen];
            //std::cout << "-4" << std::endl;
            strcpy(attr[wordsCount], singleWord);
            //std::cout << "-5" << std::endl;
            attr[wordsCount][wordLen] = '\0';
            //std::cout << "-6" << std::endl;
            wordsCount++;
            //std::cout << "-7" << std::endl;
            wordLen = 0;
            //std::cout << "-8" << std::endl;
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

    for(int i = 0; i < wordsCount; i++)
    {
        _used[i] = 0;
    }
    _used[0] = 1;
}

char* Command::operator[](size_t i)
{
    return attr[i];
}

int Command::getFirst(const char *str)
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

void Command::print()
{
    for(size_t i = 0; i < wordsCount; i ++)
    {
        std::cout << attr[i] << " -> " << type(attr[i]) << std::endl;
    }
}

size_t Command::size()
{
    return wordsCount;
}

char* Command::getStr()
{
    return _str;
}

#endif // __COMMAND
