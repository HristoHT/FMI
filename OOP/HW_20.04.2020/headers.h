#ifndef __HEADERS.h
#define __HEADERS.h

class User
{
    char _name[MAX_USER_NAME_LENGTH];
    char _email[MAX_USER_MAIL_LENGTH];
    char **_challenges = nullptr;
    int _age;
    size_t _id, _challengeCount;

    void _deleteChallenges();
public:
    User(const int id, const char *name, const char *email, const int age);
    ~User();
    void setStr(const char *str, char *toSet);
    char* getName();
    char* getEmail();
    int getAge()const;
    int getChallenge(char* challengeName);
    size_t getID()const;
    void print();
    void addChallenge(char *challengeName);
    void deleteChallenge(char *challengeName);
    void printChallenges();
    void setAge(const int age);
};

class Challange
{
    char *_name = nullptr, *_status = nullptr;
    double _evaluation = 0., _responsedToChallenge = 0.;
    int _challangedCount = 0;
    size_t _id;
public:
    Challange(const char *name, size_t id);
    ~Challange();
    Challange &operator= (const Challange &other);
    Challange(const Challange &other);
    void setName(const char *name);
    void setStatus(const char *status);
    void checkStatus();
    void challange();
    void update(double val);
    void challangeInfo();
    char *getName()const;
    size_t getId()const;
    int getChallengedCount()const;

    void _copyChallange(const Challange &other);

    double getEval()const;
    double getResponded()const;
};

class Command
{
    char *_str = nullptr;
    char *attr[MAX_COMMAND_WORD_LENGTH];
    bool _used[MAX_COMMAND_WORD_LENGTH];
    size_t wordsCount;
    void _clearCommand();
public:
    Command(char *str);
    ~Command();
    Command(Command &other);
    Command &operator= (char *str);
    Command &operator= (Command &other);
    void setStr(char *str);
    void splitCommand();
    char* operator[](size_t i);
    int getFirst(const char *str);
    void print();
    size_t size();
    char* getStr();
};

class System
{
    User users[MAX_USERS];
    Challange challenges[MAX_CHALLENGES];
    size_t usersCount, challengeCount;

public:
    System();

    void getCommand(Command &command);
    char *runCommand(Command &command);
    char *finishChallenge(Command &command);
    char *createNewUser(Command &command);
    char *displayUser(Command &command);
    char *validateChallenge(Command &command);
    char *bulkLoad(Command &command);
    char *bulkLoadChallenges(const char *filename);
    char *bulkLoadUsers(const char *filename);
    char *addNewChallenge(Command &command);

    int checkUser(const char *username);
    int checkChallenge(const char *name);

    void printUsers();
    char *printChallenges(Command &command);
    char *generateBinFile(Command &command);
    void displayCommand(char *command, char *description);
    void showHelp();
};



char* type(char *str);
int toInt(char *str);
double toDouble(const char *str);
bool approximatelyEqual(float a, float b, float epsilon);
bool definitelyGreaterThan(float a, float b, float epsilon);
bool definitelyLessThan(float a, float b, float epsilon);
void InsertionSort(Challange &arr, int *begin, int *end, void (*howToSort)(Challange, Challange));

bool newestSort(Challange &a, Challange &b);
bool oldestSort(Challange &a, Challange &b);
bool popularSort(Challange &a, Challange &b);

void sort(Challange *begin, Challange *end, bool (*compare)(Challange&, Challange&));

#endif // __HEADERS
