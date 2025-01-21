#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define IGNORE_SIZE 2147483647
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

// �Զ����ַ�����
class MyString {
private:
    char* data; // �ַ�����
    size_t length; // �ַ�������

    // �����ڴ沢�����ַ���
    void allocate_and_copy(const char* str)
    {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

public:
    // Ĭ�Ϲ��캯��
    MyString()
        : data(nullptr)
        , length(0)
    {
        data = new char[1];
        data[0] = '\0';
    }

    // ��C����ַ�������
    MyString(const char* str)
    {
        allocate_and_copy(str);
    }

    // �������캯��
    MyString(const MyString& other)
    {
        allocate_and_copy(other.data);
    }

    // �ƶ����캯��
    MyString(MyString&& other) noexcept
        : data(other.data)
        , length(other.length)
    {
        other.data = nullptr;
        other.length = 0;
    }

    // ��������
    ~MyString()
    {
        delete[] data;
    }

    // ��ֵ�����
    MyString& operator=(const MyString& other)
    {
        if (this != &other) {
            delete[] data;
            allocate_and_copy(other.data);
        }
        return *this;
    }

    // �ƶ���ֵ�����
    MyString& operator=(MyString&& other) noexcept
    {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        return *this;
    }

    // ��ȡC����ַ���
    const char* c_str() const
    {
        return data;
    }

    // ��ȡ�ַ�������
    size_t size() const
    {
        return length;
    }

    // ������������
    bool operator==(const MyString& other) const
    {
        return strcmp(data, other.data) == 0;
    }

    // ���ز��������
    bool operator!=(const MyString& other) const
    {
        return !(*this == other);
    }

    // ����С�����������������
    bool operator<(const MyString& other) const
    {
        return strcmp(data, other.data) < 0;
    }

    // ������������
    friend ostream& operator<<(ostream& os, const MyString& str)
    {
        return os << str.data;
    }

    // �������������
    friend istream& operator>>(istream& is, MyString& str)
    {
        char buffer[1024]; // �������벻�ᳬ��1023���ַ�
        is >> buffer;
        str = MyString(buffer);
        return is;
    }
};

// ����ͳ�ƹ���ְλ����
class MyJob {
private:
    // ��ֵ�Խṹ��
    struct KeyValuePair {
        MyString key; // ְλ����
        int value; // ְλ����
        KeyValuePair* next; // ָ����һ����ֵ��

        KeyValuePair(MyString k, int v)
            : key(k)
            , value(v)
            , next(nullptr)
        {
        }
    };

    KeyValuePair* head; // ����ͷָ��

public:
    // ���캯��
    MyJob()
        : head(nullptr)
    {
    }

    // �����������ͷ������ڴ�
    ~MyJob()
    {
        KeyValuePair* current = head;
        while (current != nullptr) {
            KeyValuePair* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = nullptr;
    }

    // ��������ְλ
    void insert(const MyString& key, int value)
    {
        KeyValuePair* current = head;
        KeyValuePair* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                current->value += value;
                return;
            }
            prev = current;
            current = current->next;
        }

        // ���ְλ�����ڣ������½ڵ�
        KeyValuePair* newPair = new KeyValuePair(key, value);
        if (prev == nullptr) {
            head = newPair;
        } else {
            prev->next = newPair;
        }
    }

    // ��ӡ����ְλ��������
    void print() const
    {
        KeyValuePair* current = head;
        while (current != nullptr) {
            cout << current->key << ": " << current->value << endl;
            current = current->next;
        }
    }
};

// ѧ����Ϣ�ṹ��
struct stu_info {
    int id; // ѧ��
    MyString name; // ����
    MyString sex; // �Ա�
    int age; // ����
    MyString job; // �������

    // ���캯��
    stu_info(int d = 0, MyString n = "1", MyString s = "1", int a = 1, MyString j = "1")
    {
        id = d;
        sex = s;
        name = n;
        age = a;
        job = j;
    }

    // �������������������ӡѧ����Ϣ
    friend ostream& operator<<(ostream& os, const stu_info& stu)
    {
        os << left << setw(10) << stu.id
           << left << setw(10) << stu.name
           << left << setw(10) << stu.sex
           << left << setw(10) << stu.age
           << left << setw(10) << stu.job;
        return os;
    }

    // �����������������������ѧ����Ϣ
    friend istream& operator>>(istream& is, stu_info& stu)
    {
        is >> stu.id >> stu.sex >> stu.name >> stu.age >> stu.job;
        return is;
    }

    // ���رȽ������������ѧ�űȽ�
    bool operator==(const stu_info& other) const
    {
        return id == other.id;
    }

    // ��̬�����������Ա�Ƚ�
    static bool compare_sex(const stu_info& stu, const MyString& sex)
    {
        return stu.sex == sex;
    }
};

// ǰ������ģ����List
template <class class_type>
class List;

