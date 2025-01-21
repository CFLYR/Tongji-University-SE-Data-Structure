#include "MyPriorityQueue.h"
#include "MyVector.h"
#include <iostream>

using namespace std;

int minCost(MyVector<int>& lengths)
{
    // ʹ���Զ������ȶ��У���С�ѣ����洢ľͷ����
    MyPriorityQueue<int, MyVector<int>, greater<int>> pq;
    for (int length : lengths) {
        pq.push(length);
    }

    int totalCost = 0;

    // �������л��г���һ��ľͷʱ�������и�
    while (pq.size() > 1) {
        // ȡ����̵�����ľͷ
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();

        // �����и�ɱ�������ľͷ�Żض���
        int cost = first + second;
        totalCost += cost;
        pq.push(cost);
    }

    return totalCost;
}

int main()
{

    int n;
    cout << "������ľͷ��������\n";
    while (1) {
        cin >> n;
        if (cin.fail() || n < 1 || n > 1e4) {
            cin.clear();
            cin.ignore(65532, '\n');
            cout << "�����������������\n";
        } else {
            break;
        }
    }

    MyVector<int> lengths;
    cout << "�������ľ�鳤��\n";
    for (int i = 0; i < n; ++i) {
        int length;
        cin >> length;
        lengths.push_back(length);
    }

    int result = minCost(lengths);
    cout << "��С����Ϊ��" << result << endl;
#ifdef _WIN32
    system("pause");
#elif defined(__linux__) || defined(__APPLE__)
    cout << "���س�������..." << endl;
    cin.get();
#endif
    return 0;
}
