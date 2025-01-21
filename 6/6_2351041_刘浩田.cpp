#include "Family_tree.h"

int main()
{
    cout << "开始建立家谱，请输入祖先名字" << endl;
    MyString Ancestor;
    cin >> Ancestor;
    FamilyTree family(Ancestor);

    while (true) {
        cout << "\n==============================================================\n**                      家谱管理系统                        **\n==============================================================\n"
             << "**                   请选择要执行的操作:                    **\n"
             << "**                      A---完善家谱                        **\n**                      B---添加家庭成员                    **\n"
             << "**                      C---解散局部家庭子女                **\n**                      D---更改家庭成员姓名                **\n"
             << "**                      E---显示家谱树                      **\n**                      F---退出程序                        **\n"
             << "==============================================================\n";
        char choice;
        cout << "请选择要执行的操作选项：" << endl;
#ifdef _WIN32
        choice = _getch();
#else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        choice = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
        cout << choice << endl;
        if (choice == 'A') {
            MyString parent, child;
            cout << "请输入要建立家庭的人的姓名：";
            while (1) {
                cin >> parent;
                if (!family.findMember(parent)) {
                    cout << "未找到名为“" << parent << "”的成员" << endl;
                } else {
                    break;
                }
            }

            cout << "请输入" << parent << "要添加的儿女人数：";
            int count;
            while (1) {
                cin >> count;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(65532, '\n');
                    cout << "输入错误" << endl;
                } else if (count <= 0) {
                    cin.ignore(65532, '\n');
                    cout << "输入错误" << endl;
                } else {
                    cin.ignore(65532, '\n');
                    break;
                }
            }
            cout << "请输入要添加的子女名称" << endl;
            for (int i = 0; i < count; i++) {
                while (1) {
                    cin >> child;
                    if (family.findMember(child)) {
                        cout << "该成员" << child << "已存在\n";
                    } else {
                        family.addMember(parent, child);
                        break;
                    }
                }
            }
        } else if (choice == 'B') {
            MyString parent, child;
            cout << "请输入要添加的成员家庭的父母姓名：";
            while (1) {
                cin >> parent;
                if (!family.findMember(parent)) {
                    cout << "未找到名为“" << parent << "”的成员" << endl;
                } else {
                    break;
                }
            }
            cout << "请输入成员名称\n";
            cin >> child;
            if (family.findMember(child)) {
                cout << "该成员" << child << "已存在\n";
            } else {
                family.addMember(parent, child);
            }
        } else if (choice == 'C') {
            MyString name;
            cout << "请输入要解散的成员姓名：";
            cin >> name;
            if (!family.findMember(name)) {
                cout << "未找到名为“" << name << "”的成员\n"
                     << endl;
            } else if (!family.getChildren(name)) {
                cout << "该成员" << name << "无子女\n";
            } else {
                family.startRemove(name);
            }
        } else if (choice == 'D') {
            MyString name;
            cout << "请输入要修改的成员姓名：\n";
            cin >> name;
            if (!family.findMember(name)) {
                cout << "未找到名为“" << name << "”的成员\n"
                     << endl;
            } else {
                cout << "请输入想要该改成员修改为的名字：\n";
                family.changeName(name);
            }
        } else if (choice == 'E') {
            family.display();
        } else if (choice == 'F') {
            break;
        } else {
            cout << "无此选项,请重新输入" << endl;
        }
        cout << "\n按下回车继续\n";
        WaitforEnter();
    }

    return 0;
}