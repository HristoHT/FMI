#include<iostream>
#include<cstring>
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
        cout << "Desroyed string: ";
        print();
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

    bool operator == (String other)//Comparison
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

    int indexOf(const String &str)const
    {

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

    int length()
    {
        return len;
    }

};

String operator + (char ch, const String &other)
{
    String newString(other);
    newString.addf(ch);
    return newString;
}

int main()
{
    String a = "1", b = "2", c = "3", d = "4";

    d += a + b.concat(c);

    d = '-' + d + '-';
    d.print();

    --d--;

    d.print();
    return 0;
}
