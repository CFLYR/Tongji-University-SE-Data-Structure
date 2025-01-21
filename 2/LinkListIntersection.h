#pragma once
#define IGNORE_SIZE 2147483647

#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

template <class class_type>
class List; // 前置声明

template <class class_type>
class ListNode {
    friend class List<class_type>; // 链表类为其友元类
private:
    class_type data;
    ListNode* link;

public:
    ListNode(class_type val)
        : data(val)
        , link(NULL)
    {
    } // 构造函数初始化节点
};

template <class class_type>
class List {
public:
    // 构造函数初始化链表并赋值
    List(initializer_list<class_type> values)
        : first(NULL)
        , last(NULL)
    {
        for (class_type val : values) {
            ListNode<class_type>* newNode = new ListNode<class_type>(val);
            if (first == NULL) {
                first = last = newNode;
            } else {
                last->link = newNode;
                last = newNode;
            }
        }
        return;
    }

    ~List()
    { // 析构函数释放链表内存
        ListNode<class_type>* p = first;
        while (p != NULL) {
            ListNode<class_type>* temp = p;
            p = p->link;
            delete temp;
        }
        return;
    }

    void MakeEmpty()
    { // 删去链表中除表头结点外的所有其他结点
        ListNode<class_type>* q;
        while (first->link != NULL) {
            q = first->link;
            first->link = q->link; // 将表头结点后第一个结点从链中摘下
            delete q; // 释放它
        }
        last = first;
        return;
    }

    ListNode<class_type>* Find(class_type value)
    { // 在链表中从头搜索其数据值为value的结点
        ListNode<class_type>* p = first; // 检测指针p指示第一个结点
        while (p != NULL && !(p->data == value)) {
            p = p->link;
        }
        return p; // p在搜索成功时返回找到的结点地址
    }

    int Findpos(class_type value)
    { // 在链表中从头搜索其数据值为value的结点
        int count = 1;
        ListNode<class_type>* p = first; // 检测指针p指示第一个结点
        while (p != NULL && !(p->data == value)) {
            p = p->link;
            count++;
        }
        if (p == NULL) {
            return 0;
        }
        return count;
    }

    int Truenum(class_type value)
    {
        int count = 1;
        ListNode<class_type>* p = first; // 检测指针p指示第一个结点
        while (p != NULL && count < value) {
            p = p->link;
            count++;
        }
        if (p == NULL) {
            return 0;
        }
        return p->data;
    }

    int Insert(const class_type x, const int i)
    {
        ListNode<class_type>* newNode = new ListNode<class_type>(x); // 创建新节点
        if (i == 1) { // 插入到链表头部
            newNode->link = first;
            first = newNode;
            if (last == NULL) {
                last = newNode; // 如果链表为空，则新节点也是尾节点
            }
        } else {
            ListNode<class_type>* p = first;
            for (int k = 1; p != NULL && k < i - 1; k++) {
                p = p->link;
            }
            if (p == NULL) {
                cout << "无效的插入位置!\n";
                delete newNode; // 释放新节点内存
                return 0;
            } else {
                newNode->link = p->link;
                p->link = newNode;
                if (newNode->link == NULL) {
                    last = newNode; // 如果新节点是尾节点
                }
            }
        }
        return 1; // 插入成功
    }

    void Insert_multiple()
    {
        int last = 0;
        for (int k = 1;; k++) {
            int getnum;
            while (1) {
                cin >> getnum;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "输入非正整数或超限，请重新输入" << endl;
                    continue;
                } else if (getnum < 0 && getnum != -1) {
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "输入非正整数，请重新输入" << endl;
                    continue;
                } else if (getnum < last && getnum != -1) {
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "输入了降序链表，请在输入错误位置重新输入" << endl;
                    continue;
                } else {
                    break;
                }
            }
            if (getnum == -1) {
                break;
            }
            last = getnum;
            Insert(getnum, k);
        }
    }

    int Remove(int i)
    {
        if (i < 1 || first == NULL) {
            cout << "无效的删除位置!\n";
            return 0;
        }

        ListNode<class_type>* p = first;
        if (i == 1) { // 删除第一个结点
            first = first->link;
            if (first == NULL)
                last = NULL; // 如果链表变空，更新last
        } else {
            for (int k = 1; p != NULL && k < i - 1; k++) {
                p = p->link;
            }
            if (p == NULL || p->link == NULL) {
                cout << "无效的删除位置!\n";
                return 0;
            }
            ListNode<class_type>* q = p->link;
            p->link = q->link;
            if (q == last)
                last = p; // 如果删除的是尾结点，更新last
            delete q;
        }
        return 1; // 删除成功
    }

    void Print() const
    { // 打印链表
        ListNode<class_type>* p = first;
        while (p != NULL) {
            cout << p->data << " "; // 添加换行符
            p = p->link;
        }
        return;
    }

    void single_Print(ListNode<class_type>* i)
    {
        cout << i->data << endl;
        return;
    }

    int Length() const
    { //求单链表的长度
        ListNode<class_type>* p = first; //检测指针p指示第一个结点
        int count = 0;
        if (p == NULL) {
            return 0;
        }
        while (p != NULL) { //逐个结点检测
            p = p->link;
            count++;
        }
        return count;
    }

private:
    ListNode<class_type>*first, *last;
};