// ����ڵ�ģ����
template <class class_type>
class ListNode {
    friend class List<class_type>; // ������Ϊ����Ԫ��
private:
public:
    class_type data; // �ڵ�����
    ListNode* link; // ָ����һ���ڵ��ָ��

    // ���캯����ʼ���ڵ�
    ListNode(class_type val)
        : data(val)
        , link(NULL)
    {
    }
};

// ����ģ����
template <class class_type>
class List {
public:
    ListNode<class_type>*first, *last; // ����ͷβָ��

    // ���캯����ʹ�ó�ʼ���б�
    List(initializer_list<class_type> values)
        : first(NULL)
        , last(NULL)
    {
        for (class_type val : values) {
            ListNode<class_type>* newNode = new ListNode<class_type>(val);
            if (first == NULL) {
                first = last = newNode;
            } else {
                last->link = newNode;
                last = newNode;
            }
        }
        return;
    }

    // �����������ͷ������ڴ�
    ~List()
    {
        ListNode<class_type>* p = first;
        while (p != NULL) {
            ListNode<class_type>* temp = p;
            p = p->link;
            delete temp;
        }
        return;
    }

    // �����������ͷ�ڵ�
    void MakeEmpty()
    {
        ListNode<class_type>* q;
        while (first->link != NULL) {
            q = first->link;
            first->link = q->link; // �Ƴ��ڵ�
            delete q; // �ͷ��ڴ�
        }
        last = first;
        return;
    }

    // ��ȡ������
    int Length() const
    {
        ListNode<class_type>* p = first;
        int count = 0;
        while (p != NULL) {
            p = p->link;
            count++;
        }
        return count;
    }

    // ���ҽڵ㣬���ؽڵ�ָ��
    ListNode<class_type>* Find(class_type value)
    {
        ListNode<class_type>* p = first;
        while (p != NULL && !(p->data == value)) {
            p = p->link;
        }
        return p;
    }

    // ���ҽڵ�λ�ã�����λ������
    int Findpos(class_type value)
    {
        int count = 1;
        ListNode<class_type>* p = first;
        while (p != NULL && !(p->data == value)) {
            p = p->link;
            count++;
        }
        if (p == NULL) {
            return 0;
        }
        return count;
    }

    // ��ָ��λ�ò���ڵ�
    int Insert(const class_type x, const int i)
    {
        ListNode<class_type>* newNode = new ListNode<class_type>(x);
        if (i == 1) { // ���뵽ͷ��
            newNode->link = first;
            first = newNode;
            if (last == NULL) {
                last = newNode;
            }
        } else {
            ListNode<class_type>* p = first;
            for (int k = 1; p != NULL && k < i - 1; k++) {
                p = p->link;
            }
            if (p == NULL) {
                cout << "��Ч�Ĳ���λ��!\n";
                delete newNode;
                return 0;
            } else {
                newNode->link = p->link;
                p->link = newNode;
                if (newNode->link == NULL) {
                    last = newNode;
                }
            }
        }
        return 1; // ����ɹ�
    }

    // �����������ѧ������
    void Findage(int& count, int& all)
    {
        ListNode<class_type>* p = first;
        while (p != NULL) {
            all++;
            count += p->data.age;
            p = p->link;
        }
        return;
    }

    // �����Ա�ͳ������
    void Findsex(int& male, int& female, int& lgbt)
    {
        ListNode<class_type>* p = first;
        while (p != NULL) {
            if (p->data.sex == "��") {
                male++;
            } else if (p->data.sex == "Ů") {
                female++;
            } else {
                lgbt++;
            }
            p = p->link;
        }
        return;
    }

    // ɾ��ָ��λ�õĽڵ�
    int Remove(int i)
    {
        if (i < 1 || first == NULL) {
            cout << "��Ч��ɾ��λ��!\n";
            return 0;
        }

        ListNode<class_type>* p = first;
        if (i == 1) { // ɾ��ͷ�ڵ�
            first = first->link;
            if (first == NULL)
                last = NULL;
        } else {
            for (int k = 1; p != NULL && k < i - 1; k++) {
                p = p->link;
            }
            if (p == NULL || p->link == NULL) {
                cout << "��Ч��ɾ��λ��!\n";
                return 0;
            }
            ListNode<class_type>* q = p->link;
            p->link = q->link;
            if (q == last)
                last = p;
            delete q;
        }
        return 1; // ɾ���ɹ�
    }

    // ��ӡ��������
    void Print() const
    {
        ListNode<class_type>* p = first;
        while (p != NULL) {
            cout << p->data << endl;
            p = p->link;
        }
        return;
    }

    // ��ӡ����ѧ����Ϣ
    void single_Print(ListNode<class_type>* i)
    {
        cout << i->data << endl;
        return;
    }
};

// ѧ���б������
class stu_list {

private:
public:
    List<stu_info> list_1; // ѧ������

    // Ĭ�Ϲ��캯��
    stu_list()
        : list_1({})
    {
    }

