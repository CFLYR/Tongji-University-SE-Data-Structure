#include "MyPriorityQueue.h"
#include "MyString.h"
#include "MyVector.h"
#include <iostream>

const int MAX_SIZE = 100000;

using namespace std;

// 道路结构体，包含起点、终点和长度
struct Road {
    MyString first;
    MyString second;
    int length;
    Road()
        : first("")
        , second("")
        , length(0)
    {
    }
    Road(MyString f, MyString s, int l)
        : first(f)
        , second(s)
        , length(l)
    {
    }
};

// 弧节点结构体，包含邻接顶点索引、下一条弧和第二个节点名称
typedef struct ArcNode {
    int adjvex;
    struct ArcNode* nextarc;
    MyString sec_name;
    ArcNode()
        : adjvex(0)
        , nextarc(nullptr)
        , sec_name("")
    {
    }
} ArcNode;

// 顶点节点结构体，包含顶点名称和第一条弧
typedef struct VNode {
    MyString Name;
    ArcNode* firstarc;
    VNode()
        : Name("")
        , firstarc(nullptr)
    {
    }
} VNode;

// 邻接表图类
class ALGraph {
private:
    MyVector<VNode> vertices; // 顶点数组
    int vexnum, arcnum; // 顶点数和弧数

public:
    ALGraph()
        : vexnum(0)
        , arcnum(0)
    {
    }

    // 搜索最小的邻接顶点索引，并返回其名称
    int SearchMost(ArcNode* firstarc, MyString& second)
    {
        int smallest = MAX_SIZE + 1;
        ArcNode* newNode = new ArcNode();
        while (firstarc->nextarc != nullptr) {
            if (firstarc->adjvex < smallest) {
                smallest = firstarc->adjvex;
                second = firstarc->sec_name;
            }
            firstarc = firstarc->nextarc;
        }
        return smallest;
    }

    // 搜索顶点名称，返回其索引
    unsigned int SearchVex(const MyString Name)
    {
        for (unsigned int i = 0; i < vertices.size(); i++) {
            if (Name == vertices[i].Name) {
                return i + 1;
            }
        }
        return 0;
    }

    // 创建图
    void CreatGraph()
    {
        int num;
        cout << "请输入节点数\n";
        while (1) {
            cin >> num;
            if (cin.fail()) {
                cout << "输入错误，请重输" << endl;
                cin.clear();
                cin.ignore(MAX_SIZE, '\n');
            } else if (num < 1 || num > MAX_SIZE) {
                cout << "输入错误，请重输" << endl;
                cin.clear();
                cin.ignore(MAX_SIZE, '\n');
            } else {
                break;
            }
        }
        vexnum = num;
        cout << "请依次输入各节点名称\n";
        for (int i = 0; i < num; i++) {
            VNode Alpha;
            vertices.push_back(Alpha);
            MyString avl_name;
            cin >> avl_name;
            if (!SearchVex(avl_name)) {
                vertices[i].Name = avl_name;
            } else {
                cout << "输入错误，请重输\n";
                i--;
                continue;
            }
        }
        cout << "创建完成\n";
    }

    // 添加边
    void AddEdges()
    {
        MyVector<VNode> edge_editer = vertices;
        for (unsigned int i = 0; i < vertices.size(); i++) {
            for (unsigned int j = i + 1; j < vertices.size(); j++) {
                int length;
                cout << "请输入从" << vertices[i].Name << "到" << vertices[j].Name << "的路径长度\n";
                while (1) {
                    cin >> length;
                    if (cin.fail()) {
                        cout << "输入错误，请重输" << endl;
                        cin.clear();
                        cin.ignore(MAX_SIZE, '\n');
                    } else if (length < 1 || length > MAX_SIZE) {
                        cout << "输入错误，请重输" << endl;
                        cin.clear();
                        cin.ignore(MAX_SIZE, '\n');
                    } else {
                        break;
                    }
                }

                // 添加从i到j的边
                ArcNode* newNode1 = new ArcNode();
                newNode1->adjvex = length;
                newNode1->sec_name = vertices[j].Name;
                newNode1->nextarc = vertices[i].firstarc;
                vertices[i].firstarc = newNode1;

                // 添加从j到i的边
                ArcNode* newNode2 = new ArcNode();
                newNode2->adjvex = length;
                newNode2->sec_name = vertices[i].Name;
                newNode2->nextarc = vertices[j].firstarc;
                vertices[j].firstarc = newNode2;

                arcnum += 2;
            }
        }
    }

    // 创建最小生成树
    void CreatMST()
    {
        MyString startName;
        cout << "请输入开始建立电网的节点名称\n";
        while (1) {
            cin >> startName;
            if (SearchVex(startName)) {
                break;
            } else {
                cout << "无此节点，请重输\n";
            }
        }

        MyVector<bool> visited;
        for (int i = 0; i < vexnum; ++i) {
            visited.push_back(false);
        }
        MyVector<Road> mst;
        MyPriorityQueue<Road, MyVector<Road>, CompareRoad> pq;

        int startIndex = SearchVex(startName) - 1;
        visited[startIndex] = true;

        addEdgesToPQ(startIndex, pq, visited);

        while (!pq.empty() && mst.size() < size_t(vexnum - 1)) {
            Road minRoad = pq.top();
            pq.pop();

            int secondIndex = SearchVex(minRoad.second) - 1;
            if (!visited[secondIndex]) {
                visited[secondIndex] = true;
                mst.push_back(minRoad);

                addEdgesToPQ(secondIndex, pq, visited);
            }
        }
        cout << "电网建立结果为：\n";
        for (size_t i = 0; i < mst.size(); ++i) {
            const Road& road = mst[i];
            cout << road.first << " - " << road.second << ": " << road.length << endl;
        }
    }

    // 比较道路长度的仿函数
    struct CompareRoad {
        bool operator()(const Road& r1, const Road& r2)
        {
            return r1.length > r2.length;
        }
    };

    // 将节点的边添加到优先队列中
    void addEdgesToPQ(int nodeIndex, MyPriorityQueue<Road, MyVector<Road>, CompareRoad>& pq, const MyVector<bool>& visited)
    {
        ArcNode* arc = vertices[nodeIndex].firstarc;
        while (arc != nullptr) {
            int adjIndex = SearchVex(arc->sec_name) - 1;
            if (!visited[adjIndex]) {
                pq.push(Road(vertices[nodeIndex].Name, arc->sec_name, arc->adjvex));
            }
            arc = arc->nextarc;
        }
    }
};