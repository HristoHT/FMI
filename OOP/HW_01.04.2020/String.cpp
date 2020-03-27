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
    void addb(const char &ch)
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

    void addf(const char &ch)
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

    String concat(String other)
    {
        String newString;

        for(size_t i = 0; i < len; i ++)
            newString += data[i];
        for(size_t i = 0; i < other.lngth(); i ++)
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
        copyString(other);
        return *this;
    }

    String &operator += (const char ch)
    {
        addb(ch);
        return *this;
    }

    String &operator += (String other){
         for(size_t i = 0; i < other.lngth(); i ++)
            *this += other[i];
    }

    String operator + (const char &ch)
    {
        String newString(*this);
        newString += ch;
        return newString;
    }

    String operator + (String other){
        String newString(*this);
        newString += other;
        return newString;
    }

    char operator [] (const size_t &pos) const
    {
        return data[pos];
    }

    char &operator [] (const size_t &pos)
    {
        return data[pos];
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

    int lngth()
    {
        return len;
    }

};

String operator + (char ch, const String &other){
    String newString(other);
    newString.addf(ch);
    return newString;
}

int main()
{
    String a = "1", b = "2", c = "3", d = "4";

    d += a + b.concat(c);

    d = '-' + d + '-';
    cout << 1 << endl;
    d.print();
    return 0;
}
