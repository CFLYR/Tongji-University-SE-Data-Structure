#include "PowerStimulation.h"
#include <iostream>

using namespace std;

int main()
{

    int generated = 0;
    bool quit = false;
    char op;
    ALGraph grapher;
    while (!quit) {
        cout << "==================================================" << endl;
        cout << "**\t\t�������ģ��ϵͳ\t\t**" << endl;
        cout << "==================================================" << endl;
        cout << "**\t\tA --- ������������\t\t**" << endl;
        cout << "**\t\tB --- ��ӵ����ı�\t\t**" << endl;
        cout << "**\t\tC --- �������ɷ���\t\t**" << endl;
        cout << "**\t\tD --- �˳�����\t\t\t**" << endl;
        cout << "**\t\t���ڵ�����������10^5\t\t**" << endl;
        cout << "==================================================" << endl;
        cout << "\n������ѡ��\n";
        cin >> op;
        switch (op) {
        case 'A':
            if (!generated) {
                grapher.CreatGraph();
                generated++;
            } else {
                cout << "����������\n";
            }
            break;
        case 'B':
            if (generated == 1) {
                grapher.AddEdges();
                generated++;
            } else {
                cout << "����δ����\n";
            }
            break;
        case 'C':
            if (generated == 2) {
                grapher.CreatMST();
            } else {
                cout << "����δ����\n";
            }
            break;
        case 'D':
            quit = true;
            break;
        default:
            cout << "�޴�ѡ�������\n";
            cin.clear();
            cin.ignore(MAX_SIZE, '\n');
            break;
        }
    }

    return 0;
}