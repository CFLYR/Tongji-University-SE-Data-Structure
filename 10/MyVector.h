#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <algorithm>
#include <cstddef>
#include <stdexcept>

template <typename T>
class MyVector {
private:
    T* data;
    size_t size_;
    size_t capacity_;

public:
    MyVector()
        : data(nullptr)
        , size_(0)
        , capacity_(0)
    {
    }

    explicit MyVector(size_t n)
        : data(new T[n])
        , size_(n)
        , capacity_(n)
    {
        for (size_t i = 0; i < n; ++i) {
            data[i] = T();
        }
    }

    MyVector(const MyVector& other)
        : data(new T[other.size_])
        , size_(other.size_)
        , capacity_(other.size_)
    {
        std::copy(other.data, other.data + size_, data);
    }

    ~MyVector()
    {
        delete[] data;
    }

    MyVector& operator=(const MyVector& other)
    {
        if (this != &other) {
            delete[] data;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data = new T[capacity_];
            std::copy(other.data, other.data + size_, data);
        }
        return *this;
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

    void push_back(const T& value)
    {
        if (size_ == capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            T* new_data = new T[new_capacity];
            std::copy(data, data + size_, new_data);
            delete[] data;
            data = new_data;
            capacity_ = new_capacity;
        }
        data[size_++] = value;
    }

    T* begin()
    {
        return data;
    }

    T* end()
    {
        return data + size_;
    }

    const T* begin() const
    {
        return data;
    }

    const T* end() const
    {
        return data + size_;
    }

    void resize(size_t new_size)
    {
        if (new_size > capacity_) {
            T* new_data = new T[new_size];
            std::copy(data, data + size_, new_data);
            delete[] data;
            data = new_data;
            capacity_ = new_size;
        }
        size_ = new_size;
    }

    T* data_ptr()
    {
        return data;
    }
};

#endif // MYVECTOR_H