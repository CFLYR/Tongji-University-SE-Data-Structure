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
            cout << "│";
        }
        for (int j = 0; j < width; j++) {
            cout << " ";
        }
    }
}

// 家族成员节点
class FamilyMember {
public:
    MyString name;
    MyVector<FamilyMember*> children;

    FamilyMember(const MyString& n)
        : name(n)
    {
    }
};

// 家谱树
class FamilyTree {
private:
    FamilyMember* root;

    // 递归查找成员
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

    // 递归显示家谱
    int displayTree(FamilyMember* current, int layer, bool isLast)
    {
        if (!current->children.empty()) {
            for (auto it = current->children.begin(); it != current->children.end(); ++it) {
                FamilyMember* ptr = *it;
                bool lastChild = (it == current->children.end() - 1);
                printSpace(layer, isLast);
                cout << "│" << endl;
                printSpace(layer, isLast);
                cout << "└──"
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

    // 添加家族成员
    void addMember(const MyString& parentName, const MyString& childName)
    {
        FamilyMember* parent = findMember(root, parentName);
        if (parent) {
            parent->children.push_back(new FamilyMember(childName));
            cout << childName << "成功作为" << parentName << "的子女被添加" << endl;
        } else {
            cout << "未找到名为"
                    " << parentName << "
                    "的作为父母的成员"
                 << endl;
        }
    }

    // 显示整个家谱
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
                cout << "未修改，请重新输入！\n";
            } else if (findMember(replacer)) {
                cout << "不可以更改为重名成员！\n";
            } else {
                break;
            }
        }
        current->name = replacer;
        return;
    }

    // 查找成员
    bool findMember(const MyString& name)
    {
        return findMember(root, name) != nullptr;
    }

    void startRemove(const MyString& name)
    {
        FamilyMember* current = findMember(root, name);
        if (current) {
            cout << "正在解散 " << name << " 的家庭..." << endl;
            while (!current->children.empty()) {
                FamilyMember* child = current->children.back();
                removeMember(child);
                current->children.pop_back();
                delete child;
            }
            cout << name << " 的家庭已经解散" << endl;
        } else {
            cout << "未找到名为 " << name << " 的成员" << endl;
        }
    }

    void removeMember(FamilyMember* current)
    {
        if (!current)
            return;

        // 首先递归删除所有子节点
        while (!current->children.empty()) {
            FamilyMember* child = current->children.back();
            removeMember(child);
            current->children.pop_back();
            delete child;
        }
        // 当前节点的所有子节点已被删除，current->children 现在为空
    }

    // 获取子女
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