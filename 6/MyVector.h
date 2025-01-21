#pragma once
#include <algorithm>
#include <stdexcept>

template <typename T>
class MyVector {
private:
    T* data;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity)
    {
        T* new_data = new T[new_capacity];
        std::copy(data, data + size_, new_data);
        delete[] data;
        data = new_data;
        capacity_ = new_capacity;
    }

public:
    MyVector()
        : data(nullptr)
        , size_(0)
        , capacity_(0)
    {
    }

    ~MyVector()
    {
        delete[] data;
    }

    void push_back(const T& value)
    {
        if (size_ == capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            resize(new_capacity);
        }
        data[size_++] = value;
    }

    void pop_back()
    {
        if (size_ > 0) {
            --size_;
        }
    }

    T& back()
    {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return data[size_ - 1];
    }

    T& operator[](size_t index)
    {
        return data[index];
    }

    const T& operator[](size_t index) const
    {
        return data[index];
    }

    size_t size() const
    {
        return size_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

    typedef T* iterator;
    typedef const T* const_iterator;

    iterator begin()
    {
        return data;
    }

    iterator end()
    {
        return data + size_;
    }

    const_iterator begin() const
    {
        return data;
    }

    const_iterator end() const
    {
        return data + size_;
    }
};