#include "MyPriorityQueue.h"
#include "MyString.h"
#include "MyVector.h"
#include <iostream>

const int MAX_SIZE = 100000;

using namespace std;

// ��·�ṹ�壬������㡢�յ�ͳ���
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

// ���ڵ�ṹ�壬�����ڽӶ�����������һ�����͵ڶ����ڵ�����
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

// ����ڵ�ṹ�壬�����������ƺ͵�һ����
typedef struct VNode {
    MyString Name;
    ArcNode* firstarc;
    VNode()
        : Name("")
        , firstarc(nullptr)
    {
    }
} VNode;

// �ڽӱ�ͼ��
class ALGraph {
private:
    MyVector<VNode> vertices; // ��������
    int vexnum, arcnum; // �������ͻ���

public:
    ALGraph()
        : vexnum(0)
        , arcnum(0)
    {
    }

    // ������С���ڽӶ���������������������
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

    // �����������ƣ�����������
    unsigned int SearchVex(const MyString Name)
    {
        for (unsigned int i = 0; i < vertices.size(); i++) {
            if (Name == vertices[i].Name) {
                return i + 1;
            }
        }
        return 0;
    }

    // ����ͼ
    void CreatGraph()
    {
        int num;
        cout << "������ڵ���\n";
        while (1) {
            cin >> num;
            if (cin.fail()) {
                cout << "�������������" << endl;
                cin.clear();
                cin.ignore(MAX_SIZE, '\n');
            } else if (num < 1 || num > MAX_SIZE) {
                cout << "�������������" << endl;
                cin.clear();
                cin.ignore(MAX_SIZE, '\n');
            } else {
                break;
            }
        }
        vexnum = num;
        cout << "������������ڵ�����\n";
        for (int i = 0; i < num; i++) {
            VNode Alpha;
            vertices.push_back(Alpha);
            MyString avl_name;
            cin >> avl_name;
            if (!SearchVex(avl_name)) {
                vertices[i].Name = avl_name;
            } else {
                cout << "�������������\n";
                i--;
                continue;
            }
        }
        cout << "�������\n";
    }

    // ��ӱ�
    void AddEdges()
    {
        MyVector<VNode> edge_editer = vertices;
        for (unsigned int i = 0; i < vertices.size(); i++) {
            for (unsigned int j = i + 1; j < vertices.size(); j++) {
                int length;
                cout << "�������" << vertices[i].Name << "��" << vertices[j].Name << "��·������\n";
                while (1) {
                    cin >> length;
                    if (cin.fail()) {
                        cout << "�������������" << endl;
                        cin.clear();
                        cin.ignore(MAX_SIZE, '\n');
                    } else if (length < 1 || length > MAX_SIZE) {
                        cout << "�������������" << endl;
                        cin.clear();
                        cin.ignore(MAX_SIZE, '\n');
                    } else {
                        break;
                    }
                }

                // ��Ӵ�i��j�ı�
                ArcNode* newNode1 = new ArcNode();
                newNode1->adjvex = length;
                newNode1->sec_name = vertices[j].Name;
                newNode1->nextarc = vertices[i].firstarc;
                vertices[i].firstarc = newNode1;

                // ��Ӵ�j��i�ı�
                ArcNode* newNode2 = new ArcNode();
                newNode2->adjvex = length;
                newNode2->sec_name = vertices[i].Name;
                newNode2->nextarc = vertices[j].firstarc;
                vertices[j].firstarc = newNode2;

                arcnum += 2;
            }
        }
    }

    // ������С������
    void CreatMST()
    {
        MyString startName;
        cout << "�����뿪ʼ���������Ľڵ�����\n";
        while (1) {
            cin >> startName;
            if (SearchVex(startName)) {
                break;
            } else {
                cout << "�޴˽ڵ㣬������\n";
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
        cout << "�����������Ϊ��\n";
        for (size_t i = 0; i < mst.size(); ++i) {
            const Road& road = mst[i];
            cout << road.first << " - " << road.second << ": " << road.length << endl;
        }
    }

    // �Ƚϵ�·���ȵķº���
    struct CompareRoad {
        bool operator()(const Road& r1, const Road& r2)
        {
            return r1.length > r2.length;
        }
    };

    // ���ڵ�ı���ӵ����ȶ�����
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