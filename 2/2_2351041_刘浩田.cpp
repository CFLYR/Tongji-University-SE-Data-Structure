#include "LinkListIntersection.h" // ����ͷ�ļ�

using namespace std;

int main()
{
    // ��ʾ�û������һ�зǽ����������У���-1��β
    cout << "�������һ�зǽ����������У���-1��β" << endl;
    List<int> Link_1 = {}; // ������һ���������
    Link_1.Insert_multiple(); // ������Ԫ�ص���һ������
    cout << "������ĵ�һ�зǽ�����������Ϊ��" << endl;
    if (!Link_1.Length()) { // �������Ϊ��
        cout << "NULL" << endl; // ���NULL
    } else {
        Link_1.Print(); // ��ӡ����
        cout << endl;
    }
    cin.ignore(IGNORE_SIZE, '\n'); // �������뻺�����е��ַ�
    // ��ʾ�û�����ڶ��зǽ����������У���-1��β
    cout << "������ڶ��зǽ����������У���-1��β" << endl;
    List<int> Link_2 = {}; // �����ڶ����������
    Link_2.Insert_multiple(); // ������Ԫ�ص��ڶ�������
    cout << "������ĵڶ��зǽ�����������Ϊ��" << endl;
    if (!Link_2.Length()) { // �������Ϊ��
        cout << "NULL" << endl; // ���NULL
    } else {
        Link_2.Print(); // ��ӡ����
        cout << endl;
    }
    int pos = 1; // ��ʼ��λ�ñ���
    int check = 0; // ��ʼ��������
    List<int> Link_same = {}; // �����洢��ͬԪ�ص��������
    // ������һ������
    for (int i = 1; i <= Link_1.Length(); i++) {
        // �����ڶ�������
        for (int j = 1; j <= Link_2.Length(); j++) {
            // ������������Ԫ����ͬ
            if (Link_1.Truenum(i) == Link_2.Truenum(j)) {
                // �����ͬԪ�ز���Link_same��
                if (!Link_same.Findpos(Link_2.Truenum(j))) {
                    Link_same.Insert(Link_1.Truenum(i), pos); // ������ͬԪ�ص�Link_same
                    check++; // ���Ӽ�����
                    pos++; // ����λ�ü���
                }
            }
        }
    }
    // ����ԱȽ��
    cout << "�Ա������������£�" << endl;
    cout << "��ͬ����Ϊ��";
    if (!Link_same.Length()) { // ���û����ͬԪ��
        cout << "NULL" << endl; // ���NULL
    } else {
        Link_same.Print(); // ��ӡ��ͬԪ��
        cout << endl;
    }
    // �������˵��
    cout << "����˵��Ϊ��";
    if (!Link_1.Length() || !Link_2.Length()) { // �������һ������Ϊ��
        cout << "����һ������Ϊ�յ����" << endl;
    } else if (!Link_same.Length()) { // ���û����ͬԪ��
        cout << "����Ϊ�յ����" << endl;
    } else if (check == Link_1.Length() && check == Link_2.Length()) { // �������������ȫ�ཻ
        cout << "��ȫ�ཻ�����" << endl;
    } else if (check == Link_1.Length() || check == Link_2.Length()) { // �������һ��������ȫ���ڽ���
        cout << "����һ��������ȫ���ڽ��������" << endl;
    } else {
        cout << "һ�����" << endl; // һ�����
    }
#ifdef _WIN32
    system("pause"); // ��ͣϵͳ���ȴ��û�����
#elif __linux__
    cout << "���س�������..." << endl;
    cin.get(); // ��ͣϵͳ���ȴ��û�����
#endif
    return 0; // ����0
}