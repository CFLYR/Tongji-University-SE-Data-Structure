#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <algorithm>
#include <stdexcept>

template <typename T>
class MyVector {
private:
    T* data;
    size_t capacity;
    size_t size_;

public:
    MyVector()
        : data(nullptr)
        , capacity(0)
        , size_(0)
    {
    }

    explicit MyVector(size_t n)
        : data(new T[n])
        , capacity(n)
        , size_(n)
    {
    }

    ~MyVector()
    {
        delete[] data;
    }

    void push_back(const T& value)
    {
        if (size_ == capacity) {
            size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
            T* new_data = new T[new_capacity];
            std::copy(data, data + size_, new_data);
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        data[size_++] = value;
    }

    void pop_back()
    {
        if (size_ > 0) {
            --size_;
        }
    }

    T& operator[](size_t index)
    {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const
    {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t size() const
    {
        return size_;
    }

    T* begin()
    {
        return data;
    }

    T* end()
    {
        return data + size_;
    }
};

#endif // MYVECTOR_H
