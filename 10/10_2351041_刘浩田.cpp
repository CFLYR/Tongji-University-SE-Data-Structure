#include "Sort_Comparison.h"
int main()
{

    int random_numbers;
    cout << "请输入需要排序的随机数数量,大小从1到2147483647\n";
    CheckCin(random_numbers, 1);
    MyVector<int> numbers_first(random_numbers);
    for (int i = 0; i < random_numbers; i++) {
        numbers_first[i] = rand();
    }
    while (1) {
        int choice;
        int compareCount = 0;
        cout << "请选择排序算法: \n";
        printf("====================================================\n");
        printf("**                  排序算法比较                  **\n");
        printf("====================================================\n");
        printf("**                  1.冒泡排序                    **\n");
        printf("**                  2.选择排序                    **\n");
        printf("**                  3.直接插入排序                **\n");
        printf("**                  4.折半插入排序                **\n");
        printf("**                  5.希尔排序                    **\n");
        printf("**                  6.快速排序                    **\n");
        printf("**                  7.堆排序                      **\n");
        printf("**                  8.归并排序                    **\n");
        printf("**                  9.基数排序                    **\n");
        printf("**                  0.退出程序                    **\n");
        printf("====================================================\n");
        CheckCin(choice, 0, 9);
        auto start = chrono::high_resolution_clock::now();
        MyVector<int> numbers = numbers_first;
        switch (choice) {
        case 1:
            cout << "冒泡排序开始,请等待结果\n";
            BubbleSort(numbers, compareCount);
            break;
        case 2:
            cout << "选择排序开始，请等待结果\n";
            SelectSort(numbers, compareCount);
            break;
        case 3:
            cout << "直接插入排序开始，请等待结果\n";
            StraightInsertSort(numbers, compareCount);
            break;
        case 4:
            cout << "折半插入排序开始，请等待结果\n";
            BinaryInsertSort(numbers, compareCount);
            break;
        case 5:
            cout << "希尔排序开始，请等待结果\n";
            ShellSort(numbers, compareCount);
            break;
        case 6:
            cout << "快速排序开始，请等待结果\n";
            QuickSort(numbers, 0, numbers.size() - 1, compareCount);
            break;
        case 7:
            cout << "堆排序开始，请等待结果\n";
            HeapSort(numbers, numbers.size(), compareCount);
            break;
        case 8:
            cout << "归并排序开始，请等待结果\n";
            MergeSort(numbers, 0, numbers.size() - 1, compareCount);
            break;
        case 9:
            cout << "基数排序开始，请等待结果\n";
            RadixSort(numbers, compareCount);
            break;
        case 0:
            cout << "程序退出\n";
            return 0;
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "排序完成\n";
        cout << "比较次数: " << compareCount << endl;
        cout << "排序时间: " << elapsed.count() << "s\n";
    }
    return 0;
}