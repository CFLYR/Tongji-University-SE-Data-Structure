#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define IGNORE_SIZE 2147483647
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

// 自定义字符串类
class MyString {
private:
    char* data; // 字符数据
    size_t length; // 字符串长度

    // 分配内存并复制字符串
    void allocate_and_copy(const char* str)
    {
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

public:
    // 默认构造函数
    MyString()
        : data(nullptr)
        , length(0)
    {
        data = new char[1];
        data[0] = '\0';
    }

    // 从C风格字符串构造
    MyString(const char* str)
    {
        allocate_and_copy(str);
    }

    // 拷贝构造函数
    MyString(const MyString& other)
    {
        allocate_and_copy(other.data);
    }

    // 移动构造函数
    MyString(MyString&& other) noexcept
        : data(other.data)
        , length(other.length)
    {
        other.data = nullptr;
        other.length = 0;
    }

    // 析构函数
    ~MyString()
    {
        delete[] data;
    }

    // 赋值运算符
    MyString& operator=(const MyString& other)
    {
        if (this != &other) {
            delete[] data;
            allocate_and_copy(other.data);
        }
        return *this;
    }

    // 移动赋值运算符
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

    // 获取C风格字符串
    const char* c_str() const
    {
        return data;
    }

    // 获取字符串长度
    size_t size() const
    {
        return length;
    }

    // 重载相等运算符
    bool operator==(const MyString& other) const
    {
        return strcmp(data, other.data) == 0;
    }

    // 重载不等运算符
    bool operator!=(const MyString& other) const
    {
        return !(*this == other);
    }

    // 重载小于运算符（用于排序）
    bool operator<(const MyString& other) const
    {
        return strcmp(data, other.data) < 0;
    }

    // 重载输出运算符
    friend ostream& operator<<(ostream& os, const MyString& str)
    {
        return os << str.data;
    }

    // 重载输入运算符
    friend istream& operator>>(istream& is, MyString& str)
    {
        char buffer[1024]; // 假设输入不会超过1023个字符
        is >> buffer;
        str = MyString(buffer);
        return is;
    }
};

// 用于统计工作职位的类
class MyJob {
private:
    // 键值对结构体
    struct KeyValuePair {
        MyString key; // 职位名称
        int value; // 职位数量
        KeyValuePair* next; // 指向下一个键值对

        KeyValuePair(MyString k, int v)
            : key(k)
            , value(v)
            , next(nullptr)
        {
        }
    };

    KeyValuePair* head; // 链表头指针

public:
    // 构造函数
    MyJob()
        : head(nullptr)
    {
    }

    // 析构函数，释放链表内存
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

    // 插入或更新职位
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

        // 如果职位不存在，创建新节点
        KeyValuePair* newPair = new KeyValuePair(key, value);
        if (prev == nullptr) {
            head = newPair;
        } else {
            prev->next = newPair;
        }
    }

    // 打印所有职位及其数量
    void print() const
    {
        KeyValuePair* current = head;
        while (current != nullptr) {
            cout << current->key << ": " << current->value << endl;
            current = current->next;
        }
    }
};

// 学生信息结构体
struct stu_info {
    int id; // 学号
    MyString name; // 姓名
    MyString sex; // 性别
    int age; // 年龄
    MyString job; // 报考类别

    // 构造函数
    stu_info(int d = 0, MyString n = "1", MyString s = "1", int a = 1, MyString j = "1")
    {
        id = d;
        sex = s;
        name = n;
        age = a;
        job = j;
    }

    // 重载输出运算符，方便打印学生信息
    friend ostream& operator<<(ostream& os, const stu_info& stu)
    {
        os << left << setw(10) << stu.id
           << left << setw(10) << stu.name
           << left << setw(10) << stu.sex
           << left << setw(10) << stu.age
           << left << setw(10) << stu.job;
        return os;
    }

    // 重载输入运算符，方便输入学生信息
    friend istream& operator>>(istream& is, stu_info& stu)
    {
        is >> stu.id >> stu.sex >> stu.name >> stu.age >> stu.job;
        return is;
    }

    // 重载比较运算符，根据学号比较
    bool operator==(const stu_info& other) const
    {
        return id == other.id;
    }

    // 静态函数，根据性别比较
    static bool compare_sex(const stu_info& stu, const MyString& sex)
    {
        return stu.sex == sex;
    }
};

// 前置声明模板类List
template <class class_type>
class List;

// 链表节点模板类
template <class class_type>
class ListNode {
    friend class List<class_type>; // 链表类为其友元类
private:
public:
    class_type data; // 节点数据
    ListNode* link; // 指向下一个节点的指针

    // 构造函数初始化节点
    ListNode(class_type val)
        : data(val)
        , link(NULL)
    {
    }
};

// 链表模板类
template <class class_type>
class List {
public:
    ListNode<class_type>*first, *last; // 链表头尾指针

    // 构造函数，使用初始化列表
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

    // 析构函数，释放链表内存
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

    // 清空链表，保留头节点
    void MakeEmpty()
    {
        ListNode<class_type>* q;
        while (first->link != NULL) {
            q = first->link;
            first->link = q->link; // 移除节点
            delete q; // 释放内存
        }
        last = first;
        return;
    }

    // 获取链表长度
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

    // 查找节点，返回节点指针
    ListNode<class_type>* Find(class_type value)
    {
        ListNode<class_type>* p = first;
        while (p != NULL && !(p->data == value)) {
            p = p->link;
        }
        return p;
    }

