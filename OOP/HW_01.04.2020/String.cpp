#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

class String
{
    size_t len = 0;
    char *data;
    void copyString(const char *str)
    {
        len = strlen(str);
        char *strng = new char[len + 1];

        for(size_t i = 0; i < len; i ++)
        {
            strng[i] = str[i];
        }
        strng[len] = '\0';

        data = strng;
    }

    void copyString(const String &other)
    {
        copyString(other.data);
    }



public:
    String concat(String other)
    {
        String newString;

        for(size_t i = 0; i < len; i ++)
            newString += data[i];
        for(size_t i = 0; i < other.length(); i ++)
            newString += other[i];

        return newString;
    }

    String()
    {
        copyString("");
    }

    String(const char *str)
    {
        copyString(str);
    }

    String(const String &other)
    {
        copyString(other);
    }

    ~String()
    {
        //cout << "Desroyed string: ";
        //print();
        delete[] data;
    }


    String operator = (const char *str)
    {
        copyString(str);
        return *this;
    }

    String operator = (const String &other)
    {
        if(&other != this)
            copyString(other);
        return *this;
    }

    String &operator += (const char ch)
    {
        addb(ch);
        return *this;
    }

    String &operator += (String other)
    {
        for(size_t i = 0; i < other.length(); i ++)
            *this += other[i];
    }

    String operator + (const char &ch)
    {
        String newString(*this);
        newString += ch;
        return newString;
    }

    String operator + (String other)
    {
        String newString(*this);
        newString += other;
        return newString;
    }

    String operator -- (const int h)
    {
        return  popb();
    }

    String operator -- ()
    {
        return  popf();
    }

    bool operator == (const String &other)const//Comparison
    {
        if(len != other.length())
            return false;
        else
        {
            for(size_t i = 0; i < len; i ++)
                if(data[i] != other[i])
                    return false;
        }
        return true;
    }

    bool operator != (const String &other)const
    {
        return !(*this==other);
    }

    char operator [] (const size_t &pos) const
    {
        return data[pos];
    }

    char &operator [] (const size_t &pos)
    {
        return data[pos];
    }

    void addb(const char &ch)//Add back
    {
        char *newData = new char[len + 1];
        for (size_t i = 0; i < len; i++)
        {
            newData[i] = data[i];
        }
        newData[len] = ch;
        newData[len + 1] = '\0';

        delete[] data;
        data = newData;
        len++;
    }

    void addf(const char &ch)//Add front
    {
        char *newData = new char[len + 1];
        newData[0] = ch;
        for (size_t i = 1; i <= len; i++)
        {
            newData[i] = data[i - 1];
        }
        newData[len + 1] = '\0';

        delete[] data;
        data = newData;
        len++;
    }

    String substr(const size_t &st, const size_t &length)
    {
        String newString;

        for(size_t i = st; i < min(st + length, len); i ++)
        {
            newString += data[i];
        }

        return newString;
    }

    String popf() // Pop front
    {
        char *newData = new char[len - 1];
        String toReturn = substr(0, 1);

        for (size_t i = 1; i < len; i++)
        {
            newData[i - 1] = data[i];
        }
        newData[len - 1] = '\0';

        delete[] data;
        data = newData;
        len--;
        cout << "toRetrurn:";
        toReturn.print();
        return toReturn;
    }

    String popb() // Pop back
    {
        char *newData = new char[len - 1];
        String toReturn = substr(len - 1, 1);

        for (size_t i = 0; i < len - 1; i++)
        {
            newData[i] = data[i];
        }
        newData[len - 1] = '\0';

        delete[] data;
        data = newData;
        len--;

        return toReturn;
    }

    int indexOf(String str)
    {
        size_t compLen = str.length();
        String newString = substr(0, compLen);


        for(size_t i = compLen; i <= len; i ++)
        {
            if(newString == str)
                return i - compLen;

            --newString;

            if(i < len)
                newString+=data[i];
        }

        return -1;
    }

    void print()
    {
        cout << '"';
        for(size_t i = 0; i < len; i ++)
        {
            cout << data[i];
        }
        cout << '"';
        cout << endl;
    }

    int length()const
    {
        return len;
    }

    void setData(char *newData){
        delete[] data;
        data = newData;
        len = strlen(newData);
    }

};

String operator + (char ch, const String &other)
{
    String newString(other);
    newString.addf(ch);
    return newString;
}

String operator + (char first[], String &other)
{
    char *newData = new char[strlen(first) + other.length()];
    String newString;
    int lenFirst = strlen(first);

    for(size_t i = 0; i < lenFirst; i++)newData[i] =  first[i];
    for(size_t i = 0; i < other.length(); i++)newData[i + lenFirst] =  other[i];
    newData[lenFirst + other.length()] = '\0';
    newString.setData(newData);
    return newString;
}

vector<String> split(String toSplit, String str)
{
    String newCopy(toSplit);
    size_t newLen = 0, nextPos = newCopy.indexOf(str);
    vector <int> pos;

    //pos.push_back(-1);
    while(nextPos != -1)
    {
        pos.push_back(nextPos);
        newCopy = newCopy.substr(nextPos + 1, newCopy.length());
        nextPos = newCopy.indexOf(str);
        if(newCopy.indexOf(str) == -1)
            nextPos = -1;
    }
    pos.push_back(newCopy.length());

    vector<String> newVector;
    int st = 0;
    for(size_t i = 0; i < pos.size(); i ++)
    {
        newVector.push_back(toSplit.substr(st, pos[i]));
        st += pos[i] + 1;
    }

    return newVector;
}

int main()
{
    String a = "1", b = "2", c = "3", d = "4", *arr;

    d = '-' + a + "-" + b + "--" + c + "-" + d+ "-";
    d.print();

    vector<String> z = split(d, "-");

    for(size_t i = 0; i < z.size(); i ++)
    {
        z[i].print();
    }

    //d[0].print();
    return 0;
}
