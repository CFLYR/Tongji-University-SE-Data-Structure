#pragma once
#include <assert.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#elif defined(__linux__)
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

// 宏定义
#define MEMORY_ALLOCATION_ERROR -1
#define INVALID_INDEX_ERROR -2
#define MAZE_BLANK 0
#define MAZE_WALL 1
#define MAZE_PATH 2
#define MAZE_BLOCK 3
#define IGNORE_SIZE 1000000

// 定义方向枚举
enum Direction { Up,
    Down,
    Left,
    Right,
    BLANK };

///////////////////////////////////////////////////
// 定义点类
class Point {
public:
    int row;
    int col;
    Point()
        : row(0)
        , col(0)
    {
    }
    Point(int r, int c)
    {
        row = r;
        col = c;
    }
};

// 定义栈模板类
template <class T>
class Stack {
public:
    Stack(int = IGNORE_SIZE); // 构造函数
    void Push(const T& item); // 进栈
    T Pop(); // 出栈
    T GetTop(); // 取栈顶元素
    void MakeEmpty(); // 置空栈
    int IsEmpty() const; // 判栈空否
    int IsFull() const; // 判栈满否
    void Print() const; // 打印栈内容
    int CheckTop(); // 检查栈顶索引
private:
    int top; // 栈顶数组指针
    T* elements; // 栈数组
    int maxSize; // 栈最大容量
};

// 构造函数实现
template <class T>
Stack<T>::Stack(int s)
    : top(-1)
    , maxSize(s)
{
    elements = new T[maxSize];
    assert(elements != 0); // 断言
}

// 进栈操作实现
template <class T>
void Stack<T>::Push(const T& item)
{
    assert(!IsFull()); // 先决条件断言
    elements[++top] = item; // 加入新元素
}

// 出栈操作实现
template <class T>
T Stack<T>::Pop()
{
    assert(!IsEmpty()); // 先决条件断言
    return elements[top--]; // 退出栈顶元素
}

// 获取栈顶元素实现
template <class T>
T Stack<T>::GetTop()
{
    if (IsEmpty()) {
        return 'N';
    }
    return elements[top]; // 取出栈顶元素
}

// 置空栈实现
template <class T>
void Stack<T>::MakeEmpty()
{
    top = -1; // 置空栈
}

// 打印栈内容实现
template <class T>
void Stack<T>::Print() const
{
    if (IsEmpty()) {
        cout << "Stack is empty" << endl;
        return;
    }
    for (int i = 0; i <= top; i++) { // 正确的循环条件
        cout << "(" << elements[i].row << "," << elements[i].col << ")";
        if (i != top) {
            cout << "->";
        }
    }
    cout << endl;
}

// 判断栈空实现
template <class T>
int Stack<T>::IsEmpty() const
{
    return top == -1; // 判栈空否
}

// 判断栈满实现
template <class T>
int Stack<T>::IsFull() const
{
    return top == maxSize - 1; // 判栈满否
}

// 检查栈顶索引实现
template <class T>
int Stack<T>::CheckTop()
{
    return top;
}

// 定义迷宫类
class Maze {
private:
    int** mazeMap; // 迷宫地图
    int rows; // 行数
    int cols; // 列数
    int startRow; // 起始行
    int startCol; // 起始列
    int targetRow; // 目标行
    int targetCol; // 目标列
    int currRow; // 当前行
    int currCol; // 当前列
    int mazePointCount; // 迷宫点计数
    struct MazePoint {
        int row;
        int col;
        Direction direction;
    }; // 迷宫点结构体
    MazePoint* mazePointList; // 迷宫点列表

public:
    Stack<Point> Plist; // 点栈
    int Stat(int Dircet1, int Dircet2); // 状态检查
    void pushList(const struct MazePoint& mazePoint); // 推入列表
    void popList(int index); // 弹出列表
    void findAdjacentWalls(void); // 查找相邻墙壁
    void generateMaze(void); // 生成迷宫
    bool isValid(int row, int col); // 检查有效性
    Maze(int _rows, int _cols, int _startRow, int _startCol, int _targetRow, int _targetCol); // 构造函数
    ~Maze(); // 析构函数
    void output(void); // 输出迷宫
    int FindWay(int i, int j, Direction direction); // 寻找路径
    void PrintStack(); // 打印栈内容
};

// 推入列表实现
void Maze::pushList(const struct MazePoint& mazePoint)
{
    mazePointList[mazePointCount++] = mazePoint;
}

// 弹出列表实现
void Maze::popList(int index)
{
    if (index < 0 || index >= mazePointCount) {
        cerr << "Error: Invalid index for erase operation." << endl;
        exit(INVALID_INDEX_ERROR);
    }
    for (int i = index; i < mazePointCount - 1; i++)
        mazePointList[i] = mazePointList[i + 1];
    mazePointCount--;
}

