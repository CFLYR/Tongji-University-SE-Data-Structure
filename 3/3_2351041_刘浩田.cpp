#include "maze.h" // �����Թ���ص�ͷ�ļ�

int main()
{
    srand(static_cast<unsigned int>(time(nullptr))); // ʹ�õ�ǰʱ���������������
    int rows; // ����
    int cols; // ����
    cout << "������������������" << endl; // ��ʾ�û���������
    while (1) {
        cin >> rows; // ��ȡ�û����������
        if (cin.fail()) { // ��������Ƿ�ʧ��
            cin.clear(); // ��������־
            cin.ignore(IGNORE_SIZE, '\n'); // ���Դ�������
            cout << "�����������������" << endl; // ��ʾ�û���������
            continue; // ����ѭ��
        } else if (rows % 2 == 0) { // �������������Ƿ�Ϊż��
            cin.clear(); // ��������־
            cin.ignore(IGNORE_SIZE, '\n'); // ���Դ�������
            cout << "��֧��ż��������������" << endl; // ��ʾ�û���������
            continue; // ����ѭ��
        } else {
            cin.ignore(IGNORE_SIZE, '\n'); // ���Զ�������
            break; // �˳�ѭ��
        }
    }
    cout << "������������������" << endl; // ��ʾ�û���������
    while (1) {
        cin >> cols; // ��ȡ�û����������
        if (cin.fail()) { // ��������Ƿ�ʧ��
            cin.clear(); // ��������־
            cin.ignore(IGNORE_SIZE, '\n'); // ���Դ�������
            cout << "�����������������" << endl; // ��ʾ�û���������
            continue; // ����ѭ��
        } else if (cols % 2 == 0) { // �������������Ƿ�Ϊż��
            cin.clear(); // ��������־
            cin.ignore(IGNORE_SIZE, '\n'); // ���Դ�������
            cout << "��֧��ż��������������" << endl; // ��ʾ�û���������
            continue; // ����ѭ��
        }

        else {
            cin.ignore(IGNORE_SIZE, '\n'); // ���Զ�������
            break; // �˳�ѭ��
        }
    }
    rows = rows + 2; // ������������Ӧ�Թ��߽�
    cols = cols + 2; // ������������Ӧ�Թ��߽�
    int startRow = 1; // ��ʼ��
    int startCol = 1; // ��ʼ��
    int targetRow = rows - 2; // Ŀ����
    int targetCol = cols - 2; // Ŀ����

    Maze maze(rows, cols, startRow, startCol, targetRow, targetCol); // �����Թ�����

    cout << "��PRIM��ʽ�����Թ����£�" << endl; // ��ʾ�û��Թ����ɷ�ʽ
    maze.output(); // ������ɵ��Թ�
    cout << "��ENTER��ʼѰ·" << endl; // ��ʾ�û����س�����ʼѰ·
    wait_for_enter(); // �ȴ��û����س���
    cout << "·��Ϊ:" << endl; // ��ʾ�û���ʾ·��
    maze.FindWay(); // Ѱ���Թ�·��
    maze.output(); // �������·�����Թ�
    cout << "��ENTER��ʼ��ʾ����·�ߣ��ı���" << endl; // ��ʾ�û����س�����ʾ����·��
    wait_for_enter(); // �ȴ��û����س���
    cout << "·��Ϊ:" << endl; // ��ʾ�û���ʾ����·��
    maze.PrintStack(); // ��ӡ����·��

#ifdef _WIN32
    system("pause"); // ��ͣ���򣬵ȴ��û������������
#else
    cout << "�����������..." << endl;
    cin.get(); // ��ͣ���򣬵ȴ��û������������
#endif

    return 0; // ����0����ʾ������������
}