#include "CriticalActivity.h"
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
    int point_node;
    cout << "请输入任务交接点数量\n";
    CheckCin(point_node, 1, 100, 0);
    int task_num;
    cout << "请输入任务数量\n";
    CheckCin(task_num, point_node, 100);
    Graph task_graph { point_node, task_num };
    task_graph.CreateGraph(point_node, task_num, task_num);
    MyVector<PathInfo> result;
    Graph result_graph = task_graph;
    int project_duration = result_graph.CriticalPath(result_graph, result);
    cout << "任务完成时间为：\n";
    cout << project_duration << endl;
    cout << "对应路径为：\n";
    for (const auto& path : result) {
        cout << path.start << " -> " << path.end << endl;
    }
#ifdef _WIN32
    system("pause");
#elif defined(__linux__) || defined(__APPLE__)
    cout << "按回车键继续..." << endl;
    cin.get();
#endif
    return 0;
}