#ifndef MYPRIORITYQUEUE_H
#define MYPRIORITYQUEUE_H
#include "MyVector.h"
#include <cstring>
#include <functional>

template <typename T, typename Container = MyVector<T>, typename Compare = std::less<typename Container::value_type>>
class MyPriorityQueue {
private:
    Container c;
    Compare comp;

    void heapify_up(size_t index)
    {
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

    void heapify_down(size_t index)
    {
        size_t size = c.size();
        while (true) {
            size_t left_child = 2 * index + 1;
            size_t right_child = 2 * index + 2;
            size_t largest = index;

            if (left_child < size && comp(c[largest], c[left_child])) {
                largest = left_child;
            }
            if (right_child < size && comp(c[largest], c[right_child])) {
                largest = right_child;
            }

            if (largest != index) {
                std::swap(c[index], c[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    MyPriorityQueue() = default;

    void push(const T& value)
    {
        c.push_back(value);
        heapify_up(c.size() - 1);
    }

    void pop()
    {
        if (!empty()) {
            c[0] = c.back();
            c.pop_back();
            if (!empty()) {
                heapify_down(0);
            }
        }
    }

    const T& top() const { return c[0]; }
    bool empty() const { return c.empty(); }
    size_t size() const { return c.size(); }
};

#endif // MYPRIORITYQUEUE_H
