#pragma once
#define IGNORE_SIZE 2147483647

#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

template <class class_type>
class List; // ǰ������

template <class class_type>
class ListNode {
    friend class List<class_type>; // ������Ϊ����Ԫ��
private:
    class_type data;
    ListNode* link;

public:
    ListNode(class_type val)
        : data(val)
        , link(NULL)
    {
    } // ���캯����ʼ���ڵ�
};

template <class class_type>
class List {
public:
    // ���캯����ʼ��������ֵ
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
    { // ���������ͷ������ڴ�
        ListNode<class_type>* p = first;
        while (p != NULL) {
            ListNode<class_type>* temp = p;
            p = p->link;
            delete temp;
        }
        return;
    }

    void MakeEmpty()
    { // ɾȥ�����г���ͷ�����������������
        ListNode<class_type>* q;
        while (first->link != NULL) {
            q = first->link;
            first->link = q->link; // ����ͷ�����һ����������ժ��
            delete q; // �ͷ���
        }
        last = first;
        return;
    }

    ListNode<class_type>* Find(class_type value)
    { // �������д�ͷ����������ֵΪvalue�Ľ��
        ListNode<class_type>* p = first; // ���ָ��pָʾ��һ�����
        while (p != NULL && !(p->data == value)) {
            p = p->link;
        }
        return p; // p�������ɹ�ʱ�����ҵ��Ľ���ַ
    }

    int Findpos(class_type value)
    { // �������д�ͷ����������ֵΪvalue�Ľ��
        int count = 1;
        ListNode<class_type>* p = first; // ���ָ��pָʾ��һ�����
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
        ListNode<class_type>* p = first; // ���ָ��pָʾ��һ�����
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
        ListNode<class_type>* newNode = new ListNode<class_type>(x); // �����½ڵ�
        if (i == 1) { // ���뵽����ͷ��
            newNode->link = first;
            first = newNode;
            if (last == NULL) {
                last = newNode; // �������Ϊ�գ����½ڵ�Ҳ��β�ڵ�
            }
        } else {
            ListNode<class_type>* p = first;
            for (int k = 1; p != NULL && k < i - 1; k++) {
                p = p->link;
            }
            if (p == NULL) {
                cout << "��Ч�Ĳ���λ��!\n";
                delete newNode; // �ͷ��½ڵ��ڴ�
                return 0;
            } else {
                newNode->link = p->link;
                p->link = newNode;
                if (newNode->link == NULL) {
                    last = newNode; // ����½ڵ���β�ڵ�
                }
            }
        }
        return 1; // ����ɹ�
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
                    cout << "��������������ޣ�����������" << endl;
                    continue;
                } else if (getnum < 0 && getnum != -1) {
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "�����������������������" << endl;
                    continue;
                } else if (getnum < last && getnum != -1) {
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "�����˽������������������λ����������" << endl;
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
            cout << "��Ч��ɾ��λ��!\n";
            return 0;
        }

        ListNode<class_type>* p = first;
        if (i == 1) { // ɾ����һ�����
            first = first->link;
            if (first == NULL)
                last = NULL; // ��������գ�����last
        } else {
            for (int k = 1; p != NULL && k < i - 1; k++) {
                p = p->link;
            }
            if (p == NULL || p->link == NULL) {
                cout << "��Ч��ɾ��λ��!\n";
                return 0;
            }
            ListNode<class_type>* q = p->link;
            p->link = q->link;
            if (q == last)
                last = p; // ���ɾ������β��㣬����last
            delete q;
        }
        return 1; // ɾ���ɹ�
    }

    void Print() const
    { // ��ӡ����
        ListNode<class_type>* p = first;
        while (p != NULL) {
            cout << p->data << " "; // ��ӻ��з�
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
    { //������ĳ���
        ListNode<class_type>* p = first; //���ָ��pָʾ��һ�����
        int count = 0;
        if (p == NULL) {
            return 0;
        }
        while (p != NULL) { //��������
            p = p->link;
            count++;
        }
        return count;
    }

private:
    ListNode<class_type>*first, *last;
};