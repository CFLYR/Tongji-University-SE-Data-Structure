#ifndef MYPRIORITYQUEUE_H
#define MYPRIORITYQUEUE_H

#include "MyVector.h"
#include <functional>

template <typename T, typename Container = MyVector<T>, typename Compare = std::less<typename Container::value_type>>
class MyPriorityQueue {
private:
    Container c;
    Compare comp;

    void heapify(size_t index)
    {
        size_t size = c.size();
        size_t largest = index;
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;

        if (left < size && comp(c[largest], c[left]))
            largest = left;

        if (right < size && comp(c[largest], c[right]))
            largest = right;

        if (largest != index) {
            std::swap(c[index], c[largest]);
            heapify(largest);
        }
    }

public:
    MyPriorityQueue()
        : c()
        , comp()
    {
    }

    void push(const T& value)
    {
        c.push_back(value);
        size_t index = c.size() - 1;
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (comp(c[parent], c[index])) {
                std::swap(c[parent], c[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void pop()
    {
        if (c.size() == 0)
            return;
        c[0] = c[c.size() - 1];
        c.pop_back();
        heapify(0);
    }

    T top() const
    {
        if (c.size() == 0)
            throw std::out_of_range("Priority queue is empty");
        return c[0];
    }

    size_t size() const
    {
        return c.size();
    }
};

#endif // MYPRIORITYQUEUE_H