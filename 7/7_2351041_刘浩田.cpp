#include "MyPriorityQueue.h"
#include "MyVector.h"
#include <iostream>

using namespace std;

int minCost(MyVector<int>& lengths)
{
    // 使用自定义优先队列（最小堆）来存储木头长度
    MyPriorityQueue<int, MyVector<int>, greater<int>> pq;
    for (int length : lengths) {
        pq.push(length);
    }

    int totalCost = 0;

    // 当队列中还有超过一块木头时，继续切割
    while (pq.size() > 1) {
        // 取出最短的两块木头
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();

        // 计算切割成本并将新木头放回队列
        int cost = first + second;
        totalCost += cost;
        pq.push(cost);
    }

    return totalCost;
}

int main()
{

    int n;
    cout << "请输入木头的数量：\n";
    while (1) {
        cin >> n;
        if (cin.fail() || n < 1 || n > 1e4) {
            cin.clear();
            cin.ignore(65532, '\n');
            cout << "输入错误，请重新输入\n";
        } else {
            break;
        }
    }

    MyVector<int> lengths;
    cout << "请输入各木块长度\n";
    for (int i = 0; i < n; ++i) {
        int length;
        cin >> length;
        lengths.push_back(length);
    }

    int result = minCost(lengths);
    cout << "最小花费为：" << result << endl;
#ifdef _WIN32
    system("pause");
#elif defined(__linux__) || defined(__APPLE__)
    cout << "按回车键继续..." << endl;
    cin.get();
#endif
    return 0;
}
