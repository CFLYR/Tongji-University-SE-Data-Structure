#define _CRT_SECURE_NO_WARNINGS
#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstring>
#include <iostream>

class MyString {
private:
    char* data;
    size_t _size;

public:
    MyString()
        : data(new char[1])
        , _size(0)
    {
        data[0] = '\0';
    }

    MyString(const char* str)
        : _size(strlen(str))
    {
        data = new char[_size + 1];
        strcpy(data, str);
    }

    MyString(const MyString& other)
        : _size(other._size)
    {
        data = new char[_size + 1];
        strcpy(data, other.data);
    }

    ~MyString()
    {
        delete[] data;
    }

    MyString& operator=(const MyString& other)
    {
        if (this != &other) {
            delete[] data;
            _size = other._size;
            data = new char[_size + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    bool operator==(const MyString& other) const
    {
        return strcmp(data, other.data) == 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyString& str)
    {
        os << str.data;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, MyString& str)
    {
        char buffer[1024];
        is >> buffer;
        str = MyString(buffer);
        return is;
    }

    const char* c_str() const { return data; }
    size_t size() const { return _size; }
    bool empty() const { return _size == 0; }
};

#endif // MYSTRING_H