#include "Family_tree.h"

int main()
{
    cout << "��ʼ�������ף���������������" << endl;
    MyString Ancestor;
    cin >> Ancestor;
    FamilyTree family(Ancestor);

    while (true) {
        cout << "\n==============================================================\n**                      ���׹���ϵͳ                        **\n==============================================================\n"
             << "**                   ��ѡ��Ҫִ�еĲ���:                    **\n"
             << "**                      A---���Ƽ���                        **\n**                      B---��Ӽ�ͥ��Ա                    **\n"
             << "**                      C---��ɢ�ֲ���ͥ��Ů                **\n**                      D---���ļ�ͥ��Ա����                **\n"
             << "**                      E---��ʾ������                      **\n**                      F---�˳�����                        **\n"
             << "==============================================================\n";
        char choice;
        cout << "��ѡ��Ҫִ�еĲ���ѡ�" << endl;
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
            cout << "������Ҫ������ͥ���˵�������";
            while (1) {
                cin >> parent;
                if (!family.findMember(parent)) {
                    cout << "δ�ҵ���Ϊ��" << parent << "���ĳ�Ա" << endl;
                } else {
                    break;
                }
            }

            cout << "������" << parent << "Ҫ��ӵĶ�Ů������";
            int count;
            while (1) {
                cin >> count;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(65532, '\n');
                    cout << "�������" << endl;
                } else if (count <= 0) {
                    cin.ignore(65532, '\n');
                    cout << "�������" << endl;
                } else {
                    cin.ignore(65532, '\n');
                    break;
                }
            }
            cout << "������Ҫ��ӵ���Ů����" << endl;
            for (int i = 0; i < count; i++) {
                while (1) {
                    cin >> child;
                    if (family.findMember(child)) {
                        cout << "�ó�Ա" << child << "�Ѵ���\n";
                    } else {
                        family.addMember(parent, child);
                        break;
                    }
                }
            }
        } else if (choice == 'B') {
            MyString parent, child;
            cout << "������Ҫ��ӵĳ�Ա��ͥ�ĸ�ĸ������";
            while (1) {
                cin >> parent;
                if (!family.findMember(parent)) {
                    cout << "δ�ҵ���Ϊ��" << parent << "���ĳ�Ա" << endl;
                } else {
                    break;
                }
            }
            cout << "�������Ա����\n";
            cin >> child;
            if (family.findMember(child)) {
                cout << "�ó�Ա" << child << "�Ѵ���\n";
            } else {
                family.addMember(parent, child);
            }
        } else if (choice == 'C') {
            MyString name;
            cout << "������Ҫ��ɢ�ĳ�Ա������";
            cin >> name;
            if (!family.findMember(name)) {
                cout << "δ�ҵ���Ϊ��" << name << "���ĳ�Ա\n"
                     << endl;
            } else if (!family.getChildren(name)) {
                cout << "�ó�Ա" << name << "����Ů\n";
            } else {
                family.startRemove(name);
            }
        } else if (choice == 'D') {
            MyString name;
            cout << "������Ҫ�޸ĵĳ�Ա������\n";
            cin >> name;
            if (!family.findMember(name)) {
                cout << "δ�ҵ���Ϊ��" << name << "���ĳ�Ա\n"
                     << endl;
            } else {
                cout << "��������Ҫ�øĳ�Ա�޸�Ϊ�����֣�\n";
                family.changeName(name);
            }
        } else if (choice == 'E') {
            family.display();
        } else if (choice == 'F') {
            break;
        } else {
            cout << "�޴�ѡ��,����������" << endl;
        }
        cout << "\n���»س�����\n";
        WaitforEnter();
    }

    return 0;
}