// 查找相邻墙壁实现
void Maze::findAdjacentWalls(void)
{
    if (currRow < rows - 1 && mazeMap[currRow + 1][currCol] == MAZE_WALL)
        pushList({ currRow + 1, currCol, Down });
    if (currCol < cols - 1 && mazeMap[currRow][currCol + 1] == MAZE_WALL)
        pushList({ currRow, currCol + 1, Right });
    if (currRow > 0 && mazeMap[currRow - 1][currCol] == MAZE_WALL)
        pushList({ currRow - 1, currCol, Up });
    if (currCol > 0 && mazeMap[currRow][currCol - 1] == MAZE_WALL)
        pushList({ currRow, currCol - 1, Left });
}

// 生成迷宫实现
void Maze::generateMaze(void)
{
    findAdjacentWalls();
    while (mazePointCount) {
        int index = rand() % mazePointCount;
        MazePoint currPoint = mazePointList[index];
        currRow = currPoint.row;
        currCol = currPoint.col;
        if (currPoint.direction == Up)
            currRow--;
        else if (currPoint.direction == Down)
            currRow++;
        else if (currPoint.direction == Left)
            currCol--;
        else if (currPoint.direction == Right)
            currCol++;
        if (isValid(currRow, currCol) && mazeMap[currRow][currCol] == MAZE_WALL) {
            mazeMap[currPoint.row][currPoint.col] = mazeMap[currRow][currCol] = MAZE_BLANK;
            findAdjacentWalls();
        }
        popList(index);
    }
}

// 检查有效性实现
bool Maze::isValid(int row, int col)
{
    return (row >= 0 && row < rows && col >= 0 && col < cols);
}

// 构造函数实现
Maze::Maze(int _rows, int _cols, int _startRow, int _startCol, int _targetRow, int _targetCol)
{
    rows = _rows;
    cols = _cols;
    startRow = _startRow;
    startCol = _startCol;
    targetRow = _targetRow;
    targetCol = _targetCol;
    currRow = startRow;
    currCol = startCol;
    mazeMap = new int*[rows];
    for (int i = 0; i < rows; i++) {
        mazeMap[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            mazeMap[i][j] = MAZE_WALL;
    mazeMap[currRow][currCol] = MAZE_BLANK;
    mazePointCount = 0;
    mazePointList = new MazePoint[rows * cols];
    generateMaze();
}

// 析构函数实现
Maze::~Maze()
{
    for (int i = 0; i < rows; i++)
        delete[] mazeMap[i];
    delete[] mazeMap;
    delete[] mazePointList;
}

// 输出迷宫实现
void Maze::output(void)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == startRow && j == startCol - 1) {
                cout << "○";
            } else if (i == targetRow && j == targetCol + 1)
                cout << "○";
            else if (mazeMap[i][j] == MAZE_BLANK)
                cout << "  ";
            else if (mazeMap[i][j] == MAZE_WALL)
                cout << "■";
            else if (mazeMap[i][j] == MAZE_PATH)
                cout << "◇";
            else
                cout << "XX";
        }
        cout << endl;
    }
    return;
}

// 状态检查实现
int Maze::Stat(int Direct1, int Direct2)
{
    if (mazeMap[Direct1][Direct2] == MAZE_BLANK) {
        return 1;
    } else {
        return 0;
    }
}

// 寻找路径实现
int Maze::FindWay(int i = 1, int j = 1, Direction d = BLANK)
{
    Point p = { i, j };
    Plist.Push(p);

    if (i == targetRow && j == targetCol) {
        mazeMap[i][j] = MAZE_PATH;
        return 1; // 找到路径
    }

    // 标记为已访问
    mazeMap[i][j] = MAZE_PATH;

    if (Stat(i + 1, j) && d != Up) {
        if (FindWay(i + 1, j, Down)) {
            return 1;
        }
    }

    if (Stat(i - 1, j) && d != Down) {
        if (FindWay(i - 1, j, Up)) {
            return 1;
        }
    }

    if (Stat(i, j + 1) && d != Left) {
        if (FindWay(i, j + 1, Right)) {
            return 1;
        }
    }

    if (Stat(i, j - 1) && d != Right) {
        if (FindWay(i, j - 1, Left)) {
            return 1;
        }
    }

    mazeMap[i][j] = MAZE_BLANK;
    Plist.Pop();
    return 0; // 未找到路径
}

// 打印栈内容实现
void Maze::PrintStack()
{
    Plist.Print();
}

#if defined(_WIN32) || defined(_WIN64)
// 等待回车实现 (Windows)
void wait_for_enter()
{
    int chopace;
    while (1) {
        chopace = _getch();
        if (chopace == '\r') {
            break;
        } else {
            continue;
        }
    }
    return;
}
#elif defined(__linux__)
// 等待回车实现 (Linux)
void wait_for_enter()
{
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int chopace;
    while (1) {
        chopace = getchar();
        if (chopace == '\n') {
            break;
        } else {
            continue;
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return;
}
#endif