#pragma once
#include "MyString.h"
#include "MyVector.h"
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
#include <iostream>

using namespace std;

void printSpace(int layer, bool isLast)
{
    const int width = 4;
    for (int i = 0; i < layer; i++) {
        if (isLast && i == layer - 1) {
            cout << " ";
        } else {
            cout << "��";
        }
        for (int j = 0; j < width; j++) {
            cout << " ";
        }
    }
}

// �����Ա�ڵ�
class FamilyMember {
public:
    MyString name;
    MyVector<FamilyMember*> children;

    FamilyMember(const MyString& n)
        : name(n)
    {
    }
};

// ������
class FamilyTree {
private:
    FamilyMember* root;

    // �ݹ���ҳ�Ա
    FamilyMember* findMember(FamilyMember* current, const MyString& name)
    {
        if (current->name == name) {
            return current;
        }
        for (FamilyMember* child : current->children) {
            FamilyMember* found = findMember(child, name);
            if (found) {
                return found;
            }
        }
        return nullptr;
    }

    // �ݹ���ʾ����
    int displayTree(FamilyMember* current, int layer, bool isLast)
    {
        if (!current->children.empty()) {
            for (auto it = current->children.begin(); it != current->children.end(); ++it) {
                FamilyMember* ptr = *it;
                bool lastChild = (it == current->children.end() - 1);
                printSpace(layer, isLast);
                cout << "��" << endl;
                printSpace(layer, isLast);
                cout << "������"
                     << "  " << ptr->name << endl;
                displayTree(ptr, layer + 1, lastChild);
            }
        }

        return 0;
    }

public:
    FamilyTree(const MyString& rootName)
    {
        root = new FamilyMember(rootName);
    }

    // ��Ӽ����Ա
    void addMember(const MyString& parentName, const MyString& childName)
    {
        FamilyMember* parent = findMember(root, parentName);
        if (parent) {
            parent->children.push_back(new FamilyMember(childName));
            cout << childName << "�ɹ���Ϊ" << parentName << "����Ů�����" << endl;
        } else {
            cout << "δ�ҵ���Ϊ"
                    " << parentName << "
                    "����Ϊ��ĸ�ĳ�Ա"
                 << endl;
        }
    }

    // ��ʾ��������
    void display()
    {
        cout << root->name << endl;
        displayTree(root, 0, true);
    }

    void changeName(const MyString& name)
    {
        FamilyMember* current = findMember(root, name);
        MyString replacer;
        while (1) {
            cin >> replacer;
            if (replacer == name) {
                cout << "δ�޸ģ����������룡\n";
            } else if (findMember(replacer)) {
                cout << "�����Ը���Ϊ������Ա��\n";
            } else {
                break;
            }
        }
        current->name = replacer;
        return;
    }

    // ���ҳ�Ա
    bool findMember(const MyString& name)
    {
        return findMember(root, name) != nullptr;
    }

    void startRemove(const MyString& name)
    {
        FamilyMember* current = findMember(root, name);
        if (current) {
            cout << "���ڽ�ɢ " << name << " �ļ�ͥ..." << endl;
            while (!current->children.empty()) {
                FamilyMember* child = current->children.back();
                removeMember(child);
                current->children.pop_back();
                delete child;
            }
            cout << name << " �ļ�ͥ�Ѿ���ɢ" << endl;
        } else {
            cout << "δ�ҵ���Ϊ " << name << " �ĳ�Ա" << endl;
        }
    }

    void removeMember(FamilyMember* current)
    {
        if (!current)
            return;

        // ���ȵݹ�ɾ�������ӽڵ�
        while (!current->children.empty()) {
            FamilyMember* child = current->children.back();
            removeMember(child);
            current->children.pop_back();
            delete child;
        }
        // ��ǰ�ڵ�������ӽڵ��ѱ�ɾ����current->children ����Ϊ��
    }

    // ��ȡ��Ů
    int getChildren(const MyString& name)
    {
        FamilyMember* member = findMember(root, name);
        if (member) {
            if (member->children.empty()) {
                return 0;
            } else {
                return 1;
            }
        } else {
            return 0;
        }
    }
};

#ifdef _WIN32
void WaitforEnter()
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
#else
void WaitforEnter()
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