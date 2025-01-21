#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"

using namespace std;

// ������
int main()
{
    print_line(); // ��ӡ�ָ���
    cout << "�����뽨��������Ϣϵͳ��" << endl;
    print_line();
    cout << "�����뿼��������" << endl;
    print_line();
    int num;
    while (1) {
        cin >> num; // ���뿼������
        if (cin.fail()) { // ��������Ƿ�ʧ��
            cin.clear();
            cin.ignore(IGNORE_SIZE, '\n');
            cout << "�����������������" << endl;
            continue;
        } else if (num <= 0) { // ��������Ƿ�Ϊ����
            cin.ignore(IGNORE_SIZE, '\n');
            cout << "�����������������" << endl;
            continue;
        } else {
            cin.ignore(IGNORE_SIZE, '\n');
            break;
        }
    }
    print_line();
    cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
    print_line();
    stu_list all_list; // ����ѧ���б����
    all_list.input_students(num); // ���뿼����Ϣ
    print_line();
    cout << "ϵͳ��ϢΪ��" << endl;
    print_line();
    print_chart(); // ��ӡͼ��
    print_line();
    all_list.print_students(); // ��ӡ���п�����Ϣ
    print_line();
    int choice = 1;
    while (choice) { // ����ѭ��
        cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
        while (1) {
            cin >> choice; // �������ѡ��
            if (cin.fail()) { // ��������Ƿ�ʧ��
                cin.clear();
                cin.ignore(IGNORE_SIZE, '\n');
                cout << "�����������������" << endl;
                continue;
            } else if (choice < 0 || choice > 5) { // ���ѡ���Ƿ�����Ч��Χ
                cin.ignore(IGNORE_SIZE, '\n');
                cout << "�����������������" << endl;
                continue;
            } else {
                cin.ignore(IGNORE_SIZE, '\n');
                break;
            }
        }
        switch (choice) {
        case 0:
            break; // ȡ������
        case 1:
            cout << "��������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
            all_list.input_students(1); // �����¿���
            break;
        case 2:
            cout << "��������Ҫɾ���Ŀ����Ŀ���" << endl;
            int id_2;
            while (1) {
                cin >> id_2; // ����Ҫɾ���Ŀ������
                if (cin.fail()) { // ��������Ƿ�ʧ��
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "�����������������" << endl;
                    continue;
                } else if (!all_list.find_student(id_2)) { // ��鿼���Ƿ����
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "�����ڴ˿���������������" << endl;
                    continue;
                } else {
                    cin.ignore(IGNORE_SIZE, '\n');
                    break;
                }
            }
            id_2 = all_list.find_studentpos(id_2); // ���ҿ���λ��
            all_list.remove_student(id_2); // ɾ������
            break;
        case 3:
            cout << "��������Ҫ���ҵĿ����Ŀ���" << endl;
            int id_3;
            while (1) {
                cin >> id_3; // ����Ҫ���ҵĿ������
                if (cin.fail()) { // ��������Ƿ�ʧ��
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "�����������������" << endl;
                    continue;
                } else if (!all_list.find_studentpos(id_3)) { // ��鿼���Ƿ����
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "�����ڴ˿���������������" << endl;
                    continue;
                } else {
                    cin.ignore(IGNORE_SIZE, '\n');
                    break;
                }
            }
            print_line();
            cout << "������ҵĿ���Ϊ��" << endl;
            print_line();
            all_list.print_single_stu(id_3); // ��ӡ����������Ϣ
            print_line();
            break;
        case 4:
            cout << "��������Ҫ�޸ĵĿ����Ŀ���" << endl;
            int id_4;
            while (1) {
                cin >> id_4; // ����Ҫ�޸ĵĿ������
                if (cin.fail()) { // ��������Ƿ�ʧ��
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "�����������������" << endl;
                    continue;
                } else if (!all_list.find_studentpos(id_4)) { // ��鿼���Ƿ����
                    cin.clear();
                    cin.ignore(IGNORE_SIZE, '\n');
                    cout << "�����ڴ˿���������������" << endl;
                    continue;
                } else {
                    cin.ignore(IGNORE_SIZE, '\n');
                    break;
                }
            }
            all_list.remove_student(all_list.find_studentpos(id_4)); // ɾ������Ϣ
            cout << "��������Ҫ�޸ĵĿ������������Ա����估�������" << endl;
            all_list.input_students(1, id_4); // ��������Ϣ
            print_line();
            cout << "��ɹ�������Ϊ" << id_4 << "�Ŀ�����Ϣ�޸�Ϊ��" << endl;
            print_line();
            all_list.print_single_stu(id_4); // ��ӡ�޸ĺ����Ϣ
            print_line();
            break;
        case 5:
            print_line();
            cout << "��ʼͳ��......" << endl;
            print_line();
            cout << "��������Ϊ��" << endl;
            cout << all_list.find_studentnum() << endl; // ��ӡ��������
            print_line();
            cout << "�����Ա����Ϊ��" << endl;
            all_list.student_sex(); // �����Ա�
            print_line();
            cout << "����ƽ������Ϊ��" << endl;
            all_list.average_age(); // ����ƽ������
            print_line();
            cout << "��������������Ϊ��" << endl;
            MyJob job_count;
            all_list.summarize_jobs(job_count); // ���ܱ������
            job_count.print(); // ��ӡ�������ͳ��
            print_line();
            break;
        }
        cout << endl;
        cout << "������ɣ���" << endl;
        cout << endl;
        print_line();
        cout << "���в������ϵͳ��ϢΪ" << endl;
        print_line();
        print_chart(); // ��ӡ���º��ͼ��
        print_line();
        all_list.print_students(); // ��ӡ���º�Ŀ�����Ϣ
        print_line();
    }
    cout << "��ɲ������˳�ϵͳ......" << endl;
    print_line();
    return 0; // �������
}