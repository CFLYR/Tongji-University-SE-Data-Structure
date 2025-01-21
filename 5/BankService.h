#pragma once
#include <cassert>
#include <iostream>
#include <limits>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#define MAX_SIZE 1000000

using namespace std;

// 定义一个模板队列类
template <class T>
class Queue {
public:
    // 构造函数，初始化队列大小和指针
    Queue(int size = MAX_SIZE)
        : maxSize(size)
        , front(0)
        , rear(0)
    {
        elements = new T[maxSize];
        assert(elements != nullptr);
    }

    // 析构函数，释放内存
    ~Queue() { delete[] elements; }

    // 入队操作
    void EnQueue(const T& item)
    {
        assert(!IsFull());
        elements[rear] = item;
        rear = (rear + 1) % maxSize;
    }

    // 出队操作
    T DeQueue()
    {
        assert(!IsEmpty());
        T frontItem = elements[front];
        front = (front + 1) % maxSize;
        return frontItem;
    }

    // 获取队首元素
    T GetFront()
    {
        assert(!IsEmpty());
        return elements[front];
    }

    // 清空队列
    void MakeEmpty()
    {
        front = 0;
        rear = 0;
    }

    // 判断队列是否为空
    bool IsEmpty() const { return front == rear; }

    // 判断队列是否已满
    bool IsFull() const { return (rear + 1) % maxSize == front; }

    // 获取队列长度
    int Length() const
    {
        return (rear - front + maxSize) % maxSize;
    }

    // 检查顾客编号奇偶性，决定进入A还是B队列
    int CheckQuene(const T& item)
    {
        if (item % 2 == 0) {
            return 0; // 偶数
        } else {
            return 1; // 奇数
        }
    }

    // 打印队列中的所有元素
    void Print()
    {
        for (int frontier = front; frontier < rear; frontier++) {
            cout << elements[frontier];
            if (frontier != rear - 1) {
                cout << " ";
            }
        }
        cout << endl;
        return;
    }

private:
    int front, rear; // 队头和队尾指针
    T* elements; // 存储队列元素的数组
    int maxSize; // 队列的最大容量
};

// 检查输入是否合法
void checkCin(int& value, const int lower_limit = 0, const int higher_limit = numeric_limits<int>::max(), const int erase_puff_area = 1)
{
    while (1) {
        cin >> value;
        if (cin.fail()) {
            // 输入失效，提示重新输入
            cout << "输入非法，请重输\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else if (value < lower_limit || value > higher_limit) {
            // 输入超出范围，提示重新输入
            cout << "输入超限，请重输\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else {
            if (erase_puff_area) {
                // 忽略多余输入
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        }
    }
}

// 等待用户按下回车键
void wait_for_enter()
{
#ifdef _WIN32
    int chopace;
    while (1) {
        chopace = _getch();
        if (chopace == '\r') {
            break; // 检测到回车键，退出循环
        } else {
            continue; // 继续等待
        }
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int chopace;
    while (1) {
        chopace = getchar();
        if (chopace == '\n') {
            break; // 检测到回车键，退出循环
        } else {
            continue; // 继续等待
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    return;
}