#pragma once
#include <cstring>
#include <iostream>

class MyString {
private:
    char* data;
    size_t length;

public:
    MyString()
        : data(nullptr)
        , length(0)
    {
    }

    MyString(const char* str)
    {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    MyString(const MyString& other)
    {
        length = other.length;
        data = new char[length + 1];
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
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    bool operator==(const MyString& other) const
    {
        return strcmp(data, other.data) == 0;
    }

    const char* c_str() const
    {
        return data;
    }

    size_t size() const
    {
        return length;
    }

    bool empty() const
    {
        return length == 0;
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
};