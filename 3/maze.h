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

// �궨��
#define MEMORY_ALLOCATION_ERROR -1
#define INVALID_INDEX_ERROR -2
#define MAZE_BLANK 0
#define MAZE_WALL 1
#define MAZE_PATH 2
#define MAZE_BLOCK 3
#define IGNORE_SIZE 1000000

// ���巽��ö��
enum Direction { Up,
    Down,
    Left,
    Right,
    BLANK };

///////////////////////////////////////////////////
// �������
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

// ����ջģ����
template <class T>
class Stack {
public:
    Stack(int = IGNORE_SIZE); // ���캯��
    void Push(const T& item); // ��ջ
    T Pop(); // ��ջ
    T GetTop(); // ȡջ��Ԫ��
    void MakeEmpty(); // �ÿ�ջ
    int IsEmpty() const; // ��ջ�շ�
    int IsFull() const; // ��ջ����
    void Print() const; // ��ӡջ����
    int CheckTop(); // ���ջ������
private:
    int top; // ջ������ָ��
    T* elements; // ջ����
    int maxSize; // ջ�������
};

// ���캯��ʵ��
template <class T>
Stack<T>::Stack(int s)
    : top(-1)
    , maxSize(s)
{
    elements = new T[maxSize];
    assert(elements != 0); // ����
}

// ��ջ����ʵ��
template <class T>
void Stack<T>::Push(const T& item)
{
    assert(!IsFull()); // �Ⱦ���������
    elements[++top] = item; // ������Ԫ��
}

// ��ջ����ʵ��
template <class T>
T Stack<T>::Pop()
{
    assert(!IsEmpty()); // �Ⱦ���������
    return elements[top--]; // �˳�ջ��Ԫ��
}

// ��ȡջ��Ԫ��ʵ��
template <class T>
T Stack<T>::GetTop()
{
    if (IsEmpty()) {
        return 'N';
    }
    return elements[top]; // ȡ��ջ��Ԫ��
}

// �ÿ�ջʵ��
template <class T>
void Stack<T>::MakeEmpty()
{
    top = -1; // �ÿ�ջ
}

// ��ӡջ����ʵ��
template <class T>
void Stack<T>::Print() const
{
    if (IsEmpty()) {
        cout << "Stack is empty" << endl;
        return;
    }
    for (int i = 0; i <= top; i++) { // ��ȷ��ѭ������
        cout << "(" << elements[i].row << "," << elements[i].col << ")";
        if (i != top) {
            cout << "->";
        }
    }
    cout << endl;
}

// �ж�ջ��ʵ��
template <class T>
int Stack<T>::IsEmpty() const
{
    return top == -1; // ��ջ�շ�
}

// �ж�ջ��ʵ��
template <class T>
int Stack<T>::IsFull() const
{
    return top == maxSize - 1; // ��ջ����
}

// ���ջ������ʵ��
template <class T>
int Stack<T>::CheckTop()
{
    return top;
}

// �����Թ���
class Maze {
private:
    int** mazeMap; // �Թ���ͼ
    int rows; // ����
    int cols; // ����
    int startRow; // ��ʼ��
    int startCol; // ��ʼ��
    int targetRow; // Ŀ����
    int targetCol; // Ŀ����
    int currRow; // ��ǰ��
    int currCol; // ��ǰ��
    int mazePointCount; // �Թ������
    struct MazePoint {
        int row;
        int col;
        Direction direction;
    }; // �Թ���ṹ��
    MazePoint* mazePointList; // �Թ����б�

public:
    Stack<Point> Plist; // ��ջ
    int Stat(int Dircet1, int Dircet2); // ״̬���
    void pushList(const struct MazePoint& mazePoint); // �����б�
    void popList(int index); // �����б�
    void findAdjacentWalls(void); // ��������ǽ��
    void generateMaze(void); // �����Թ�
    bool isValid(int row, int col); // �����Ч��
    Maze(int _rows, int _cols, int _startRow, int _startCol, int _targetRow, int _targetCol); // ���캯��
    ~Maze(); // ��������
    void output(void); // ����Թ�
    int FindWay(int i, int j, Direction direction); // Ѱ��·��
    void PrintStack(); // ��ӡջ����
};

// �����б�ʵ��
void Maze::pushList(const struct MazePoint& mazePoint)
{
    mazePointList[mazePointCount++] = mazePoint;
}

// �����б�ʵ��
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

// ��������ǽ��ʵ��
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

// �����Թ�ʵ��
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

// �����Ч��ʵ��
bool Maze::isValid(int row, int col)
{
    return (row >= 0 && row < rows && col >= 0 && col < cols);
}

// ���캯��ʵ��
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

// ��������ʵ��
Maze::~Maze()
{
    for (int i = 0; i < rows; i++)
        delete[] mazeMap[i];
    delete[] mazeMap;
    delete[] mazePointList;
}

// ����Թ�ʵ��
void Maze::output(void)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == startRow && j == startCol - 1) {
                cout << "��";
            } else if (i == targetRow && j == targetCol + 1)
                cout << "��";
            else if (mazeMap[i][j] == MAZE_BLANK)
                cout << "  ";
            else if (mazeMap[i][j] == MAZE_WALL)
                cout << "��";
            else if (mazeMap[i][j] == MAZE_PATH)
                cout << "��";
            else
                cout << "XX";
        }
        cout << endl;
    }
    return;
}

// ״̬���ʵ��
int Maze::Stat(int Direct1, int Direct2)
{
    if (mazeMap[Direct1][Direct2] == MAZE_BLANK) {
        return 1;
    } else {
        return 0;
    }
}

// Ѱ��·��ʵ��
int Maze::FindWay(int i = 1, int j = 1, Direction d = BLANK)
{
    Point p = { i, j };
    Plist.Push(p);

    if (i == targetRow && j == targetCol) {
        mazeMap[i][j] = MAZE_PATH;
        return 1; // �ҵ�·��
    }

    // ���Ϊ�ѷ���
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
    return 0; // δ�ҵ�·��
}

// ��ӡջ����ʵ��
void Maze::PrintStack()
{
    Plist.Print();
}

#if defined(_WIN32) || defined(_WIN64)
// �ȴ��س�ʵ�� (Windows)
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
// �ȴ��س�ʵ�� (Linux)
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