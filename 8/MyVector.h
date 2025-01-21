
#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <algorithm>
#include <cstddef>
#include <cstring>

template <typename T>
class MyVector {
private:
    T* data;
    size_t _size;
    size_t _capacity;

    void realloc(size_t new_capacity)
    {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        _capacity = new_capacity;
    }

public:
    MyVector()
        : data(nullptr)
        , _size(0)
        , _capacity(0)
    {
    }

    ~MyVector()
    {
        delete[] data;
    }

    MyVector(const MyVector& other)
        : _size(other._size)
        , _capacity(other._capacity)
    {
        data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            data[i] = other.data[i];
        }
    }

    MyVector& operator=(const MyVector& other)
    {
        if (this != &other) {
            delete[] data;
            _size = other._size;
            _capacity = other._capacity;
            data = new T[_capacity];
            for (size_t i = 0; i < _size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    void push_back(const T& value)
    {
        if (_size == _capacity) {
            size_t new_capacity = _capacity == 0 ? 1 : _capacity * 2;
            realloc(new_capacity);
        }
        data[_size++] = value;
    }

    void pop_back()
    {
        if (_size > 0)
            --_size;
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

    T& back() { return data[_size - 1]; }
    const T& back() const { return data[_size - 1]; }

    size_t size() const { return _size; }
    bool empty() const { return _size == 0; }

    T* begin() { return data; }
    const T* begin() const { return data; }
    T* end() { return data + _size; }
    const T* end() const { return data + _size; }
};

#endif // MYVECTOR_H