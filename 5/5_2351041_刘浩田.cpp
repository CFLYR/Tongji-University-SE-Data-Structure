#include "BankService.h"

int main()
{
    // ��ʾ�û�����˿������͹˿ͱ��
    cout << "������һ�������������е�һ����N��N<=1000��Ϊ�˿��������������Nλ�˿͵ı�š�" << endl;

    int sum;
    // ��������sum�Ƿ���0��1000֮��
    checkCin(sum, 0, 1000, 0);

    // ��ʼ����������A��B���������Ϊ1000
    Queue<int> Q_A(1000);
    Queue<int> Q_B(1000);

    // ���˿ͱ�ŷ��䵽����A��B
    for (int i = 0; i < sum; i++) {
        int id;
        checkCin(id, 0, 1000, 0);
        if (Q_A.CheckQuene(id)) {
            Q_A.EnQueue(id); // ������Ž���A����
        } else {
            Q_B.EnQueue(id); // ż����Ž���B����
        }
    }

    // ��ӡA���ڵĹ˿�
    cout << "A���ڹ˿�Ϊ��" << endl;
    Q_A.Print();

    // ��ӡB���ڵĹ˿�
    cout << "B���ڹ˿�Ϊ��" << endl;
    Q_B.Print();

    // ��ʾ�û����س�����ʼ����ҵ��
    cout << "����enter��ʼ����ҵ��" << endl;
    wait_for_enter();

    // �����������ʾ����˳��
    cout << "�����������������Ⱥ�˳��Ϊ��" << endl;
    Queue<int> Q_out(1000);
    int time_1;

    // ȷ�����������
    if (Q_A.Length() / 2 > Q_B.Length()) {
        time_1 = Q_B.Length();
    } else {
        time_1 = Q_A.Length() / 2;
    }

    // ���δ�A��B�����г��Ӳ������������
    for (int i = 0; i < time_1; i++) {
        Q_out.EnQueue(Q_A.GetFront());
        Q_A.DeQueue();
        Q_out.EnQueue(Q_A.GetFront());
        Q_A.DeQueue();
        Q_out.EnQueue(Q_B.GetFront());
        Q_B.DeQueue();
    }

    // ����ʣ���A���й˿�
    if (!Q_A.IsEmpty()) {
        Q_out.EnQueue(Q_A.GetFront());
        Q_A.DeQueue();
    }
    if (!Q_A.IsEmpty()) {
        for (; Q_A.Length();) {
            Q_out.EnQueue(Q_A.GetFront());
            Q_A.DeQueue();
        }
    } else if (!Q_B.IsEmpty()) {
        for (; Q_B.Length();) {
            Q_out.EnQueue(Q_B.GetFront());
            Q_B.DeQueue();
        }
    }
    // ��ӡ����˳��
    Q_out.Print();
#ifdef _WIN32
    system("pause"); // ��ͣϵͳ���ȴ��û�����
#else
    cout << "����enter���˳�����" << endl;
    wait_for_enter();
#endif
    return 0;
}