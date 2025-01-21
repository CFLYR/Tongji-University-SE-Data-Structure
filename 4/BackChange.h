#pragma once
#include <iostream>
#include <cassert>
#include <cstring>

// ����ջ���������
const int kMaxSize = 100;


using namespace std;

// ģ����Stack��ʵ��һ��ͨ�õ�ջ���ݽṹ
template <class T>
class Stack {
public:
    // ���캯����Ĭ�ϴ�СΪkMaxSize
    explicit Stack(int size = kMaxSize);

    // ��Ԫ��ѹ��ջ��
    void Push(const T& item);

    // ����������ջ��Ԫ��
    T Pop();

    // ��ȡջ��Ԫ��
    T GetTop();

    // ���ջ
    void MakeEmpty();

    // ���ջ�Ƿ�Ϊ��
    bool IsEmpty() const;

    // ���ջ�Ƿ�����
    bool IsFull() const;

    // ��ȡ��ǰջ������
    int GetTopIndex() const;

private:
    int top_;         // ջ��ָ��
    T* elements_;     // �洢Ԫ�ص�����
    int max_size_;    // ջ���������
};

// ���캯��ʵ��
template <class T>
Stack<T>::Stack(int size) : top_(-1), max_size_(size) {
    // �����ڴ��Ԫ������
    elements_ = new T[max_size_];
    // ����ȷ���ڴ����ɹ�
    assert(elements_ != nullptr);
}

// Push����ʵ��
template <class T>
void Stack<T>::Push(const T& item) {
    // ����ȷ��ջδ��
    assert(!IsFull());
    // ��Ԫ�ط���ջ��������ջ��ָ��
    elements_[++top_] = item;
}

// Pop����ʵ��
template <class T>
T Stack<T>::Pop() {
    // ����ȷ��ջ�ǿ�
    assert(!IsEmpty());
    // ����ջ��Ԫ�ز�����ջ��ָ��
    return elements_[top_--];
}

// GetTop����ʵ��
template <class T>
T Stack<T>::GetTop() {
    // ����ȷ��ջ�ǿ�
    assert(!IsEmpty());
    // ����ջ��Ԫ�ص����ı�ջ��ָ��
    return elements_[top_];
}

// MakeEmpty����ʵ��
template <class T>
void Stack<T>::MakeEmpty() {
    // ��ջ��ָ������Ϊ-1����ʾ��ջ
    top_ = -1;
}

// IsEmpty����ʵ��
template <class T>
bool Stack<T>::IsEmpty() const {
    // ��ջ��ָ��Ϊ-1ʱ��ջΪ��
    return top_ == -1;
}

// IsFull����ʵ��
template <class T>
bool Stack<T>::IsFull() const {
    // ��ջ��ָ��������������1ʱ��ջ����
    return top_ == max_size_ - 1;
}

// GetTopIndex����ʵ��
template <class T>
int Stack<T>::GetTopIndex() const {
    // ���ص�ǰջ��ָ��
    return top_;
}

// ��ȡ��������ȼ��ĺ���
int GetOperatorPriority(char op) {
    // �˳����ȼ�Ϊ2
    if (op == '*' || op == '/') return 2;
    // �Ӽ����ȼ�Ϊ1
    if (op == '+' || op == '-') return 1;
    // �����ַ����ȼ�Ϊ0
    return 0;
}

// �ж��ַ��Ƿ�Ϊ������ĺ���
bool IsOperator(char c) {
    // ����ַ��Ƿ�Ϊ�ӡ������ˡ���֮һ
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// ����׺���ʽת��Ϊ��׺���ʽ�ĺ���
void InfixToPostfix(const char* infix, char* postfix) {
    Stack<char> op_stack;  // ���ڴ洢�������ջ
    int postfix_index = 0; // ��׺���ʽ�ĵ�ǰ����
    bool expect_operand = true;  // ��־�������ж��Ƿ�����һ��������

    // ������׺���ʽ��ÿ���ַ�
    for (int i = 0; infix[i] != '\0'; i++) {
        // �����ո�
        if (infix[i] == ' ') {
            continue;
        }

        // �������֡����ź�С����
        if (isdigit(infix[i]) || (infix[i] == '-' && expect_operand) || infix[i] == '.') {
            // ����Ǹ������������������򽫸��ż����׺���ʽ
            if (infix[i] == '-' && expect_operand) {
                postfix[postfix_index++] = infix[i++];
            }
            // �����������ֺ�С������ӵ���׺���ʽ
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[postfix_index++] = infix[i++];
            }
            // ���ֺ���ӿո���Ϊ�ָ���
            postfix[postfix_index++] = ' ';
            i--; // ����һ���ַ�����Ϊforѭ�����ٴ�i++
            expect_operand = false; // ��������������
        }
        // ����������
        else if (infix[i] == '(') {
            op_stack.Push(infix[i]);
            expect_operand = true; // �����ź�����������
        }
        // ����������
        else if (infix[i] == ')') {
            // ��ջ������������������׺���ʽ��ֱ������������
            while (!op_stack.IsEmpty() && op_stack.GetTop() != '(') {
                postfix[postfix_index++] = op_stack.Pop();
                postfix[postfix_index++] = ' ';
            }
            // ���������ţ�������ڣ�
            if (!op_stack.IsEmpty() && op_stack.GetTop() == '(') {
                op_stack.Pop();
            }
            expect_operand = false; // �����ź�����������
        }
        // ���������
        else if (IsOperator(infix[i])) {
            // ��������
            if (infix[i] == '+' && expect_operand) {
                continue;
            }
            // �����ȼ����߻���ȵ��������ջ�е����������׺���ʽ
            while (!op_stack.IsEmpty() && op_stack.GetTop() != '(' &&
                GetOperatorPriority(op_stack.GetTop()) >= GetOperatorPriority(infix[i])) {
                postfix[postfix_index++] = op_stack.Pop();
                postfix[postfix_index++] = ' ';
            }
            // ����ǰ�����ѹ��ջ
            op_stack.Push(infix[i]);
            expect_operand = true; // �����������������
        }
    }

    // ��ջ��ʣ����������ӵ���׺���ʽ
    while (!op_stack.IsEmpty()) {
        postfix[postfix_index++] = op_stack.Pop();
        postfix[postfix_index++] = ' ';
    }

    // �Ƴ�ĩβ����Ŀո�
    if (postfix_index > 0 && postfix[postfix_index - 1] == ' ') {
        postfix_index--;
    }
    // ����ַ���������
    postfix[postfix_index] = '\0';
}