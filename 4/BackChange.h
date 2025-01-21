#pragma once
#include <iostream>
#include <cassert>
#include <cstring>

// 定义栈的最大容量
const int kMaxSize = 100;


using namespace std;

// 模板类Stack：实现一个通用的栈数据结构
template <class T>
class Stack {
public:
    // 构造函数，默认大小为kMaxSize
    explicit Stack(int size = kMaxSize);

    // 将元素压入栈顶
    void Push(const T& item);

    // 弹出并返回栈顶元素
    T Pop();

    // 获取栈顶元素
    T GetTop();

    // 清空栈
    void MakeEmpty();

    // 检查栈是否为空
    bool IsEmpty() const;

    // 检查栈是否已满
    bool IsFull() const;

    // 获取当前栈顶索引
    int GetTopIndex() const;

private:
    int top_;         // 栈顶指针
    T* elements_;     // 存储元素的数组
    int max_size_;    // 栈的最大容量
};

// 构造函数实现
template <class T>
Stack<T>::Stack(int size) : top_(-1), max_size_(size) {
    // 分配内存给元素数组
    elements_ = new T[max_size_];
    // 断言确保内存分配成功
    assert(elements_ != nullptr);
}

// Push函数实现
template <class T>
void Stack<T>::Push(const T& item) {
    // 断言确保栈未满
    assert(!IsFull());
    // 将元素放入栈顶并增加栈顶指针
    elements_[++top_] = item;
}

// Pop函数实现
template <class T>
T Stack<T>::Pop() {
    // 断言确保栈非空
    assert(!IsEmpty());
    // 返回栈顶元素并减少栈顶指针
    return elements_[top_--];
}

// GetTop函数实现
template <class T>
T Stack<T>::GetTop() {
    // 断言确保栈非空
    assert(!IsEmpty());
    // 返回栈顶元素但不改变栈顶指针
    return elements_[top_];
}

// MakeEmpty函数实现
template <class T>
void Stack<T>::MakeEmpty() {
    // 将栈顶指针重置为-1，表示空栈
    top_ = -1;
}

// IsEmpty函数实现
template <class T>
bool Stack<T>::IsEmpty() const {
    // 当栈顶指针为-1时，栈为空
    return top_ == -1;
}

// IsFull函数实现
template <class T>
bool Stack<T>::IsFull() const {
    // 当栈顶指针等于最大容量减1时，栈已满
    return top_ == max_size_ - 1;
}

// GetTopIndex函数实现
template <class T>
int Stack<T>::GetTopIndex() const {
    // 返回当前栈顶指针
    return top_;
}

// 获取运算符优先级的函数
int GetOperatorPriority(char op) {
    // 乘除优先级为2
    if (op == '*' || op == '/') return 2;
    // 加减优先级为1
    if (op == '+' || op == '-') return 1;
    // 其他字符优先级为0
    return 0;
}

// 判断字符是否为运算符的函数
bool IsOperator(char c) {
    // 检查字符是否为加、减、乘、除之一
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 将中缀表达式转换为后缀表达式的函数
void InfixToPostfix(const char* infix, char* postfix) {
    Stack<char> op_stack;  // 用于存储运算符的栈
    int postfix_index = 0; // 后缀表达式的当前索引
    bool expect_operand = true;  // 标志，用于判断是否期望一个操作数

    // 遍历中缀表达式的每个字符
    for (int i = 0; infix[i] != '\0'; i++) {
        // 跳过空格
        if (infix[i] == ' ') {
            continue;
        }

        // 处理数字、负号和小数点
        if (isdigit(infix[i]) || (infix[i] == '-' && expect_operand) || infix[i] == '.') {
            // 如果是负号且期望操作数，则将负号加入后缀表达式
            if (infix[i] == '-' && expect_operand) {
                postfix[postfix_index++] = infix[i++];
            }
            // 将连续的数字和小数点添加到后缀表达式
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[postfix_index++] = infix[i++];
            }
            // 数字后添加空格作为分隔符
            postfix[postfix_index++] = ' ';
            i--; // 回退一个字符，因为for循环会再次i++
            expect_operand = false; // 不再期望操作数
        }
        // 处理左括号
        else if (infix[i] == '(') {
            op_stack.Push(infix[i]);
            expect_operand = true; // 左括号后期望操作数
        }
        // 处理右括号
        else if (infix[i] == ')') {
            // 将栈中运算符弹出并加入后缀表达式，直到遇到左括号
            while (!op_stack.IsEmpty() && op_stack.GetTop() != '(') {
                postfix[postfix_index++] = op_stack.Pop();
                postfix[postfix_index++] = ' ';
            }
            // 弹出左括号（如果存在）
            if (!op_stack.IsEmpty() && op_stack.GetTop() == '(') {
                op_stack.Pop();
            }
            expect_operand = false; // 右括号后不期望操作数
        }
        // 处理运算符
        else if (IsOperator(infix[i])) {
            // 忽略正号
            if (infix[i] == '+' && expect_operand) {
                continue;
            }
            // 将优先级更高或相等的运算符从栈中弹出并加入后缀表达式
            while (!op_stack.IsEmpty() && op_stack.GetTop() != '(' &&
                GetOperatorPriority(op_stack.GetTop()) >= GetOperatorPriority(infix[i])) {
                postfix[postfix_index++] = op_stack.Pop();
                postfix[postfix_index++] = ' ';
            }
            // 将当前运算符压入栈
            op_stack.Push(infix[i]);
            expect_operand = true; // 运算符后期望操作数
        }
    }

    // 将栈中剩余的运算符添加到后缀表达式
    while (!op_stack.IsEmpty()) {
        postfix[postfix_index++] = op_stack.Pop();
        postfix[postfix_index++] = ' ';
    }

    // 移除末尾多余的空格
    if (postfix_index > 0 && postfix[postfix_index - 1] == ' ') {
        postfix_index--;
    }
    // 添加字符串结束符
    postfix[postfix_index] = '\0';
}