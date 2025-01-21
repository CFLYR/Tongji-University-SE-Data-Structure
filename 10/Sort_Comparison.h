#include "MyVector.h"
#include <chrono>
#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

// �������������Ƿ���ָ����Χ��
void CheckCin(int& value, const int lower_limit = 0,
    const int higher_limit = numeric_limits<int>::max())
{
    while (1) {
        cin >> value;
        if (cin.fail()) {
            cout << "�������������\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else if (value < lower_limit || value > higher_limit) {
            cout << "�������������\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return;
}

// ð������
void BubbleSort(const MyVector<int> vec, int& compareCount)
{
    MyVector<int> numbers = vec;
    int n = numbers.size();
    for (int i = 0; i < n - 1; i++) {
        bool flag = false;
        for (int j = n - 1; j > i; j--) {
            compareCount++;
            if (numbers[j] < numbers[j - 1]) {
                swap(numbers[j], numbers[j - 1]);
                flag = true;
            }
        }
        if (!flag) {
            break;
        }
    }
    return;
}

// ѡ������
void SelectSort(const MyVector<int> vec, int& compareCount)
{
    MyVector<int> numbers = vec;
    int n = numbers.size();
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            compareCount++;
            if (numbers[j] < numbers[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(numbers[i], numbers[min_index]);
        }
    }
}

// ֱ�Ӳ�������
void StraightInsertSort(const MyVector<int> vec, int& compareCount)
{
    int temp_prior;
    MyVector<int> numbers = vec;
    int n = numbers.size();
    for (int i = 1; i < n; i++) {
        temp_prior = numbers[i];
        int j = i;
        while (j > 0 && (compareCount++, temp_prior < numbers[j - 1])) {
            numbers[j] = numbers[j - 1];
            j--;
        }
        numbers[j] = temp_prior;
    }
}

// �۰��������
void BinaryInsertSort(const MyVector<int> vec, int& compareCount)
{
    MyVector<int> numbers = vec;
    int n = numbers.size();
    for (int i = 1; i < n; i++) {
        int temp = numbers[i];
        int left = 0, right = i - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            compareCount++;
            if (numbers[mid] > temp)
                right = mid - 1;
            else
                left = mid + 1;
        }
        for (int j = i - 1; j >= left; j--) {
            numbers[j + 1] = numbers[j];
        }
        numbers[left] = temp;
    }
}

// ϣ������
void ShellSort(const MyVector<int> vec, int& compareCount)
{
    int temp_prior;
    MyVector<int> numbers = vec;
    int n = numbers.size();
    int i, j, gap;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp_prior = numbers[i];
            j = i - gap;
            while (j >= 0 && (compareCount++, temp_prior < numbers[j])) {
                numbers[j + gap] = numbers[j];
                j -= gap;
            }
            numbers[j + gap] = temp_prior;
        }
    }
}

// ��������ķ�������
int Partition(MyVector<int>& numbers, int low, int high, int& compareCount)
{
    int pivot = numbers[low];
    int i = low, j = high;
    while (i < j) {
        while (i < j && numbers[j] >= pivot) {
            compareCount++; // �Ƚ�ʱ����compareCount
            j--;
        }
        if (i < j) {
            numbers[i++] = numbers[j];
        }
        while (i < j && numbers[i] <= pivot) {
            compareCount++; // �Ƚ�ʱ����compareCount
            i++;
        }
        if (i < j) {
            numbers[j] = numbers[i];
        }
    }
    numbers[i] = pivot;
    return i;
}

// ��������
void QuickSort(MyVector<int>& numbers, int low, int high, int& compareCount)
{
    if (low < high) {
        int pivot_index = Partition(numbers, low, high, compareCount);
        QuickSort(numbers, low, pivot_index - 1, compareCount);
        QuickSort(numbers, pivot_index + 1, high, compareCount);
    }
}

// �ѵ���
void HeadAdjust(MyVector<int>& numbers, int i, int length, int& compareCount)
{
    int child = 2 * i + 1;
    while (child < length) {
        if (child + 1 < length) {
            compareCount++;
            if (numbers[child] < numbers[child + 1])
                child++; // �ҽϴ���ӽڵ�
        }
        compareCount++;
        if (numbers[i] > numbers[child])
            break;
        swap(numbers[i], numbers[child]);
        i = child;
        child = 2 * i + 1;
    }
}
void BulidMaxHeap(MyVector<int>& numbers, int length, int& compareCount)
{
    for (int i = length / 2 - 1; i >= 0; i--) {
        HeadAdjust(numbers, i, length, compareCount);
    }
}

void HeapSort(MyVector<int>& numbers, int length, int& compareCount)
{
    BulidMaxHeap(numbers, length, compareCount);
    for (int i = length - 1; i > 0; i--) {
        swap(numbers[0], numbers[i]);
        HeadAdjust(numbers, 0, i, compareCount);
    }
}

// �鲢����
void Merge(MyVector<int>& numbers, int low, int mid, int high,
    int& compareCount)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int i = 0, j = 0, k = low;

    MyVector<int> leftArr(n1);
    MyVector<int> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = numbers[low + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = numbers[mid + 1 + i];

    while (i < n1 && j < n2) {
        compareCount++;
        if (leftArr[i] <= rightArr[j])
            numbers[k++] = leftArr[i++];
        else
            numbers[k++] = rightArr[j++];
    }

    while (i < n1) {
        compareCount++;
        numbers[k++] = leftArr[i++];
    }

    while (j < n2) {
        compareCount++;
        numbers[k++] = rightArr[j++];
    }
}

// �鲢����
void MergeSort(MyVector<int>& numbers, int low, int high, int& compareCount)
{
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(numbers, low, mid, compareCount);
        MergeSort(numbers, mid + 1, high, compareCount);
        Merge(numbers, low, mid, high, compareCount);
    }
}

// ��ȡ��������Ļ���
static int getDigitBase16(int x, int d)
{
    return x >> (d << 2) & 0xF;
}

// ��������
void RadixSort(const MyVector<int> vec, int& compareCount)
{
    MyVector<int> numbers = vec;
    int n = numbers.size();
    int max = -1000000000, maxd = -1;
    for (int i = 0; i < n; i++)
        if (numbers[i] > max)
            max = numbers[i];
    while (max) {
        max >>= 4;
        maxd++;
    }
    int* aux = new int[n];
    int* count = new int[16];
    for (int d = 0; d <= maxd; d++) {
        memset(count, 0, 16 * sizeof(int));
        for (int i = 0; i < n; i++)
            count[getDigitBase16(numbers[i], d)]++;
        for (int i = 1; i < 16; i++)
            count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--)
            aux[--count[getDigitBase16(numbers[i], d)]] = numbers[i];
        memcpy(numbers.data_ptr(), aux, n * sizeof(int));
    }
    delete[] count;
    delete[] aux;
}