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
        char *strng = new char[len];

        for(size_t i = 0; i < len; i ++)
        {
            strng[i] = str[i];
        }

        data = strng;

    }

    void copyString(const String &other)
    {
        copyString(other.data);
    }
public:
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

int main()
{

    String b = "12345", c = b;

    cout << b.lngth() << endl;
    b.print();

    cout << c.lngth() << endl;
    c.print();

    return 0;
}
