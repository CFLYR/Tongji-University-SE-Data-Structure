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

// ����һ��ģ�������
template <class T>
class Queue {
public:
    // ���캯������ʼ�����д�С��ָ��
    Queue(int size = MAX_SIZE)
        : maxSize(size)
        , front(0)
        , rear(0)
    {
        elements = new T[maxSize];
        assert(elements != nullptr);
    }

    // �����������ͷ��ڴ�
    ~Queue() { delete[] elements; }

    // ��Ӳ���
    void EnQueue(const T& item)
    {
        assert(!IsFull());
        elements[rear] = item;
        rear = (rear + 1) % maxSize;
    }

    // ���Ӳ���
    T DeQueue()
    {
        assert(!IsEmpty());
        T frontItem = elements[front];
        front = (front + 1) % maxSize;
        return frontItem;
    }

    // ��ȡ����Ԫ��
    T GetFront()
    {
        assert(!IsEmpty());
        return elements[front];
    }

    // ��ն���
    void MakeEmpty()
    {
        front = 0;
        rear = 0;
    }

    // �ж϶����Ƿ�Ϊ��
    bool IsEmpty() const { return front == rear; }

    // �ж϶����Ƿ�����
    bool IsFull() const { return (rear + 1) % maxSize == front; }

    // ��ȡ���г���
    int Length() const
    {
        return (rear - front + maxSize) % maxSize;
    }

    // ���˿ͱ����ż�ԣ���������A����B����
    int CheckQuene(const T& item)
    {
        if (item % 2 == 0) {
            return 0; // ż��
        } else {
            return 1; // ����
        }
    }

    // ��ӡ�����е�����Ԫ��
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
    int front, rear; // ��ͷ�Ͷ�βָ��
    T* elements; // �洢����Ԫ�ص�����
    int maxSize; // ���е��������
};

// ��������Ƿ�Ϸ�
void checkCin(int& value, const int lower_limit = 0, const int higher_limit = numeric_limits<int>::max(), const int erase_puff_area = 1)
{
    while (1) {
        cin >> value;
        if (cin.fail()) {
            // ����ʧЧ����ʾ��������
            cout << "����Ƿ���������\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else if (value < lower_limit || value > higher_limit) {
            // ���볬����Χ����ʾ��������
            cout << "���볬�ޣ�������\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else {
            if (erase_puff_area) {
                // ���Զ�������
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        }
    }
}

// �ȴ��û����»س���
void wait_for_enter()
{
#ifdef _WIN32
    int chopace;
    while (1) {
        chopace = _getch();
        if (chopace == '\r') {
            break; // ��⵽�س������˳�ѭ��
        } else {
            continue; // �����ȴ�
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
            break; // ��⵽�س������˳�ѭ��
        } else {
            continue; // �����ȴ�
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    return;
}