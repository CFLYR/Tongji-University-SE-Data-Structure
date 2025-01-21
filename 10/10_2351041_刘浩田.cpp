#include "Sort_Comparison.h"
int main()
{

    int random_numbers;
    cout << "��������Ҫ��������������,��С��1��2147483647\n";
    CheckCin(random_numbers, 1);
    MyVector<int> numbers_first(random_numbers);
    for (int i = 0; i < random_numbers; i++) {
        numbers_first[i] = rand();
    }
    while (1) {
        int choice;
        int compareCount = 0;
        cout << "��ѡ�������㷨: \n";
        printf("====================================================\n");
        printf("**                  �����㷨�Ƚ�                  **\n");
        printf("====================================================\n");
        printf("**                  1.ð������                    **\n");
        printf("**                  2.ѡ������                    **\n");
        printf("**                  3.ֱ�Ӳ�������                **\n");
        printf("**                  4.�۰��������                **\n");
        printf("**                  5.ϣ������                    **\n");
        printf("**                  6.��������                    **\n");
        printf("**                  7.������                      **\n");
        printf("**                  8.�鲢����                    **\n");
        printf("**                  9.��������                    **\n");
        printf("**                  0.�˳�����                    **\n");
        printf("====================================================\n");
        CheckCin(choice, 0, 9);
        auto start = chrono::high_resolution_clock::now();
        MyVector<int> numbers = numbers_first;
        switch (choice) {
        case 1:
            cout << "ð������ʼ,��ȴ����\n";
            BubbleSort(numbers, compareCount);
            break;
        case 2:
            cout << "ѡ������ʼ����ȴ����\n";
            SelectSort(numbers, compareCount);
            break;
        case 3:
            cout << "ֱ�Ӳ�������ʼ����ȴ����\n";
            StraightInsertSort(numbers, compareCount);
            break;
        case 4:
            cout << "�۰��������ʼ����ȴ����\n";
            BinaryInsertSort(numbers, compareCount);
            break;
        case 5:
            cout << "ϣ������ʼ����ȴ����\n";
            ShellSort(numbers, compareCount);
            break;
        case 6:
            cout << "��������ʼ����ȴ����\n";
            QuickSort(numbers, 0, numbers.size() - 1, compareCount);
            break;
        case 7:
            cout << "������ʼ����ȴ����\n";
            HeapSort(numbers, numbers.size(), compareCount);
            break;
        case 8:
            cout << "�鲢����ʼ����ȴ����\n";
            MergeSort(numbers, 0, numbers.size() - 1, compareCount);
            break;
        case 9:
            cout << "��������ʼ����ȴ����\n";
            RadixSort(numbers, compareCount);
            break;
        case 0:
            cout << "�����˳�\n";
            return 0;
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "�������\n";
        cout << "�Ƚϴ���: " << compareCount << endl;
        cout << "����ʱ��: " << elapsed.count() << "s\n";
    }
    return 0;
}