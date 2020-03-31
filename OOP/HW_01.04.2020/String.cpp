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
        //cout << "Destroyed pointer: " << &data << endl;
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

        //cout << "Length: " << len << endl;
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

    void setLength()
    {
        len = strlen(data);
    }

    void setData(char *newData)
    {
        delete[] data;
        data = newData;
        len = strlen(newData);
    }

    String *split(String str, size_t &length)
    {
        String newCopy(*this);
        size_t newLen = 0, nextPos = newCopy.indexOf(str);
        vector <int> pos;

        while(nextPos != -1)
        {
            pos.push_back(nextPos);
            newCopy = newCopy.substr(nextPos + 1, newCopy.length());
            nextPos = newCopy.indexOf(str);
            if(newCopy.indexOf(str) == -1)
                nextPos = -1;
        }
        pos.push_back(newCopy.length());

        String *arr = new String[pos.size()];
        int st = 0;

        for(size_t i = 0; i < pos.size(); i ++)
        {
            arr[i] = substr(st, pos[i]);
            st += pos[i] + 1;
        }

        length = pos.size();
        return arr;
    }

    String caseInsensitive()
    {
        String newString;

        for(size_t i = 0; i < len; i ++)
        {
            if((data[i] - 'a') >= 0 && (data[i] - 'a') <= 25)
                newString += (data[i] - 'a') + 'A';
            else
                newString += data[i];
        }

        return newString;
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

    for(size_t i = 0; i < lenFirst; i++)
        newData[i] =  first[i];

    for(size_t i = 0; i < other.length(); i++)
        newData[i + lenFirst] =  other[i];

    newData[lenFirst + other.length()] = '\0';
    newString.setData(newData);

    return newString;
}

String join(String *splitedStrings, size_t length, String joiner)
{
    String newString = splitedStrings[0];

    for(size_t i = 1; i < length; i ++)
        newString += joiner + splitedStrings[i];


    return newString;
}

ostream &operator << (ostream& stream, const String &v)
{

    for (size_t i = 0; i < v.length(); i++)
    {
        stream << v[i];
    }
    return stream;
}

int main()
{
    String a = "z-a-b-c", *b, c, d;
    size_t len;
    b = a.split("-", len);
    d = a.caseInsensitive();
    cout << "Len = " << len << endl;
    c =join(b, len, "-");
    cout << d << endl;
    cout << *(b + 1) << endl;

    return 0;
}
