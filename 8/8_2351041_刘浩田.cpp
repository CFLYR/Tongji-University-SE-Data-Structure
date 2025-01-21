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
        cout << "**\t\t电网造价模拟系统\t\t**" << endl;
        cout << "==================================================" << endl;
        cout << "**\t\tA --- 创建电网顶点\t\t**" << endl;
        cout << "**\t\tB --- 添加电网的边\t\t**" << endl;
        cout << "**\t\tC --- 构建生成方案\t\t**" << endl;
        cout << "**\t\tD --- 退出程序\t\t\t**" << endl;
        cout << "**\t\t最大节点数量不超过10^5\t\t**" << endl;
        cout << "==================================================" << endl;
        cout << "\n请输入选项\n";
        cin >> op;
        switch (op) {
        case 'A':
            if (!generated) {
                grapher.CreatGraph();
                generated++;
            } else {
                cout << "电网已生成\n";
            }
            break;
        case 'B':
            if (generated == 1) {
                grapher.AddEdges();
                generated++;
            } else {
                cout << "电网未生成\n";
            }
            break;
        case 'C':
            if (generated == 2) {
                grapher.CreatMST();
            } else {
                cout << "电网未生成\n";
            }
            break;
        case 'D':
            quit = true;
            break;
        default:
            cout << "无此选项，请重输\n";
            cin.clear();
            cin.ignore(MAX_SIZE, '\n');
            break;
        }
    }

    return 0;
}