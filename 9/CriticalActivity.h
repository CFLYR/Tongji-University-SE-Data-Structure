#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef CRITICALACTIVITY
#define CRITICALACTIVITY

#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

// 定义一个函数，用于检查用户输入的整数是否在指定的范围内
void CheckCin(int& value, const int lower_limit = 0, const int higher_limit = 10000, const int erase_puff_area = 1)
{
    while (1) {
        cin >> value;
        if (cin.fail()) {
            cout << "输入错误，请重输\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else if (value < lower_limit || value > higher_limit) {
            cout << "输入错误，请重输\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else {
            if (erase_puff_area) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        }
    }
}
// MyVector class
template <typename T>
class MyVector {
private:
    T* data;
    int size;
    int capacity;

public:
    MyVector()
        : data(nullptr)
        , size(0)
        , capacity(0)
    {
    }

    MyVector(int n)
        : data(new T[n])
        , size(n)
        , capacity(n)
    {
        for (int i = 0; i < n; i++) {
            data[i] = T();
        }
    }

    ~MyVector()
    {
        delete[] data;
    }

    void push_back(const T& value)
    {
        if (size == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            T* newData = new T[newCapacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[size++] = value;
    }

    T& operator[](int index)
    {
        return data[index];
    }

    const T& operator[](int index) const
    {
        return data[index];
    }

    int getSize() const
    {
        return size;
    }

    void resize(int newSize)
    {
        if (newSize > capacity) {
            T* newData = new T[newSize];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            for (int i = size; i < newSize; i++) {
                newData[i] = T();
            }
            delete[] data;
            data = newData;
            capacity = newSize;
        }
        size = newSize;
    }

    // 添加begin()和end()方法
    T* begin() { return data; }
    T* end() { return data + size; }
    const T* begin() const { return data; }
    const T* end() const { return data + size; }
};

// MyString class and MyStack class remain unchanged
// ...

#endif // CRITICALACTIVITY

// MyString class
class MyString {
private:
    char* data;
    int length;

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

    ~MyString()
    {
        delete[] data;
    }

    const char* c_str() const
    {
        return data;
    }

    int size() const
    {
        return length;
    }
};

// MyStack class
template <typename T>
class MyStack {
private:
    MyVector<T> data;

public:
    void push(const T& value)
    {
        data.push_back(value);
    }

    T top()
    {
        if (data.getSize() == 0) {
            throw std::out_of_range("Stack is empty");
        }
        return data[data.getSize() - 1];
    }

    void pop()
    {
        if (data.getSize() == 0) {
            throw std::out_of_range("Stack is empty");
        }
        data.resize(data.getSize() - 1);
    }

    bool empty() const
    {
        return data.getSize() == 0;
    }
};

// 定义一个结构体PathInfo，用于表示一条活动的起始和结束节点
struct PathInfo {
    int start;
    int end;
    PathInfo()
        : start(0)
        , end(0)
    {
    } // 添加默认构造函数
    PathInfo(int s, int e)
        : start(s)
        , end(e) {};
};

// 定义一个类型别名VertexType，用于表示顶点的数据类型
typedef int VertexType;

// 定义一个类Edges，用于表示一条边的信息
class Edges {
public:
    int from;
    int to;
    int weight;
    Edges()
        : from(0)
        , to(0)
        , weight(0)
    {
    }
};

// 定义一个结构体Arcnode，用于表示一条边在邻接表中的信息
struct Arcnode {
    int adjvex;
    Edges Weight;
    Arcnode* nextarc;
    Arcnode()
        : adjvex(-1)
        , nextarc(nullptr)
    {
    }
};

// 定义一个结构体Vnode，用于表示顶点的信息
struct Vnode {
    VertexType data;
    int indegree;
    Arcnode* firstarc;
    Vnode()
        : indegree(0)
        , firstarc(nullptr)
    {
    }
};

// 定义一个类Graph，用于表示一个有向图
struct Graph {
    int vexnum;
    int arcnum;
    MyVector<Vnode> vertices;
    Graph(int v, int a)
        : vexnum(v)
        , arcnum(a)
    {
    }
    // 创建一个有向图，并根据用户输入的信息构建边
    void CreateGraph(const int vexnum, const int arcnum, const int task_num)
    {
        vertices.resize(vexnum);
        for (int i = 0; i < vexnum; i++) {
            vertices[i].data = 1 + i;
        }
        for (int i = 0; i < arcnum; i++) {
            int from, to, weight;
            // 提示用户输入边的信息
            cout << "请输入第" << i + 1 << "条边的起点、终点和权重：";
            CheckCin(from, 1, task_num, 0);
            CheckCin(to, from, task_num, 0);
            CheckCin(weight);
            Arcnode* newNode = new Arcnode;
            newNode->adjvex = to;
            newNode->Weight.from = from;
            newNode->Weight.to = to;
            newNode->Weight.weight = weight;
            newNode->nextarc = vertices[from - 1].firstarc; // 将新节点插入邻接表
            vertices[from - 1].firstarc = newNode;
            vertices[to - 1].indegree++; // 更新目标顶点的入度
        }
    }

    // 计算项目的关键路径，并返回关键路径的起始和终止节点
    int CriticalPath(Graph& graph, MyVector<PathInfo>& result)
    {
        int n = graph.vexnum;
        MyVector<int> ve(n);
        MyVector<int> vl(n);
        for (int i = 0; i < n; i++) {
            vl[i] = numeric_limits<int>::max();
        }
        MyStack<int> S;

        // 拓扑排序，计算ve
        for (int i = 0; i < n; i++) {
            if (graph.vertices[i].indegree == 0) {
                S.push(i);
            }
        }

        while (!S.empty()) {
            int v = S.top();
            S.pop();
            for (Arcnode* p = graph.vertices[v].firstarc; p; p = p->nextarc) {
                int k = p->adjvex - 1;
                if (--graph.vertices[k].indegree == 0) {
                    S.push(k);
                }
                if (ve[v] + p->Weight.weight > ve[k]) {
                    ve[k] = ve[v] + p->Weight.weight;
                }
            }
        }

        // 计算vl
        int max_ve = ve[0];
        for (int i = 1; i < n; i++) {
            if (ve[i] > max_ve) {
                max_ve = ve[i];
            }
        }
        for (int i = 0; i < n; i++) {
            vl[i] = max_ve;
        }

        for (int i = n - 1; i >= 0; i--) {
            for (Arcnode* p = graph.vertices[i].firstarc; p; p = p->nextarc) {
                int k = p->adjvex - 1;
                if (vl[k] - p->Weight.weight < vl[i]) {
                    vl[i] = vl[k] - p->Weight.weight;
                }
            }
        }

        // 计算关键活动
        for (int i = 0; i < n; i++) {
            for (Arcnode* p = graph.vertices[i].firstarc; p; p = p->nextarc) {
                int k = p->adjvex - 1;
                int ee = ve[i];
                int el = vl[k] - p->Weight.weight;
                if (ee == el) {
                    result.push_back(PathInfo(i + 1, k + 1));
                }
            }
        }

        return max_ve;
    }
};