    // ʹ�ó�ʼ���б�Ĺ��캯��
    stu_list(initializer_list<stu_info> values)
        : list_1(values)
    {
    }

    // ����ѧ����Ϣ
    void input_students(int count, int edit = 0)
    {
        for (int i = 0; i < count; ++i) {
            int id, age;
            MyString sex;
            MyString name, job;
            if (edit) {
                id = edit;
                while (1) {
                    cin >> name >> sex >> age >> job;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(IGNORE_SIZE, '\n');
                        cout << "������Ϣ��������������" << endl;
                        continue;
                    } else if (age <= 0) {
                        cin.ignore(IGNORE_SIZE, '\n');
                        cout << "������Ϣ��������������" << endl;
                        continue;
                    } else {
                        cin.ignore(IGNORE_SIZE, '\n');
                        break;
                    }
                }
            } else {
                while (1) {
                    cin >> id >> name >> sex >> age >> job;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(IGNORE_SIZE, '\n');
                        cout << "������Ϣ��������������" << endl;
                        continue;
                    } else if (id < 0 || age <= 0) {
                        cin.ignore(IGNORE_SIZE, '\n');
                        cout << "������Ϣ��������������" << endl;
                        continue;
                    } else if (list_1.Findpos(stu_info(id))) {
                        cout << "���� " << id << " �Ѵ��ڣ�����������" << endl;
                        cin.ignore(IGNORE_SIZE, '\n');
                        continue;
                    } else {
                        cin.ignore(IGNORE_SIZE, '\n');
                        break;
                    }
                }
            }
            if (sex != "��" && sex != "Ů") {
                sex = "�Ƿ��Ա�";
            }
            add_student(stu_info(id, name, sex, age, job));
        }
        return;
    }

    // ����ѧ������
    int find_studentnum()
    {
        return list_1.Length();
    }

    // ��ѧ����������
    void sort_students()
    {
        if (list_1.Length() <= 1)
            return;

        ListNode<stu_info>* sorted = nullptr;

        while (list_1.first != nullptr) {
            ListNode<stu_info>* node = list_1.first;
            list_1.first = list_1.first->link;

            if (sorted == nullptr || node->data.id < sorted->data.id) {
                node->link = sorted;
                sorted = node;
            } else {
                ListNode<stu_info>* current = sorted;
                while (current->link != nullptr && current->link->data.id < node->data.id) {
                    current = current->link;
                }
                node->link = current->link;
                current->link = node;
            }
        }

        list_1.first = sorted;
        return;
    }

    // ���ѧ�����б�
    void add_student(const stu_info& student)
    {
        list_1.Insert(student, list_1.Length() + 1);
        sort_students();
        return;
    }

    // �Ƴ�ָ��������ѧ��
    void remove_student(int index)
    {
        list_1.Remove(index);
        return;
    }

    // �����Ƿ����ָ��ѧ��
    bool find_student(int index)
    {
        if (list_1.Findpos(stu_info(index))) {
            return 1;
        } else {
            return 0;
        }
    }

    // ����ѧ��λ��
    int find_studentpos(int index)
    {
        if (list_1.Findpos(stu_info(index))) {
            return list_1.Findpos(stu_info(index));
        } else {
            return 0;
        }
    }

    // ��ӡ����ѧ����Ϣ
    void print_single_stu(int index)
    {
        ListNode<stu_info>* point = list_1.Find(stu_info(index));
        list_1.single_Print(point);
        return;
    }

    // ͳ��ѧ���Ա�ֲ�
    void student_sex()
    {
        int male = 0;
        int female = 0;
        int lgbt = 0;
        list_1.Findsex(male, female, lgbt);
        cout << "�У�" << male << endl;
        cout << "Ů��" << female << endl;
        cout << "�Ƿ��Ա�" << lgbt << endl;

        return;
    }

    // ����ƽ������
    void average_age()
    {
        int count = 0;
        int all = 0;
        list_1.Findage(count, all);
        float allage = float(count) / float(all);
        cout << "ƽ�����䣺" << fixed << setprecision(2) << allage << endl;
        return;
    }

    // ����ְλ��Ϣ
    void summarize_jobs(MyJob& job_count)
    {
        ListNode<stu_info>* p = list_1.first;
        while (p != NULL) {
            job_count.insert(p->data.job, 1);
            p = p->link;
        }
    }

    // ��ӡ����ѧ����Ϣ
    void print_students() const
    {
        list_1.Print();
        return;
    }
};

// ��ӡ��ͷ
void print_chart()
{
    cout << left << setw(10) << "����"
         << left << setw(10) << "����"
         << left << setw(10) << "�Ա�"
         << left << setw(10) << "����"
         << left << setw(10) << "�������" << endl;
    return;
}

// ��ӡ�ָ���
void print_line()
{
    for (int i = 1; i <= 50; i++) {
        cout << "-";
    }
    cout << endl;
    return;
}