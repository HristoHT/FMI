#ifndef __CHALLENGE.CPP
#define __CHALLENGE.CPP

Challange::Challange(const char *name = "", size_t id = 0):_id(id)
{
    setName(name);
    checkStatus();
}

Challange::~Challange()
{
    if(_name)
        delete[] _name;
    if(_status)
        delete[] _status;
}

Challange::Challange(const Challange &other)
{
    _copyChallange(other);
}

Challange& Challange::operator= (const Challange &other)
{
    _copyChallange(other);
    return *this;
}

void Challange::_copyChallange(const Challange &other)
{
    _evaluation = other.getEval();
    _responsedToChallenge = other.getResponded();
    _challangedCount = other.getChallengedCount();
    _id = other.getId();
    setName(other.getName());
    checkStatus();
}

double Challange::getEval()const
{
    return _evaluation;
}
double Challange::getResponded()const
{
    return _responsedToChallenge;
}

void Challange::setName(const char *name)
{
    if(_name)
        delete[] _name;
    _name = new char[strlen(name) + 1];
    strcpy(_name, name);
    _name[strlen(name)] = '\0';
}

void Challange::setStatus(const char *status)
{
    if(_status)
        delete[] _status;
    _status = new char[strlen(status) + 1];
    strcpy(_status, status);
    _status[strlen(status)] = '\0';
}

void Challange::checkStatus()
{
    if(_challangedCount < 2)
        setStatus("new");
    else if(_challangedCount >= 2 && _challangedCount <= 10)
        setStatus("quite recently");
    else
        setStatus("old");
}

void Challange::challange()
{
    _challangedCount ++;
    checkStatus();
}

void Challange::update(double val)
{
    _evaluation += val;
    _responsedToChallenge += 1;
}

void Challange::challangeInfo()
{
    std::cout  << "system :>"
               << std::setw(31) << _name << "|"
               << std::setw(15) << _challangedCount << "|"
               << std::setw(20) << _status << "|"
               << std::setw(15) << (_challangedCount != 0 ?_evaluation / _challangedCount:0) << "|"
               << std::setw(15) << _id << "|"<< std::endl;
}

char* Challange::getName()const
{
    return _name;
}

size_t Challange::getId()const
{
    return _id;
}

int Challange::getChallengedCount()const
{
    return (int)(_challangedCount);
}
#endif // __CHALLENGE