    // 查找节点位置，返回位置索引
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

    // 在指定位置插入节点
    int Insert(const class_type x, const int i)
    {
        ListNode<class_type>* newNode = new ListNode<class_type>(x);
        if (i == 1) { // 插入到头部
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
                cout << "无效的插入位置!\n";
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
        return 1; // 插入成功
    }

    // 计算总年龄和学生数量
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

    // 根据性别统计数量
    void Findsex(int& male, int& female, int& lgbt)
    {
        ListNode<class_type>* p = first;
        while (p != NULL) {
            if (p->data.sex == "男") {
                male++;
            } else if (p->data.sex == "女") {
                female++;
            } else {
                lgbt++;
            }
            p = p->link;
        }
        return;
    }

    // 删除指定位置的节点
    int Remove(int i)
    {
        if (i < 1 || first == NULL) {
            cout << "无效的删除位置!\n";
            return 0;
        }

        ListNode<class_type>* p = first;
        if (i == 1) { // 删除头节点
            first = first->link;
            if (first == NULL)
                last = NULL;
        } else {
            for (int k = 1; p != NULL && k < i - 1; k++) {
                p = p->link;
            }
            if (p == NULL || p->link == NULL) {
                cout << "无效的删除位置!\n";
                return 0;
            }
            ListNode<class_type>* q = p->link;
            p->link = q->link;
            if (q == last)
                last = p;
            delete q;
        }
        return 1; // 删除成功
    }

    // 打印整个链表
    void Print() const
    {
        ListNode<class_type>* p = first;
        while (p != NULL) {
            cout << p->data << endl;
            p = p->link;
        }
        return;
    }

    // 打印单个学生信息
    void single_Print(ListNode<class_type>* i)
    {
        cout << i->data << endl;
        return;
    }
};

// 学生列表管理类
class stu_list {

private:
public:
    List<stu_info> list_1; // 学生链表

    // 默认构造函数
    stu_list()
        : list_1({})
    {
    }

    // 使用初始化列表的构造函数
    stu_list(initializer_list<stu_info> values)
        : list_1(values)
    {
    }

    // 输入学生信息
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
                        cout << "输入信息错误，请重新输入" << endl;
                        continue;
                    } else if (age <= 0) {
                        cin.ignore(IGNORE_SIZE, '\n');
                        cout << "输入信息错误，请重新输入" << endl;
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
                        cout << "输入信息错误，请重新输入" << endl;
                        continue;
                    } else if (id < 0 || age <= 0) {
                        cin.ignore(IGNORE_SIZE, '\n');
                        cout << "输入信息错误，请重新输入" << endl;
                        continue;
                    } else if (list_1.Findpos(stu_info(id))) {
                        cout << "考号 " << id << " 已存在，请重新输入" << endl;
                        cin.ignore(IGNORE_SIZE, '\n');
                        continue;
                    } else {
                        cin.ignore(IGNORE_SIZE, '\n');
                        break;
                    }
                }
            }
            if (sex != "男" && sex != "女") {
                sex = "非法性别";
            }
            add_student(stu_info(id, name, sex, age, job));
        }
        return;
    }

    // 查找学生数量
    int find_studentnum()
    {
        return list_1.Length();
    }

    // 对学生进行排序
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

    // 添加学生到列表
    void add_student(const stu_info& student)
    {
        list_1.Insert(student, list_1.Length() + 1);
        sort_students();
        return;
    }

    // 移除指定索引的学生
    void remove_student(int index)
    {
        list_1.Remove(index);
        return;
    }

    // 查找是否存在指定学生
    bool find_student(int index)
    {
        if (list_1.Findpos(stu_info(index))) {
            return 1;
        } else {
            return 0;
        }
    }

    // 查找学生位置
    int find_studentpos(int index)
    {
        if (list_1.Findpos(stu_info(index))) {
            return list_1.Findpos(stu_info(index));
        } else {
            return 0;
        }
    }

    // 打印单个学生信息
    void print_single_stu(int index)
    {
        ListNode<stu_info>* point = list_1.Find(stu_info(index));
        list_1.single_Print(point);
        return;
    }

    // 统计学生性别分布
    void student_sex()
    {
        int male = 0;
        int female = 0;
        int lgbt = 0;
        list_1.Findsex(male, female, lgbt);
        cout << "男：" << male << endl;
        cout << "女：" << female << endl;
        cout << "非法性别：" << lgbt << endl;

        return;
    }

    // 计算平均年龄
    void average_age()
    {
        int count = 0;
        int all = 0;
        list_1.Findage(count, all);
        float allage = float(count) / float(all);
        cout << "平均年龄：" << fixed << setprecision(2) << allage << endl;
        return;
    }

    // 汇总职位信息
    void summarize_jobs(MyJob& job_count)
    {
        ListNode<stu_info>* p = list_1.first;
        while (p != NULL) {
            job_count.insert(p->data.job, 1);
            p = p->link;
        }
    }

    // 打印所有学生信息
    void print_students() const
    {
        list_1.Print();
        return;
    }
};

// 打印表头
void print_chart()
{
    cout << left << setw(10) << "考号"
         << left << setw(10) << "姓名"
         << left << setw(10) << "性别"
         << left << setw(10) << "年龄"
         << left << setw(10) << "报考类别" << endl;
    return;
}

// 打印分割线
void print_line()
{
    for (int i = 1; i <= 50; i++) {
        cout << "-";
    }
    cout << endl;
    return;
}